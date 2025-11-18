# ccm-esp32-vision-node

Embedded camera node for ESP32-S3 / ESP32-CAM with real-time computer vision processing.

> Work-in-progress project showcasing embedded vision firmware engineering:
> camera bring-up, lightweight CV algorithms, and streaming from constrained hardware.

---

## Goals

This repo is a **practical example of embedded computer vision on microcontrollers**:

- Bring up common ESP32 camera modules (ESP32-CAM, ESP32-S3 with OV2640/OV5640).
- Run **lightweight CV** on-device:
  - color blob detection
  - thresholding / masking
  - ROI cropping
- Stream frames and detection metadata over **Wi-Fi or serial**.
- Measure and document **FPS, latency, and memory usage** under tight constraints.

It is designed both as:

- A **portfolio project** for embedded CV consulting work.
- A **starting point** for client projects that need ESP32-based smart cameras or IoT vision nodes.

---

## Features (planned)

- ✅ ESP32-S3 / ESP32-CAM camera bring-up (ESP-IDF)
- ✅ Configurable resolution and frame rate
- ⏳ Simple HSV color blob detector
- ⏳ ROI cropper with downsampling
- ⏳ Wi-Fi streaming endpoint (MJPEG or raw frames)
- ⏳ UART debug + statistics (FPS, heap, stack)
- ⏳ Benchmark suite for different resolutions / algorithms

---

## Tech Stack

- **Language:** C / C++
- **Platform:** ESP32-S3, ESP32-CAM
- **Framework:** ESP-IDF
- **Tooling:** CMake, idf.py

---

## Repository Layout (planned)

```
firmware/
  main/
    app_main.c
    camera_config.cpp
    cv_pipeline.cpp
    stream_server.cpp
  components/
    drivers/
    utils/
docs/
  architecture.md
  benchmarks.md
examples/
  color_blob_tracking/
  roi_cropping/
```

---

## Getting Started

1. **Install ESP-IDF**
2. **Clone repo**

```
git clone https://github.com/CahillMeyer/ccm-esp32-vision-node.git
cd ccm-esp32-vision-node/firmware
```

3. **Configure**

```
idf.py set-target esp32s3
idf.py menuconfig
```

4. **Build & flash**

```
idf.py build
idf.py flash monitor
```

---

## Roadmap

- [ ] Minimal camera demo
- [ ] Color blob detector
- [ ] Wi-Fi streaming
- [ ] ROI + downsampling
- [ ] Benchmarks
- [ ] Example object tracker

---

## License

MIT License

---

## Contact  
**Cahill Meyer** – Embedded Vision Engineer  
GitHub: https://github.com/CahillMeyer
