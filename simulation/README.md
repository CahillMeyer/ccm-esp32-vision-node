cat <<EOF > simulation/README.md
# Host-Based Vision Simulator

This tool allows you to run and debug the **CvPipeline** logic on a PC (WSL/Linux) without needing physical ESP32 hardware.

It "mocks" the ESP32-specific headers (camera, logging, timing) and feeds generated test patterns into the pipeline.

## 🚀 Purpose
- **Rapid Prototyping:** Test new algorithms (blob detection, thresholding) instantly.
- **Logic Verification:** Validate ROI math and coordinate transformations.
- **Performance Baseline:** Measure raw algorithmic overhead (ignoring hardware I/O).

## 🛠 How to Build & Run

### Prerequisites
- CMake
- G++ / GCC
- Linux environment (or WSL)

### Commands
\`\`\`bash
cd simulation
cmake .
make
./vision_sim
\`\`\`

## 🧪 Current Tests
The \`SimMain.cpp\` currently validates:
1. **ROI Extraction:** Ensures objects outside the crop zone are ignored.
2. **Downsampling:** Verifies 2x scaling logic (320x240 -> 80x60).
3. **Blob Detection:** Tracking a moving white square across the frame.

## 📂 Structure
- \`SimMain.cpp\`: Entry point; generates fake frames and calls the pipeline.
- \`include/\`: Mock headers (\`esp_camera.h\`, \`esp_log.h\`, etc.).
- \`CMakeLists.txt\`: Standard desktop build configuration.

EOF