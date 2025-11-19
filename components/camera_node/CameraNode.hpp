#pragma once
#include "esp_camera.h"

/// @brief High-level wrapper around the ESP32-S3 camera interface.
///
/// CameraNode is responsible for:
///  - Configuring the camera pins and basic sensor options
///  - Initializing the esp32-camera driver
///  - Acquiring and releasing frame buffers
///
/// This component hides the raw esp32-camera API behind a small C++ class
/// so it can be reused in different applications and pipelines.
class CameraNode {
public:
    CameraNode() = default;
    
    /// @brief Initialize the camera hardware and driver.
    /// @return true on success, false if initialization fails.
    bool init();
    
    /// @brief Capture a frame from the camera.
    /// @return Pointer to frame buffer, or nullptr on failure.
    camera_fb_t* capture();
    
    /// @brief Return a previously captured frame buffer to the driver.
    void release(camera_fb_t* fb);
};
