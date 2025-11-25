#include <esp_log.h>
#include <esp_timer.h>
#include "CameraNode.hpp"

static const char* TAG = "fps_example";

extern "C" void app_main() {
    ESP_LOGI(TAG, "Starting FPS Logger Example");

    CameraNode camera;
    if (!camera.init()) {
        ESP_LOGE(TAG, "Camera init failed! Check pin definitions in CameraNode.cpp");
        return;
    }

    int64_t last_time = esp_timer_get_time();
    int frame_count = 0;

    while (true) {
        camera_fb_t* fb = camera.capture();
        if (!fb) {
            ESP_LOGE(TAG, "Frame capture failed");
            continue;
        }

        // Simulating processing time could go here
        
        camera.release(fb);
        frame_count++;

        // Log every 100 frames to keep output clean
        if (frame_count % 100 == 0) {
            int64_t now = esp_timer_get_time();
            float fps = 100.0f / ((now - last_time) / 1000000.0f);
            ESP_LOGI(TAG, "Throughput: %.2f FPS | Resolution: %ux%u", fps, fb->width, fb->height);
            last_time = now;
            frame_count = 0;
        }
    }
}