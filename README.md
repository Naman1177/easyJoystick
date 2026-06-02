# easyJoystick Arduino Library

A lightweight, robust, and feature-rich Arduino library for interfacing with standard analog joysticks. It handles automatic calibration, configurable deadzones, software axis swapping, debounced button presses (state and edge-triggering), and 8-way directional tracking.
version = 1.0.0

---

## Technical Overview & Wiring

The library interfaces with standard 2-axis analog joysticks that feature an integrated momentary push-button.


### Hardware Connections
| Joystick Pin | Microcontroller Pin Type | Description |
| :--- | :--- | :--- |
| **VCC** | 5V / 3.3V Power | Matches MCU logic level |
| **GND** | Ground | Common system ground |
| **VRx (X-Axis)** | Analog Input (e.g., `A0`) | X-axis potentiometer voltage divider |
| **VRy (Y-Axis)** | Analog Input (e.g., `A1`) | Y-axis potentiometer voltage divider |
| **SW (Switch)** | Digital Input (e.g., `D2`) | Tactile button switch (uses internal pull-up) |

---

## API Reference

### Constructor

#### `easyJoystick(int xPin, int yPin, int digiPin, int adcBits)`
Initializes the joystick object instance and configures default internal states.
* **`xPin`**: The analog pin connected to the X-axis (`VRx`).
* **`yPin`**: The analog pin connected to the Y-axis (`VRy`).
* **`digiPin`**: The digital pin connected to the switch (`SW`).
* **`adcBits`**: The resolution of your microcontroller's ADC in bits (e.g., `10` for standard Arduino Uno/Mega, `12` for ESP32/NodeMCU). This calculates the maximum ADC range dynamically.

---

### Initialization & Configuration

#### `void begin()`
Configures the digital pin mode with an internal `INPUT_PULLUP` resistor. It samples the analog pins 10 times consecutively during setup to establish baseline resting center-point coordinates. **Must be called in `setup()`**.

#### `void calibrate()`
Re-calculates the resting center-points of both axes by averaging 10 sequential readings. Useful if the joystick is off-center or biased when the system powers on.

#### `void setDeadzone(int radius)`
Sets the deadzone threshold around the calculated center point to eliminate analog jitter/drift at rest. 
* **`radius`**: Value in raw ADC units (Default is `20`). If the delta from the center point is less than this value, the joystick reports `0%`.

#### `void setDebounceTime(unsigned long ms)`
Sets the software debounce period for the physical pushbutton switch.
* **`ms`**: Debounce time window in milliseconds (Default is `50` ms).

#### `void swapAxes(bool swap)`
Optionally swaps the X and Y coordinate tracking orientations in software.
* **`swap`**: Pass `true` to route X-axis calculations to the Y-axis physical pin and vice-versa. Pass `false` to restore default mapping.

---

### Coordinate & Position Tracking

#### `int getRawX()`
Returns the instantaneous raw ADC value read directly from the X-axis pin (or Y-axis pin if axes are swapped). Returns a value between `0` and $2^{\text{adcBits}} - 1$.

#### `int getRawY()`
Returns the instantaneous raw ADC value read directly from the Y-axis pin (or X-axis pin if axes are swapped). Returns a value between `0` and $2^{\text{adcBits}} - 1$.

#### `int getPercentageX()`
Returns the mapped position of the X-axis as an integer percentage ranging from **`-100` to `100`**.
* Returns `0` if the reading falls within the configured `_deadzone`.
* Dynamically maps negative displacement from center to `[-100, 0]` and positive displacement to `[0, 100]`.

#### `int getPercentageY()`
Returns the mapped position of the Y-axis as an integer percentage ranging from **`-100` to `100`**.
* Returns `0` if the reading falls within the configured `_deadzone`.
* Dynamically maps negative displacement from center to `[-100, 0]` and positive displacement to `[0, 100]`.

---

### Button Handling

#### `bool isPressed()`
Performs a non-blocking software debounce on the digital switch pin. Returns `true` continuously as long as the button is physically held down.

#### `bool wasPressed()`
An edge-triggered method that returns `true` **only once** per physical button press event. It latches an internal flag and will not return `true` again until the switch is fully released and pressed down a second time.

---

### Advanced Directional Assessment

#### `JoystickDirection getDirection()`
Evaluates both percentage vectors simultaneously and returns an enumerated constant representing the current direction of the stick.

The library uses a dual-threshold calculation. If both axes cross a absolute threshold of $40\%$, it registers a diagonal direction. Otherwise, it defaults to the dominant axis vector.

**Returned Enum Tokens (`JoystickDirection`):**
* `JOY_CENTER` (Both axes at `0%`)
* `JOY_UP`
* `JOY_DOWN`
* `JOY_LEFT`
* `JOY_RIGHT`
* `JOY_UP_LEFT`
* `JOY_UP_RIGHT`
* `JOY_DOWN_LEFT`
* `JOY_DOWN_RIGHT`

## Installation Guide

### Method 1: Manual Installation (Recommended for Custom Libraries)
1. Download this repository as a `.zip` file (or copy the `easyJoystick.h` and `easyJoystick.cpp` files).
2. Open your Arduino IDE.
3. Navigate to **Sketch** > **Include Library** > **Add .ZIP Library...**
4. Select the downloaded `.zip` file, or manually place the unzipped folder directly inside your local Arduino libraries directory:
   * **Windows**: `Documents\Arduino\libraries\`
   * **macOS / Linux**: `~/Arduino/libraries/`
5. Restart your Arduino IDE.

---

## How to Include and Initialize

To use the library in your sketch, include its header file at the absolute top of your program and instantiate the class object by passing your target pin architecture.
<easyJoystick.h>


---

## Author & Contributions

* **Created by:** Naman Malhotra
* **Give Stars:** If this library saved you development time, please consider dropping a ⭐ on the repository!
* **Contribute:** Pull requests, bug fixes, optimization suggestions, and feature expansions are always welcome. Please open an issue first to discuss substantial structural updates.
