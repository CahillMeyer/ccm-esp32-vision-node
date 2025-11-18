#pragma once
#include "esp_camera.h"

class CameraNode {
public:
    CameraNode() = default;
    bool init();
    camera_fb_t* capture();
    void release(camera_fb_t* fb);
};
