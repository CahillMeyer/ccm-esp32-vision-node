// main.cpp
// Entry point for the CCM ESP32 Vision Node firmware.
//
// This module wires together the high-level components:
//  - CameraNode: frame acquisition
//  - CvPipeline: image processing (WIP)
//  - StreamServer: Wi-Fi streaming (planned)
// and runs the main frame loop.

#include <esp_log.h>
#include <esp_timer.h>
#include "CameraNode.hpp"

static const char* TAG = "ccm-vision";

/// @brief ESP-IDF application entry point.
///
/// For now this runs a simple capture loop and logs FPS.
/// As CvPipeline and StreamServer mature, this will evolve into a
/// full vision processing pipeline.
extern "C" void app_main()
{
    ESP_LOGI(TAG, "Starting CCM ESP32 Vision Node (C++)");

    CameraNode camera;
    if (!camera.init()) {
        ESP_LOGE(TAG, "Camera initialization failed");
        return;
    }

    int64_t last = esp_timer_get_time();

    while (true)
    {
        auto* fb = camera.capture();
        if (!fb) {
            ESP_LOGE(TAG, "Failed to capture frame");
            continue;
        }

        camera.release(fb);

        int64_t now = esp_timer_get_time();
        float fps = 1e6f / (now - last);
        last = now;

        ESP_LOGI(TAG, "FPS: %.2f", fps);
    }
}
