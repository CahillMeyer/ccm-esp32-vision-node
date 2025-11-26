#pragma once
#include <chrono>

inline int64_t esp_timer_get_time() {
    // Return microseconds since epoch
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(
        now.time_since_epoch()).count();
}