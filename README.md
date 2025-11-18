# ccm-esp32-vision-node

![ESP-IDF](https://img.shields.io/badge/ESP--IDF-C%2B%2B%20project-orange)
![Platform](https://img.shields.io/badge/Platform-ESP32--S3-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B17-purple)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

Embedded camera node for **ESP32-S3** with a modular C++ architecture for real-time computer vision.
This project demonstrates professional embedded CV engineering: camera bring-up, modular pipelines,
and efficient processing on low-power microcontrollers.

> **Work-in-progress**: This repository is part of the CCMCode Embedded Vision toolkit and serves as
> a portfolio-quality example of modern ESP-IDF C++ development.

---

## 🚀 Features (Current & Planned)

### ✅ Implemented
- ESP-IDF C++ project with multi-component architecture (`camera_node`, `cv_pipeline`, `stream_server`, `utils`, `drivers`)
- Fully compiling project with ESP32-S3 target under WSL Ubuntu
- C++ `CameraNode` component using the `esp32-camera` managed component
- Real-time FPS measurement with `esp_timer`

### 🛠 In Progress
- C++ computer vision pipeline (`cv_pipeline`)
- Frame timing and lightweight profiling utilities
- Clean, extensible class-based architecture for embedded CV

### 📌 Planned
- Color blob detector (HSV thresholding)
- ROI extraction + simple pre-processing steps
- MJPEG or raw frame Wi-Fi streaming server
- UART debug dashboard (FPS, memory, timings)
- Benchmarks across frame sizes & pixel formats
- Example: simple color-object tracker

---

## 🧱 Project Architecture
For a detailed component diagram and explanation, see [docs/architecture.md](docs/architecture.md).

```
ccm-esp32-vision-node/
│
├── components/
│   ├── camera_node/       # Camera bring-up abstraction
│   ├── cv_pipeline/       # Modular image processing pipeline (WIP)
│   ├── stream_server/     # Wi-Fi streaming endpoint (planned)
│   ├── drivers/           # Camera/sensor-specific helpers
│   └── utils/             # Logging, timers, profiling
│
├── firmware/
│   ├── main/              # App entry point (main.cpp)
│   └── CMakeLists.txt     # ESP-IDF project definition
│
├── docs/                  # Architecture & benchmarks (planned)
└── examples/              # Sample demos (planned)
```

---

## 🧪 Tested / Target Environment

This project is being developed and tested with:

- **Chip:** ESP32-S3
- **SDK:** ESP-IDF (Linux / WSL)
- **Host environment:** Windows 10 + WSL Ubuntu
- **Tooling:** VS Code, `idf.py`, CMake

Planned hardware targets include:

- ESP32-S3 dev boards with PSRAM
- Camera modules based on OV2640 / OV5640

---

## 🖥️ Getting Started (ESP-IDF)

### 1. Install ESP-IDF

Follow the official install instructions:
https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/

### 2. Clone the repository

```bash
git clone https://github.com/CahillMeyer/ccm-esp32-vision-node.git
cd ccm-esp32-vision-node/firmware
```

### 3. Configure the target

```bash
idf.py set-target esp32s3
idf.py menuconfig
```

### 4. Build & flash

```bash
idf.py build
idf.py flash monitor
```

---

## 📊 Status

This project successfully:
- builds under **WSL Ubuntu**
- uses the **esp32-camera** managed component
- compiles a fully working **C++ main loop**
- initializes and reads from the camera
- produces frame timing (FPS) logs

Next steps will add actual image-processing functionality.

---

## 🗺️ Roadmap

- [ ] Add CvPipeline grayscale + threshold stage
- [ ] Add frame buffer pre-processing (ROI, downsample)
- [ ] Add MJPEG Wi-Fi streaming server
- [ ] Add architecture diagrams
- [ ] Add host-side unit tests for pipeline components
- [ ] Add example demos (color tracking, region extraction)

---

## 📄 License

MIT License

---

## 👤 Author

**Cahill Meyer**  
Embedded Vision Engineer  
GitHub: https://github.com/CahillMeyer
