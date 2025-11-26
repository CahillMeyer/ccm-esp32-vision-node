# Contributing to ccm-esp32-vision-node

Thank you for your interest in contributing!  
This project is part of the **CCM Code Embedded Vision Toolkit**, and follows a clean, modular C++ architecture for ESP-IDF development.  
To maintain consistency and reliability, please follow the guidelines below.

---

## 📐 Project Philosophy

This repository is designed to demonstrate:
- High‑quality embedded C++ design  
- Clear architectural separation (`camera_node`, `cv_pipeline`, `drivers`, `utils`)  
- Professional build workflows and maintainability  
- Production‑ready ESP-IDF patterns

Contributions should preserve clarity, correctness, and modularity.

---

## 🧰 Development Environment

### Required:
- **ESP-IDF v5.0+**
- **ESP32-S3** dev board with PSRAM
- **CMake** and **Ninja** (installed with ESP-IDF)
- **Python 3.8+**
- WSL, macOS, or Linux recommended

To set up ESP-IDF:
https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/

---

## 📁 Repository Structure

```
components/
  camera_node/
  cv_pipeline/
  drivers/
  stream_server/   # planned
  utils/

firmware/
  main/            # main.cpp application entry point

examples/
  basic_fps_logger/

docs/
  architecture.md
  media/
```

---

## 📝 Code Style

### C++
- Use **C++17**.
- Follow ESP-IDF's formatting conventions.
- Prefer **header-only utilities** for simple helpers.
- Use **RAII**, avoid raw pointers when possible.
- Use `constexpr`, `enum class`, and `struct` for clarity.
- Keep all component APIs clean, minimal, and consistent.

### Formatting
A `clang-format` configuration is planned but not required yet.  
Until then:

- 4‑space indentation  
- No trailing whitespace  
- Consistent brace style (K&R)  
- Use descriptive naming (`CameraNode`, `CvPipeline`, `FrameBuffer`)  

---

## 🧪 Testing

### Before submitting a PR:
1. **Hardware Test:**
   - Ensure the project builds: `idf.py build`
   - Test on ESP32-S3 if available.

2. **Simulation Test (Recommended):**
   - If modifying `cv_pipeline` logic, verify it on the host simulator:
     ```bash
     cd simulation
     cmake . && make
     ./vision_sim
     ```
   - Ensure ROI and Blob logic holds up against the test pattern.

---

## 🔀 Pull Request Process

1. **Open an issue first**  
   Describe the feature, fix, or enhancement you want to add.

2. **Create a feature branch**
   ```bash
   git checkout -b feature/your-change
   ```

3. **Keep commits clean and logical**  
   Squash commits if appropriate.

4. **Ensure the project still builds**
   ```bash
   idf.py build
   ```

5. **Submit a PR**  
   Include:
   - What the change does  
   - Why it’s needed  
   - Hardware used for testing  
   - Any screenshots or logs  

6. **Review Process**  
   PRs will be reviewed for:
   - Correctness  
   - Code clarity  
   - Alignment with project architecture  
   - Maintainability  

---

## 🧭 Component Contribution Guidelines

### `camera_node`
- Avoid board-specific logic.
- Use `camera_config_t` cleanly.
- Ensure frame buffers are safely returned.

### `cv_pipeline`
- All stages must be stateless or self-contained.
- Minimize RAM usage.
- Add timing hooks using `esp_timer`.

### `drivers`
- Add new camera or board-specific helpers here.
- Clearly document pin mappings.

### `utils`
- Only lightweight helpers (timing, logging).
- Keep dependencies minimal.

---

## 🌱 Adding New Examples

Examples should live under:

```
examples/<example_name>/
```

Each example must include:
- `README.md`
- Clear build/run instructions
- Expected output
- Purpose of the example

---

## 📄 License

By contributing, you agree that your contributions will be licensed under the **MIT License**.

---

## 🙌 Thanks

Thank you for helping improve the CCM Code Embedded Vision Toolkit!  
Your contributions make this a stronger, more professional embedded vision reference.
