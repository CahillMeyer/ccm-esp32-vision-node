#include "CameraNode.hpp"
#include <esp_log.h>
#include <cstring>

static const char* TAG = "CameraNode";

bool CameraNode::init()
{
    camera_config_t config = {};

     // TODO: adjust these pins to actual board layout
    config.pin_pwdn     = -1;
    config.pin_reset    = -1;
    config.pin_xclk     = 10;
    config.pin_sccb_sda = 40;
    config.pin_sccb_scl = 39;
    config.pin_d7       = 48;
    config.pin_d6       = 47;
    config.pin_d5       = 21;
    config.pin_d4       = 14;
    config.pin_d3       = 13;
    config.pin_d2       = 12;
    config.pin_d1       = 11;
    config.pin_d0       = 9;
    config.pin_vsync    = 38;
    config.pin_href     = 42;
    config.pin_pclk     = 8;

    config.xclk_freq_hz = 20'000'000;
    config.ledc_timer   = LEDC_TIMER_0;
    config.ledc_channel = LEDC_CHANNEL_0;

    config.pixel_format = PIXFORMAT_JPEG;     // good for streaming
    config.frame_size   = FRAMESIZE_QVGA;     // 320x240 to start
    config.jpeg_quality = 12;
    config.fb_count     = 1;

    // Newer fields in camera_config_t – set explicitly
    config.grab_mode    = CAMERA_GRAB_WHEN_EMPTY;
#ifdef CONFIG_SPIRAM
    config.fb_location  = CAMERA_FB_IN_PSRAM;
#else
    config.fb_location  = CAMERA_FB_IN_DRAM;
#endif
    config.sccb_i2c_port = 0;  // default I2C port for SCCB

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_camera_init failed: %s", esp_err_to_name(err));
        return false;
    }

    ESP_LOGI(TAG, "Camera initialized");
    return true;
}

camera_fb_t* CameraNode::capture()
{
    return esp_camera_fb_get();
}

void CameraNode::release(camera_fb_t* fb)
{
    esp_camera_fb_return(fb);
}
