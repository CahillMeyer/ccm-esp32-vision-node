# ccm-esp32-vision-node

![ESP-IDF](https://img.shields.io/badge/ESP--IDF-C%2B%2B%20project-orange)
![Platform](https://img.shields.io/badge/Platform-ESP32--S3-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B17-purple)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
![CI](https://github.com/CahillMeyer/ccm-esp32-vision-node/actions/workflows/ci.yml/badge.svg)

Embedded camera node for **ESP32-S3** with a modular C++ architecture for real-time computer vision.
This project demonstrates professional embedded CV engineering: camera bring-up, modular pipelines,
efficient frame handling, and low‑power vision processing.

> **Work‑in‑progress:** Part of the CCM Code Embedded Vision toolkit.  
> Designed as a portfolio‑quality example of clean, modern ESP‑IDF C++ development.

---

## 🚀 Features (Current & Planned)

### ✅ Implemented
- ESP-IDF C++ project with multi-component architecture
- C++ `CameraNode` component using the `esp32-camera` managed component
- **CvPipeline** with Grayscale, ROI, Downsampling, Thresholding, and Blob Detection
- **Host-Based Simulator** (`simulation/`) for fast PC-based testing
- **Persistent Settings** using NVS (Non-Volatile Storage)
- Real-time FPS measurement and per-stage profiling

### 🛠 In Progress
- MJPEG Wi‑Fi streaming server (`stream_server`)
- Color blob detector (HSV)

### 📌 Planned
- UART debug dashboard (FPS, memory, timings)
- Example: simple color-object tracker

---

## 🧱 Project Architecture

For full component documentation, see:  
👉 `docs/architecture.md`

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
│   └── CMakeLists.txt
│
├── docs/
│   ├── architecture.md
│   └── media/             # diagrams (placeholder)
│
└── examples/
    └── basic_fps_logger/  # First working demo
```

---

## 🧪 Tested / Target Environment

Developed and tested with:

- **Chip:** ESP32-S3  
- **SDK:** ESP-IDF (Linux / WSL)  
- **Environment:** Windows 10 + WSL Ubuntu  
- **Tools:** VS Code, `idf.py`, CMake  

Validated hardware:

- ESP32-S3 dev boards with PSRAM  
- OV2640 camera modules  
- OV5640 (planned, not yet validated)

---

## 📸 Hardware Requirements

Target boards:

- ESP32-S3 dev board with PSRAM  
- Camera modules:  
  - OV2640 (supported)  
  - OV5640 (planned)

Recommended specs:

- 8 MB PSRAM  
- QVGA or VGA frame sizes for initial demos  
- Stable 5V USB power  

If using boards such as **Seeed XIAO ESP32‑S3 Sense**, adjust only `camera_config_t` in `camera_node`.

---

## 🖥️ Getting Started (ESP-IDF)

### 1. Install ESP-IDF  
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

## 📟 Example Serial Output (FPS Logger)

```text
I (0) cpu_start: Starting scheduler on PRO CPU.
I (0) main: Initialising camera...
I (250) camera_node: Camera init OK (320x240, PIXFORMAT_JPEG)
I (260) main: Captured frame 1 (size=32768 bytes)
I (270) main: FPS: 18.7
I (323) main: Captured frame 2 (size=32768 bytes)
I (333) main: FPS: 19.5
...
```

---

## 📊 Early Benchmarks (Placeholder)

| Resolution | Pixel Format | Pipeline Stages | Avg FPS | Notes |
|-----------|--------------|------------------|--------:|-------|
| 320×240   | RGB565       | None (raw)       | TBD     | Baseline |
| 320×240   | Gray         | grayscale        | TBD     | First CV test |
| 320×240   | Gray+TH      | gray+threshold   | TBD     | Planned |
| 640×480   | RGB565       | None             | TBD     | PSRAM required |
| 320×240 | Gray + Threshold | ~4.5 ms | ~28 | Host Sim |
| 320×240 | Gray + ROI + Downsample (2x) | ~1.0 ms | ~90+ | Host Sim (80x60 effective) |

Benchmarks will be updated as the pipeline matures.

---

## 🗺️ Roadmap

### Near-term
- [x] Add `cv_pipeline` grayscale + threshold stage
- [x] Add ROI cropping + reduction steps
- Add MJPEG Wi‑Fi streaming server  
- Add diagrams under `docs/media/`  

### Mid-term
- Add blob detection demo  
- Add region extraction example  
- Add JSON status endpoint  
- Add host-side tests  

### Vision
A reusable, modular **Embedded Vision Node** for ESP32-S3:  
Setup board → configure pipeline → get structured vision output via UART or Wi‑Fi.

---

## Who Is This For?

- Embedded firmware engineers exploring ESP-IDF C++ patterns  
- Robotics / IoT teams evaluating low‑power embedded vision  
- Engineering leads reviewing CCM Code’s architecture + code quality  
- Clients needing a reference implementation for ESP32‑based smart camera nodes  

---

## What Works Today (v0.1.0 – Alpha)

- ESP-IDF C++ multi-component project structure  
- Camera bring-up via `esp32-camera`  
- Continuous capture loop with real-time FPS logging  
- Builds and flashes cleanly from WSL → ESP32-S3  
- Early example demo under `examples/basic_fps_logger`  

---

## 📄 License

MIT License — see `LICENSE`.

---

## 👤 Author

**Christie Cahill Meyer**  
Embedded Vision Engineer  
GitHub: https://github.com/CahillMeyer
