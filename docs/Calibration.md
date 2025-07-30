# Sensor Calibration Guide for GITS

This document explains how to calibrate the **MPS20N0040D + HX710B** pressure sensor for the Glove Integrity Testing System (GITS).

---

## Why Calibrate?
The sensor’s raw readings (in ADC counts) need to be mapped to **pressure values in kPa**.  
Calibration ensures accuracy for pass/fail testing.

---

## Requirements
- Arduino UNO with uploaded `GITS.ino` firmware  
- Serial Monitor (Arduino IDE)  
- A hand pump or syringe for applying known pressures  
- A reference pressure gauge (optional but recommended)

---

## Steps

### 1. Enable Calibration Mode
1. Open `GITS.ino` in Arduino IDE.
2. Locate this line:
   ```cpp
   #define CALIBRATION_MODE false
