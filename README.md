Here’s your **updated README** with everything integrated (including the `designs/` folder mention and calibration guide reference):

---

# Glove Integrity Testing System (GITS)

**Arduino-Based Pressure Decay Leak Detector**

[![Arduino](https://img.shields.io/badge/Made%20With-Arduino-blue?logo=arduino)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](./LICENSE)
[![Status](https://img.shields.io/badge/Status-Prototype-orange)]()
[![PRs Welcome](https://img.shields.io/badge/PRs-Welcome-brightgreen)]()

A **reliable, low-cost** system for testing glove integrity by measuring **pressure decay**.
Designed for **medical, laboratory, and industrial applications**.

---

## 📖 Overview

This project automates glove leak detection by:

* **Pressurizing the glove** with an air pump.
* **Monitoring pressure stability** using a high-resolution sensor.
* **Evaluating leaks** against a configurable threshold (**FAIL** if pressure drops excessively).
* **Providing visual feedback** via LEDs + LCD.
* **Safely deflating** after the test.

---

## 🛠 Hardware Components

| Component                | Purpose                         |
| ------------------------ | ------------------------------- |
| **Arduino UNO**          | Control unit for logic & I/O    |
| **MPS20N0040D + HX710B** | High-resolution pressure sensor |
| **12V Air Pump**         | Inflates the glove              |
| **6V Solenoid Valve**    | Releases air post-test          |
| **L298N Motor Driver**   | Drives pump & valve             |
| **16x2 I2C LCD**         | Displays real-time pressure     |
| **Tactile Button**       | Starts the test cycle           |
| **Red/Green LEDs**       | Pass/Fail indicators            |

**See detailed wiring in [`docs/wiring_diagram.png`](./docs/wiring_diagram.png).**

---

## ✨ Key Features

* **Automated Testing** – Single-button operation.
* **Real-Time Monitoring** – Pressure displayed on LCD.
* **Configurable Thresholds** – Adjustable pass/fail criteria.
* **Safety** – Auto-deflation prevents over-pressurization.
* **Serial Output** – For debugging and data logging.

---

## 🔧 Setup Instructions

### 1. Hardware Assembly

1. Connect all components as shown in the [wiring diagram](./docs/wiring_diagram.png).
2. Ensure an **airtight glove attachment** (e.g., use a 3D-printed adapter from the `designs/` folder).

### 2. Software

1. Open `GITS.ino` in Arduino IDE.
2. Upload it to your Arduino UNO.
3. Calibrate the sensor by following steps in [`docs/Calibration.md`](./docs/Calibration.md).

### 3. Operation

1. **Press the button** to start a test.
2. **Monitor the LCD** for real-time pressure.
3. **Pass/Fail** will be indicated by LEDs and on the screen.

---

## 📷 Images

![Prototype Setup](./assets/setup.jpg)
*Figure 1: Prototype with pump, Arduino, and LCD.*

![Sensor Close-up](./assets/sensor_closeup.jpg)
*Figure 2: Pressure sensor and valve wiring.*

---

## 🚀 Future Improvements

* **Enclosure Design** – 3D-printed case for portability.
* **Data Logging** – Export test results to SD card.
* **User Threshold Adjustments** – Via onboard potentiometer.
* **Quieter Pump** – For medical/lab environments.
* **ROS2 Integration** – For remote monitoring and control.

---

## 📁 Project Structure

```
GITS/
├── GITS.ino                # Main Arduino code
├── README.md               # Project documentation
├── LICENSE                 # License file
├── docs/
│   ├── wiring_diagram.png  # Wiring diagram
│   ├── Calibration.md      # Sensor calibration guide
├── assets/
│   ├── setup.jpg           # Prototype photo
│   ├── sensor_closeup.jpg  # Sensor wiring photo
├── designs/                # 3D models for chassis & adapters
│   ├── chassis.stl
│   ├── glove_adapter.stl
└── extras/
    ├── notes.txt           # Development notes
```

---

## 📄 License

This project is licensed under the **MIT License**. See [`LICENSE`](./LICENSE) for details.

---

## 👤 Author

**Hatim Ahmed Hassan** – 2025
For questions or collaboration, open an issue or contact **[xayari229@gmail.com](mailto:xayari229@gmail.com)**.

---
