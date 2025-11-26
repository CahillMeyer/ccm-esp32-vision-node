/**
 * @file main.cpp
 * @brief Application Entry Point for CCM ESP32 Vision Node.
 *
 * Orchestrates CameraNode capture, CvPipeline processing, and System Settings.
 *
 * @author CCM Code (Christie Cahill Meyer)
 * @date 2025
 * @copyright MIT License
 */

#include <esp_log.h>
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <atomic>
#include "esp_app_desc.h"

#include "CameraNode.hpp"
#include "CvPipeline.hpp"
#include "Settings.hpp"

static const char* TAG = "ccm-vision";

// Control flag for the main application loop.
static std::atomic<bool> g_is_running(true);

extern "C" void app_main()
{
    // Retrieve the version baked into the binary header by CMake
    const esp_app_desc_t* app_desc = esp_app_get_description();
    
    ESP_LOGI(TAG, "Starting CCM ESP32 Vision Node (v%s)", app_desc->version);
    ESP_LOGI(TAG, "Compile Date: %s | Time: %s", app_desc->date, app_desc->time);

    // --- 1. Load Settings (NVS) ---
    if (Settings::get().init() != ESP_OK) {
        ESP_LOGE(TAG, "Critical Failure: Settings init failed");
        return;
    }

    // --- 2. Hardware Initialization ---
    CameraNode camera;
    if (!camera.init()) {
        ESP_LOGE(TAG, "Camera initialization failed. System halted.");
        return;
    }

    // --- 3. Pipeline Configuration ---
    CvPipeline pipeline;
    
    // Apply the loaded configuration from NVS
    pipeline.configure(Settings::get().cfg());
    ESP_LOGI(TAG, "Pipeline configured from NVS settings");

    // --- 4. Main Capture Loop ---
    int64_t last_log_time = esp_timer_get_time();
    int frame_count = 0;

    while (g_is_running)
    {
        // A. Capture
        auto* fb = camera.capture();
        if (!fb) {
            ESP_LOGE(TAG, "Frame capture failed");
            vTaskDelay(pdMS_TO_TICKS(100)); // Prevent tight loop on error
            continue;
        }

        // B. Process
        int64_t start_proc = esp_timer_get_time();
        pipeline.process(fb);
        int64_t end_proc = esp_timer_get_time();

        // C. Release
        camera.release(fb);

        // D. Telemetry & Results
        frame_count++;
        
        // Check for detections
        const auto& blobs = pipeline.getBlobs();
        if (!blobs.empty()) {
            const auto& b = blobs[0];
            ESP_LOGD(TAG, "Blob Detected: Area=%u Center=(%u, %u)", b.area, b.cx, b.cy);
        }

        // Periodic Performance Logging
        if (frame_count % 50 == 0) {
            int64_t now = esp_timer_get_time();
            float fps = 50.0f / ((now - last_log_time) / 1000000.0f);
            int64_t proc_ms = (end_proc - start_proc) / 1000;

            ESP_LOGI(TAG, "FPS: %.2f | Proc Time: %lld ms | Blobs: %u | Output: %ux%u", 
                     fps, proc_ms, blobs.size(), pipeline.getWidth(), pipeline.getHeight());
            
            last_log_time = now;
            frame_count = 0;
        }

        // Yield to watchdog
        vTaskDelay(1); 
    }

    ESP_LOGI(TAG, "Application stopped.");
}