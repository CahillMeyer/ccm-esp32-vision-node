#pragma once
#include "esp_camera.h"

/// @brief Planned component for exposing frames over Wi-Fi.
///
/// StreamServer will eventually provide:
///  - An HTTP endpoint for MJPEG streaming
///  - A lightweight status/metrics endpoint
///  - Optional raw frame or metadata streaming for debugging.
///
/// For now, this component is a placeholder to show the intended
/// architecture and responsibilities.
class StreamServer {
public:
    StreamServer() = default;

    /// @brief Initialize networking and prepare streaming endpoints.
    bool init();

    /// @brief Push a processed frame to any active stream clients.
    void pushFrame(const camera_fb_t* frame);
};
