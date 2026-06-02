/**
 * @file DirectionAndClick.ino
 * @author Naman Malhotra
 * @brief Demonstrates edge-triggered button events and 8-way directional tracking.
 */

#include <easyJoystick.h>

#define X_PIN   A0
#define Y_PIN   A1 // use according to your board
#define SW_PIN  2
#define ADC_BIT 10

easyJoystick joystick(X_PIN, Y_PIN, SW_PIN, ADC_BIT);
JoystickDirection lastDirection = JOY_CENTER;

void setup() {
  Serial.begin(115200);
  joystick.begin();
  
  // Tweak deadzone if your joystick has heavy mechanical drift
  joystick.setDeadzone(30); 
  // Set custom debounce time window
  joystick.setDebounceTime(40);
  
  Serial.println(F("System Ready. Move stick or click button."));
}

void loop() {
  // 1. Edge-triggered button event handler
  if (joystick.wasPressed()) {
    Serial.println(F("--> Button Event: Click Detected! <--"));
  }

  // 2. State-change tracking for joystick direction
  JoystickDirection currentDirection = joystick.getDirection();
  
  if (currentDirection != lastDirection) {
    Serial.print(F("Direction Changed: "));
    
    switch (currentDirection) {
      case JOY_CENTER:     Serial.println(F("CENTER"));     break;
      case JOY_UP:         Serial.println(F("UP"));         break;
      case JOY_DOWN:       Serial.println(F("DOWN"));       break;
      case JOY_LEFT:       Serial.println(F("LEFT"));       break;
      case JOY_RIGHT:      Serial.println(F("RIGHT"));      break;
      case JOY_UP_LEFT:    Serial.println(F("UP-LEFT"));    break;
      case JOY_UP_RIGHT:   Serial.println(F("UP-RIGHT"));   break;
      case JOY_DOWN_LEFT:  Serial.println(F("DOWN-LEFT"));  break;
      case JOY_DOWN_RIGHT: Serial.println(F("DOWN-RIGHT")); break;
    }
    lastDirection = currentDirection;
  }
}
