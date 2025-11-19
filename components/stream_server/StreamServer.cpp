// StreamServer.cpp
// Placeholder for future MJPEG / HTTP streaming server.
//
// TODO:
//  - Implement basic HTTP server using ESP-IDF httpd component.
//  - Expose MJPEG stream endpoint for live preview.
//  - Expose simple JSON status endpoint (FPS, heap usage, etc.).

#include "StreamServer.hpp"
#include <esp_log.h>

static const char* TAG = "StreamServer";

bool StreamServer::init()
{
    ESP_LOGW(TAG, "StreamServer not implemented yet");
    return true;
}

void StreamServer::pushFrame(const camera_fb_t* frame)
{
    (void)frame;
    // Future: push frame to stream clients.
}
