/**
 * @file CvPipeline.hpp
 * @brief Modular computer vision pipeline for ESP32-S3.
 *
 * Provides a configurable processing chain including Grayscale,
 * ROI extraction, Downsampling, Thresholding, and Blob Detection.
 * designed for memory-constrained embedded environments.
 *
 * @author CCM Code (Christie Cahill Meyer)
 * @date 2025
 * @copyright MIT License
 */

#pragma once

#include "esp_camera.h"
#include <vector>
#include <cstdint>

/// @brief Represents a detected object in the frame.
struct Blob {
    uint16_t x;      ///< Top-left X coordinate
    uint16_t y;      ///< Top-left Y coordinate
    uint16_t w;      ///< Width of the bounding box
    uint16_t h;      ///< Height of the bounding box
    uint16_t cx;     ///< Centroid X coordinate
    uint16_t cy;     ///< Centroid Y coordinate
    uint32_t area;   ///< Total pixel count
};

/// @brief Runtime configuration for the vision pipeline.
struct PipelineConfig {
    // --- Stage 1: Pre-processing ---
    bool enable_grayscale = true;     ///< Convert RGB565 to Grayscale (Required for most stages)

    // --- Stage 2: Segmentation ---
    bool enable_threshold = false;    ///< Enable binary thresholding
    uint8_t threshold_val = 100;      ///< 0-255 threshold level
    bool invert = false;              ///< Invert binary mask (true = detect dark objects)

    // --- Stage 3: ROI & Scaling ---
    bool enable_roi = false;          ///< Enable Region of Interest cropping
    uint16_t roi_x = 0;               ///< ROI start X
    uint16_t roi_y = 0;               ///< ROI start Y
    uint16_t roi_w = 0;               ///< ROI width
    uint16_t roi_h = 0;               ///< ROI height
    uint8_t downsample_factor = 1;    ///< 1 = native, 2 = 1/2 size, 4 = 1/4 size

    // --- Stage 4: Analysis ---
    bool enable_blob_detection = false; ///< Enable connected component analysis
    uint32_t min_blob_area = 10;        ///< Minimum pixels for a valid blob
};

/**
 * @brief Main pipeline class for processing camera frames.
 *
 * This class manages its own working buffer in PSRAM to avoid modifying
 * the original camera framebuffer (zero-copy when possible, but distinct
 * buffers are needed for destructive operations like thresholding).
 */
class CvPipeline {
public:
    CvPipeline();
    ~CvPipeline();

    /**
     * @brief Update the pipeline configuration.
     * @param config The new configuration settings.
     */
    void configure(const PipelineConfig& config);

    /**
     * @brief Execute the pipeline on a captured frame.
     * @param frame Pointer to the raw ESP camera framebuffer.
     */
    void process(camera_fb_t* frame);

    /**
     * @brief Get the processed binary or grayscale buffer.
     * @return Pointer to the internal working buffer.
     */
    const uint8_t* getOutput() const { return m_out_buffer; }

    /**
     * @brief Get the list of blobs detected in the last frame.
     * @return Vector of detected Blob objects.
     */
    const std::vector<Blob>& getBlobs() const { return m_blobs; }

    // Getters for current effective dimensions
    size_t getWidth() const { return m_width; }
    size_t getHeight() const { return m_height; }

private:
    PipelineConfig m_config;

    uint8_t* m_out_buffer = nullptr;
    size_t m_buffer_alloc_size = 0;

    // Working dimensions (may change due to ROI/Scaling)
    size_t m_width = 0;
    size_t m_height = 0;

    std::vector<Blob> m_blobs;

    // Internal Stages
    void convertGrayscale(const camera_fb_t* fb);
    void applyROI();
    void applyDownsample();
    void applyThreshold();
    void runBlobDetection();
};