// CvPipeline.cpp
// Lightweight, modular image processing pipeline.
//
// TODO:
//  - Implement first stage: grayscale + optional threshold.
//  - Add simple configuration struct for enabling/disabling stages.
//  - Add lightweight profiling hooks to measure per-stage timings.

#include "CvPipeline.hpp"
#include <esp_log.h>

static const char* TAG = "CvPipeline";

void CvPipeline::process(camera_fb_t* frame)
{
    // Placeholder implementation – will be extended with real stages.
    (void)frame;
    ESP_LOGV(TAG, "CvPipeline::process() called (no-op)");
}
