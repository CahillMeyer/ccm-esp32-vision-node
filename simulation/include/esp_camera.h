#pragma once
#include <cstdint>
#include <cstddef>

// Mock Pixel Formats
typedef enum {
    PIXFORMAT_RGB565,
    PIXFORMAT_GRAYSCALE,
    PIXFORMAT_JPEG
} pixformat_t;

// Mock Framebuffer Struct
typedef struct {
    uint8_t * buf;
    size_t len;
    size_t width;
    size_t height;
    pixformat_t format;
} camera_fb_t;