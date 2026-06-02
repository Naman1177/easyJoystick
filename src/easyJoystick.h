#ifndef EASYJOYSTICK_H
#define EASYJOYSTICK_H
#include <Arduino.h>
enum JoystickDirection {
    JOY_CENTER = 0,
    JOY_UP,
    JOY_DOWN,
    JOY_LEFT,
    JOY_RIGHT,
    JOY_UP_LEFT,
    JOY_UP_RIGHT,
    JOY_DOWN_LEFT,
    JOY_DOWN_RIGHT
};
class easyJoystick{
    private:
        int _xPin;
        int _yPin;
        int _digiPin;
        int _deadzone;
        unsigned long _buttonDelay;
        int _centreX;
        int _centreY;
        int _adcValue;
        bool _lastButtonState;
        unsigned long _lastDebounceTime;
        bool _stableButtonState;
        bool _wasPressedFlag;
        bool _swapAxes;



    public:
        easyJoystick(int xPin, int yPin, int digiPin , int adcBits);

        void begin();
        int getRawX();
        int getRawY();
        int getPercentageX();
        int getPercentageY();
        void setDebounceTime(unsigned long ms);
        void setDeadzone(int radius);
        bool isPressed();
        bool wasPressed();
        void swapAxes(bool swap);
        void calibrate();

        JoystickDirection getDirection();
};
#endif
