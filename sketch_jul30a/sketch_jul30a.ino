#include <Arduino.h>

#define PRESSURE_DATA 2
#define PRESSURE_CLK 3
#define BUTTON_PIN 4
#define PUMP_IN1 5
#define PUMP_IN2 6
#define VALVE_IN3 7
#define VALVE_IN4 8
#define GREEN_LED 9
#define RED_LED 10

const float targetPressure = 8.0;   // Target pressure (kPa)
const float maxDrop = 0.5;         // Max allowed pressure drop (kPa)
const unsigned long holdTime = 5000; // Hold time (ms)
const unsigned long inflationTimeout = 30000; // Max inflation time (ms)

// Read raw pressure data from sensor
long readPressureRaw() {
  while (digitalRead(PRESSURE_DATA)); // Wait for data ready
  long count = 0;
  for (byte i = 0; i < 24; i++) {
    digitalWrite(PRESSURE_CLK, HIGH);
    count = count << 1;
    digitalWrite(PRESSURE_CLK, LOW);
    if (digitalRead(PRESSURE_DATA)) count++;
  }
  // Extra clock cycle
  digitalWrite(PRESSURE_CLK, HIGH);
  digitalWrite(PRESSURE_CLK, LOW);
  return count ^ 0x800000;  // Convert to signed value
}

// Convert raw pressure to kPa
float readPressureKpa() {
  return (readPressureRaw() / 16777215.0) * 40.0; // Adjust scale if needed
}

// Turn pump ON
void pumpOn() {
  digitalWrite(PUMP_IN1, HIGH);
  digitalWrite(PUMP_IN2, LOW);
}

// Turn pump OFF
void pumpOff() {
  digitalWrite(PUMP_IN1, LOW);
  digitalWrite(PUMP_IN2, LOW);
}

// Open solenoid (hold air)
void valveOpen() {
  digitalWrite(VALVE_IN3, HIGH);
  digitalWrite(VALVE_IN4, LOW);
}

// Close solenoid (release air)
void valveClose() {
  digitalWrite(VALVE_IN3, LOW);
  digitalWrite(VALVE_IN4, LOW);
}

void setup() {
  pinMode(PRESSURE_DATA, INPUT);
  pinMode(PRESSURE_CLK, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button uses internal pull-up
  pinMode(PUMP_IN1, OUTPUT);
  pinMode(PUMP_IN2, OUTPUT);
  pinMode(VALVE_IN3, OUTPUT);
  pinMode(VALVE_IN4, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Initialize
  pumpOff();
  valveClose();
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  Serial.begin(9600); // For debugging
}

void loop() {
  // === WHEN BUTTON IS PRESSED & HELD ===
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(50); // Debounce
    if (digitalRead(BUTTON_PIN) != LOW) return; // Ensure button is held

    // Reset LEDs
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);

    // === 1. INFLATE (PUMP RUNS WHILE BUTTON HELD) ===
    valveOpen(); // Allow air to glove
    pumpOn(); // Start pumping
    Serial.println("Pumping...");

    unsigned long startTime = millis();
    bool pressureReached = false;

    // Keep pumping while button is held or until target pressure
    while (digitalRead(BUTTON_PIN) == LOW && !pressureReached && (millis() - startTime < inflationTimeout)) {
      float pressure = readPressureKpa();
      Serial.print("Pressure: "); Serial.println(pressure);
      if (pressure >= targetPressure) {
        pressureReached = true;
      }
      delay(1000);
    }

    pumpOff(); // Stop when button is released or pressure reached

    // === 2. HOLD PRESSURE (IF REACHED TARGET) ===
    if (pressureReached) {
      float initialPressure = readPressureKpa();
      Serial.print("Holding at: "); Serial.println(initialPressure);
      unsigned long holdStart = millis();

      while (millis() - holdStart < holdTime) {
        delay(100); // Just wait (solenoid holds air)
      }

      float finalPressure = readPressureKpa();
      Serial.print("Final pressure: "); Serial.println(finalPressure);

      // === 3. CHECK RESULT ===
      if ((initialPressure - finalPressure) <= maxDrop) {
        digitalWrite(GREEN_LED, HIGH); // Pass
        Serial.println("PASS: Pressure stable");
      } else {
        digitalWrite(RED_LED, HIGH); // Fail
        Serial.println("FAIL: Pressure drop too high");
      }
    } else {
      Serial.println("Inflation stopped (button released or timeout)");
    }

    // === 4. RELEASE AIR ===
    valveClose(); // Open exhaust
    delay(2000); // Vent air
    valveOpen(); // Reset to default state
  }
}