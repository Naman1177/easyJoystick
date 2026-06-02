/**
 * @file BasicRead.ino
 * @author Naman Malhotra
 * @brief Demonstrates basic initialization, calibration, and percentage readings.
 */

#include <easyJoystick.h>

// Pin Definitions
#define X_PIN   A0
#define Y_PIN   A1
#define SW_PIN  D1
#define ADC_BIT 12  // Set to 12 for ESP32/NodeMCU, 10 for Arduino Uno/Mega

// Instantiate easyJoystick
easyJoystick joystick(X_PIN, Y_PIN, SW_PIN, ADC_BIT);

void setup() {
  Serial.begin(115200); // High baud rate for smooth plotting/reading
  
  Serial.println(F("Initializing joystick..."));
  // Initializes pins and takes baseline samples to calibrate the center point
  joystick.begin(); 
  Serial.println(F("Calibration complete. Move the stick!"));
}

void loop() {
  // Get percentage vectors scaled from -100 to 100
  int pctX = joystick.getPercentageX();
  int pctY = joystick.getPercentageY();
  
  // Check if button is currently being held down (debounced)
  bool buttonHeld = joystick.isPressed();

  // Print format compatible with Arduino Serial Plotter
  Serial.print(F("X_Pct:"));
  Serial.print(pctX);
  Serial.print(F(",Y_Pct:"));
  Serial.print(pctY);
  Serial.print(F(",Button:"));
  Serial.println(buttonHeld ? 50 : 0); // Spikes to 50 on the plotter when pressed

  delay(20); // Small delay to prevent serial flooding
}
