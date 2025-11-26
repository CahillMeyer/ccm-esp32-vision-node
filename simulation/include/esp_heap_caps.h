#pragma once
#include <cstdlib>

// Map ESP32-specific memory allocation to standard malloc
#define MALLOC_CAP_SPIRAM 0
#define MALLOC_CAP_8BIT 0

inline void* heap_caps_malloc(size_t size, uint32_t caps) {
    return malloc(size);
}

inline void heap_caps_free(void* ptr) {
    free(ptr);
}