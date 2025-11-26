/**
 * @file CvPipeline.cpp
 * @brief Implementation of the CCM Code Embedded Vision Pipeline.
 *
 * Handles buffer management (PSRAM/DRAM) and executes the configured
 * CV stages sequentially.
 *
 * @author CCM Code (Christie Cahill Meyer)
 * @date 2025
 * @copyright MIT License
 */

#include "CvPipeline.hpp"
#include <esp_log.h>
#include <esp_heap_caps.h>
#include <cstring>
#include <algorithm>
#include <queue>

static const char* TAG = "CvPipeline";

CvPipeline::CvPipeline() {
    // Set safe defaults
    m_config.enable_grayscale = true;
}

CvPipeline::~CvPipeline() {
    if (m_out_buffer) {
        heap_caps_free(m_out_buffer);
        m_out_buffer = nullptr;
    }
}

void CvPipeline::configure(const PipelineConfig& config) {
    m_config = config;
}

void CvPipeline::process(camera_fb_t* frame) {
    if (!frame) {
        ESP_LOGE(TAG, "Input frame is null");
        return;
    }

    // 1. Reset State
    m_blobs.clear();
    m_width = frame->width;
    m_height = frame->height;
    size_t needed_size = m_width * m_height;

    // 2. Buffer Management
    // Allocate in PSRAM (SPIRAM) if available to save internal heap.
    if (m_buffer_alloc_size < needed_size) {
        if (m_out_buffer) {
            heap_caps_free(m_out_buffer);
        }

        m_out_buffer = (uint8_t*)heap_caps_malloc(needed_size, MALLOC_CAP_SPIRAM);
        if (!m_out_buffer) {
            // Fallback to internal RAM (only works for small resolutions like QVGA)
            ESP_LOGW(TAG, "PSRAM allocation failed, falling back to DRAM");
            m_out_buffer = (uint8_t*)heap_caps_malloc(needed_size, MALLOC_CAP_8BIT);
        }

        if (!m_out_buffer) {
            ESP_LOGE(TAG, "Failed to allocate pipeline buffer (%zu bytes)", needed_size);
            return;
        }
        m_buffer_alloc_size = needed_size;
    }

    // 3. Execution Pipeline
    
    // Stage 1: Grayscale (Base Requirement)
    convertGrayscale(frame);

    // Stage 2: Region of Interest (Crop)
    if (m_config.enable_roi) {
        applyROI();
    }

    // Stage 3: Downsampling (Scale)
    if (m_config.downsample_factor > 1) {
        applyDownsample();
    }

    // Stage 4: Thresholding (Binarize)
    if (m_config.enable_threshold) {
        applyThreshold();
    }

    // Stage 5: Blob Analysis
    if (m_config.enable_blob_detection) {
        runBlobDetection();
    }
}

void CvPipeline::convertGrayscale(const camera_fb_t* fb) {
    // Conversion: RGB565 -> 8-bit Grayscale
    const uint8_t* src = fb->buf;
    uint8_t* dst = m_out_buffer;
    size_t len = fb->width * fb->height;

    for (size_t i = 0; i < len; i++) {
        uint8_t low = *src++;
        uint8_t high = *src++;
        uint16_t pixel = (high << 8) | low;

        // Extract RGB565 components
        uint8_t r = (pixel >> 11) & 0x1F;
        uint8_t g = (pixel >> 5) & 0x3F;
        uint8_t b = pixel & 0x1F;

        // Approximate Luminance:
        // Scaled to 8-bit range approx (R*2 + G*4 + B) / 8
        // Higher precision: 0.299R + 0.587G + 0.114B
        
        // We expand 5/6-bit to 8-bit first for better accuracy
        uint16_t r8 = (r * 527 + 23) >> 6;
        uint16_t g8 = (g * 259 + 33) >> 6;
        uint16_t b8 = (b * 527 + 23) >> 6;

        *dst++ = (uint8_t)((r8 * 77 + g8 * 150 + b8 * 29) >> 8);
    }
}

void CvPipeline::applyROI() {
    uint16_t rx = std::min((size_t)m_config.roi_x, m_width - 1);
    uint16_t ry = std::min((size_t)m_config.roi_y, m_height - 1);
    uint16_t rw = std::min((size_t)m_config.roi_w, m_width - rx);
    uint16_t rh = std::min((size_t)m_config.roi_h, m_height - ry);

    if (rw == 0 || rh == 0) return;

    // Destructive crop: Move ROI data to the start of the buffer.
    uint8_t* src_base = m_out_buffer + (ry * m_width) + rx;
    uint8_t* dst = m_out_buffer;

    for (int y = 0; y < rh; y++) {
        memmove(dst, src_base, rw);
        dst += rw;
        src_base += m_width;
    }

    m_width = rw;
    m_height = rh;
}

void CvPipeline::applyDownsample() {
    int factor = m_config.downsample_factor;
    if (factor <= 1) return;

    size_t new_w = m_width / factor;
    size_t new_h = m_height / factor;
    uint8_t* dst = m_out_buffer;

    // Nearest Neighbor Downscaling
    for (size_t y = 0; y < new_h; y++) {
        for (size_t x = 0; x < new_w; x++) {
            size_t src_idx = (y * factor * m_width) + (x * factor);
            *dst++ = m_out_buffer[src_idx];
        }
    }

    m_width = new_w;
    m_height = new_h;
}

void CvPipeline::applyThreshold() {
    size_t len = m_width * m_height;
    uint8_t th = m_config.threshold_val;
    bool inv = m_config.invert;

    // TODO: Optimize with SIMD instructions (ESP32-S3 supports vector instructions)
    for (size_t i = 0; i < len; i++) {
        bool pass = (m_out_buffer[i] >= th);
        if (inv) pass = !pass;
        m_out_buffer[i] = pass ? 255 : 0;
    }
}

void CvPipeline::runBlobDetection() {
    // Algorithm: Queue-based Flood Fill (Scanline or recursive is risky on stack)
    if (m_width * m_height == 0) return;

    size_t len = m_width * m_height;
    std::queue<std::pair<uint16_t, uint16_t>> q;

    for (size_t i = 0; i < len; i++) {
        // Find a starting white pixel
        if (m_out_buffer[i] == 255) {
            uint16_t start_x = i % m_width;
            uint16_t start_y = i / m_width;

            Blob b = {start_x, start_y, 0, 0, 0, 0, 0};
            uint16_t min_x = start_x, max_x = start_x;
            uint16_t min_y = start_y, max_y = start_y;
            uint32_t sum_x = 0, sum_y = 0;

            q.push({start_x, start_y});
            m_out_buffer[i] = 0; // Mark visited (destructive)

            while (!q.empty()) {
                auto p = q.front();
                q.pop();

                uint16_t cx = p.first;
                uint16_t cy = p.second;

                // Accumulate statistics
                b.area++;
                sum_x += cx;
                sum_y += cy;

                if (cx < min_x) min_x = cx;
                if (cx > max_x) max_x = cx;
                if (cy < min_y) min_y = cy;
                if (cy > max_y) max_y = cy;

                // Check 4-connected neighbors
                const int dx[] = {1, -1, 0, 0};
                const int dy[] = {0, 0, 1, -1};

                for (int k = 0; k < 4; k++) {
                    int nx = cx + dx[k];
                    int ny = cy + dy[k];

                    // Bounds check
                    if (nx >= 0 && nx < (int)m_width && ny >= 0 && ny < (int)m_height) {
                        size_t nidx = ny * m_width + nx;
                        if (m_out_buffer[nidx] == 255) {
                            m_out_buffer[nidx] = 0; // Mark visited
                            q.push({(uint16_t)nx, (uint16_t)ny});
                        }
                    }
                }
            }

            // Store valid blobs
            if (b.area >= m_config.min_blob_area) {
                b.x = min_x;
                b.y = min_y;
                b.w = max_x - min_x + 1;
                b.h = max_y - min_y + 1;
                b.cx = sum_x / b.area;
                b.cy = sum_y / b.area;
                m_blobs.push_back(b);
            }
        }
    }
}