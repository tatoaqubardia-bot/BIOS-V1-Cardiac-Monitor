# BIOS-V1 | Cardiac Monitor & Bio-Simulator

Overview
BIOS-V1 is an ultra-low-power cardiac monitoring system written in C++. Unlike standard monitors, this project integrates Physical Constraints (Battery life) and Biological Safety (Thermal limits) directly into the software logic.

This was built to explore the intersection of Software Engineering and Medical Technology.

 Key Features

### 1. High-Efficiency Observation ($O(1)$)
Uses a `std::deque` sliding window to process heartbeats in **Constant Time**. This ensures the CPU never spikes, which is a mechanical necessity for embedded medical implants.

### 2. Battery Longevity Prediction (Physics)
Includes a `MedicalSystem` structure that tracks energy consumption in **Joules**. It predicts the remaining lifespan of the device (in years) based on the user's current heart rate and metabolic load.

### 3. Thermal Safety Guard (Biology)
Implements a simulated feedback loop that monitors chip temperature. If the processing load causes the temperature to exceed **42°C**, the system triggers a mandatory shutdown to prevent tissue damage (protein denaturation).

## Technical Details
- **Language:** C++17
- **Data Structures:** `std::deque` for time-efficient windowing.
- **Complexity:** $O(1)$ per heartbeat.
- **Hardware Profile:** Simulated CR2032 Lithium Coin Cell (2430 Joules).

How to Run
1. Clone the repository.
2. Compile using any C++ compiler:
   ```bash
   g++ -o BIOS_V1 main.cpp
