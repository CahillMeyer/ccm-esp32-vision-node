# Basic FPS Logger Example

This example provides the minimal working demonstration of the **CCM ESP32 Vision Node**:

- Initialize the ESP32-S3 camera
- Capture frames in a loop
- Measure and log frames-per-second (FPS)
- Validate hardware, PSRAM, and camera configuration

It serves as the baseline sanity check before adding any image-processing stages.

---

## Who This Example Is For

- Embedded developers bringing up ESP32-S3 camera hardware
- Robotics / IoT engineers running a small smart-camera node
- Engineering leads evaluating CCM Code’s firmware structure
- Anyone validating that their board + camera module is wired and configured correctly

---

## Hardware Requirements

Recommended and tested target:

- ESP32-S3 dev board with PSRAM
- Camera module:
  - OV2640
  - OV5640
- Example boards:
  - Seeed XIAO ESP32-S3 Sense
  - ESP32-S3-EYE
  - AI-Thinker ESP32-S3-CAM

Required tools:

- USB cable
- ESP-IDF v5 or newer
- Serial monitor (`idf.py monitor` or VS Code ESP-IDF extension)

---

## How to Build & Run

From the repository root:

```bash
cd firmware
idf.py set-target esp32s3
idf.py menuconfig      # configure serial port and camera pins if needed
idf.py build
idf.py flash monitor
```

This example is the default firmware entry point (`firmware/main/main.cpp`).
If additional examples are added later, use a compile-time switch or Kconfig option to select them.

---

## Expected Serial Output

If everything is configured correctly, you should see logs similar to:

```text
I (200) camera_node: Camera initialized: 320x240, PIXFORMAT_RGB565
I (210) main: Starting capture loop...
I (1210) main: Frame 100, avg FPS = 28.7, min = 26.4, max = 30.1
I (2210) main: Frame 200, avg FPS = 28.9, min = 26.2, max = 30.3
```

This verifies:

- Proper camera pin configuration
- PSRAM buffers are stable
- Frame acquisition loop is running
- Timing metrics are correct

If you see camera initialization errors, re-check:

- Pin assignments
- PSRAM stability in `menuconfig`
- Sensor module orientation

---

## What to Try Next

After FPS logging works:

- Increase resolution and compare FPS
- Enable grayscale or early `CvPipeline` stages
- Add logging of per-stage timings
- Move toward blob detection and MJPEG streaming

The FPS logger is intentionally simple — it is your reference baseline as the vision node grows.

---

## File Structure

```text
examples/
└── basic_fps_logger/
    ├── README.md       <-- this file
    └── (future) CMakeLists.txt or example-specific config
```

Additional example variants (blob detection, ROI cropping, streaming) will live beside this one.
