#include <esp_log.h>
#include <esp_timer.h>
#include "CameraNode.hpp"

static const char* TAG = "ccm-vision";

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
