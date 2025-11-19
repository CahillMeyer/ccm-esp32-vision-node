#pragma once
#include <stdint.h>

/// @brief Helper for measuring frame-to-frame timing and FPS.
///
/// FrameTimer wraps esp_timer so that the main loop can print human-readable
/// FPS values without cluttering application logic.
class FrameTimer {
public:
    FrameTimer();

    /// @brief Mark the beginning of a new frame and compute FPS.
    /// @return Instantaneous frames-per-second value.
    float tick();

private:
    int64_t m_lastUs;
};
