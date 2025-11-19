#pragma once
#include "esp_camera.h"

/// @brief Simple image processing pipeline for camera frames.
///
/// CvPipeline is designed to be a lightweight, modular processing chain
/// that can be extended with small "stages" such as:
///  - grayscale conversion
///  - thresholding / masking
///  - ROI extraction / downsampling
///  - basic blob detection
///
/// The initial implementation focuses on clarity and testability rather
/// than heavy optimization, making it suitable as a teaching/reference
/// pipeline for embedded CV work.
class CvPipeline {
public:
    CvPipeline() = default;

    /// @brief Process a captured frame in-place or using an internal buffer.
    ///
    /// For now this function will be a stub / no-op until stages are added.
    void process(camera_fb_t* frame);
};
