#include <iostream>
#include <vector>
#include <cstring>
#include <inttypes.h> // For PRId64
#include "CvPipeline.hpp"
#include "esp_log.h"
#include "esp_timer.h"

// Helper: Generate a test pattern (White square on black background)
// Simulates the raw sensor data (QVGA 320x240)
void generateTestPattern(camera_fb_t* fb, int x, int y, int w, int h) {
    memset(fb->buf, 0, fb->len); // Clear to black
    
    uint16_t* pixels = (uint16_t*)fb->buf;
    for(int j = y; j < y + h; j++) {
        for(int i = x; i < x + w; i++) {
            if(i >= 0 && i < (int)fb->width && j >= 0 && j < (int)fb->height) {
                pixels[j * fb->width + i] = 0xFFFF; // White
            }
        }
    }
}

int main() {
    printf("--- CCM Simulation: ROI & Downsample Test ---\n");

    // 1. Setup Mock Camera Frame (Native Sensor Resolution: 320x240)
    camera_fb_t fb;
    fb.width = 320;
    fb.height = 240;
    fb.format = PIXFORMAT_RGB565;
    fb.len = fb.width * fb.height * 2;
    fb.buf = (uint8_t*)malloc(fb.len);

    // 2. Configure Pipeline with Advanced Features
    CvPipeline pipeline;
    PipelineConfig config;
    
    // Basic detection
    config.enable_grayscale = true;
    config.enable_threshold = true;
    config.threshold_val = 100;
    config.enable_blob_detection = true;
    config.min_blob_area = 20; // Lower area threshold since blob will shrink

    // --- TEST: Region of Interest (ROI) ---
    // We only look at the CENTER of the image (x=80 to x=240)
    config.enable_roi = true;
    config.roi_x = 80;
    config.roi_y = 60;
    config.roi_w = 160;
    config.roi_h = 120;

    // --- TEST: Downsampling ---
    // Shrink the cropped area by 2x.
    // Expected Output Size: 160/2 x 120/2 = 80x60
    config.downsample_factor = 2;

    pipeline.configure(config);

    // 3. Simulation Loop
    // We move the object from X=40 (Left) to X=240 (Right)
    // The ROI starts at X=80. 
    // EXPECTATION: 
    //  - Frames 0-1: Object is at X=40, X=60. Outside ROI. -> NO DETECTION
    //  - Frames 2+:  Object enters X=80. -> DETECTION STARTS
    //  - Coordinates: Should be relative to the 80x60 buffer.

    for (int i = 0; i < 11; i++) {
        int blobRawX = 40 + (i * 20); // Move 20px right each frame
        
        // Draw the blob on the "Sensor"
        generateTestPattern(&fb, blobRawX, 100, 40, 40);

        // Run Pipeline
        int64_t start = esp_timer_get_time();
        pipeline.process(&fb);
        int64_t end = esp_timer_get_time();

        const auto& blobs = pipeline.getBlobs();
        
        // Print Status
        // Note: Using %zu for size_t and cast for timer to ensure portability
        printf("[Frame %2d] RawX=%-3d | Output Res: %zux%zu | Blobs: %zu", 
               i, blobRawX, pipeline.getWidth(), pipeline.getHeight(), blobs.size());

        if (!blobs.empty()) {
            // Because we cropped X=80 and Downsampled 2x:
            // Expected X = (RawX - 80) / 2
            printf(" -> Det at: x=%d, y=%d (w=%d h=%d)", 
                   blobs[0].x, blobs[0].y, blobs[0].w, blobs[0].h);
        } else {
            printf(" -> (Outside ROI)");
        }
        printf("\n");
    }

    free(fb.buf);
    return 0;
}