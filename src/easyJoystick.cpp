#include "easyJoystick.h"

easyJoystick::easyJoystick(int xPin, int yPin, int digiPin, int adcBits){
    _xPin = xPin;
    _yPin = yPin;
    _digiPin = digiPin;
    _adcValue = (1<<adcBits)-1;
    _deadzone = 20;
    _buttonDelay = 50;      
    _lastButtonState = false;
    _stableButtonState = false;
    _wasPressedFlag = false;
    _swapAxes = false;

}
void easyJoystick::begin(){
    pinMode(_digiPin, INPUT_PULLUP);
    long sumX = 0;
    long sumY = 0;
    for(int i = 0; i < 10; i++){
        sumX = sumX+analogRead(_xPin);
        sumY = sumY+analogRead(_yPin);
        delay(10);
    }
    _centreX = sumX/10;
    _centreY = sumY/10;
}
void easyJoystick::calibrate() {
    long sumX = 0;
    long sumY = 0;
    for(int i = 0; i < 10; i++){
        sumX = sumX+analogRead(_xPin);
        sumY = sumY+analogRead(_yPin);
        delay(10);
    }
    _centreX = sumX/10;
    _centreY = sumY/10;
}
void easyJoystick::setDeadzone(int radius) { 
    _deadzone = radius; 
}
void easyJoystick::swapAxes(bool swap) {
    _swapAxes = swap;
}

int easyJoystick::getRawX(){
    if (_swapAxes) {
        return analogRead(_yPin); 
    }
    return analogRead(_xPin);
}

int easyJoystick::getRawY(){
    if (_swapAxes) {
        return analogRead(_xPin); 
    }
    return analogRead(_yPin);
}
int easyJoystick::getPercentageX(){
    int raw = getRawX();
    int diff = abs(raw - _centreX);
    if(diff < _deadzone){
        return 0;
    }
    if (raw > _centreX){
        return map(raw, _centreX, _adcValue, 0, 100);
    }
    else{
        return map(raw, 0, _centreX, -100, 0);
    }
}
int easyJoystick::getPercentageY(){
    int raw = getRawY();
    int diff = abs(raw - _centreY);
    if(diff < _deadzone){
        return 0;
    }
    if (raw > _centreY){
        return map(raw, _centreY, _adcValue, 0, 100);
    }
    else{
        return map(raw, 0, _centreY, -100, 0);
    }
}
void easyJoystick::setDebounceTime(unsigned long ms) {
     _buttonDelay = ms; 
}
bool easyJoystick::isPressed() {
    bool currentRead = (digitalRead(_digiPin) == LOW);
    if (currentRead != _lastButtonState){
        _lastDebounceTime = millis();
    }
    
    if ((millis() - _lastDebounceTime) > _buttonDelay) {
        _stableButtonState = currentRead;
    }
    _lastButtonState = currentRead;
    return _stableButtonState;
} 

bool easyJoystick::wasPressed() {
    bool pressedNow = isPressed();
    if (pressedNow && !_wasPressedFlag) {
        _wasPressedFlag = true; 
        return true;
    }
    if (!pressedNow) _wasPressedFlag = false;
    return false;
}



JoystickDirection easyJoystick::getDirection() {
    int pctX = getPercentageX();
    int pctY = getPercentageY();
    
    if (pctX == 0 && pctY == 0) {
        return JOY_CENTER;
    }
    
    
    if (pctY > 40 && pctX > 40){
        return JOY_UP_RIGHT;
    }
    if (pctY > 40 && pctX < -40)  {
        return JOY_UP_LEFT;
    }
    if (pctY < -40 && pctX > 40)  {
        return JOY_DOWN_RIGHT;
    }
    if (pctY < -40 && pctX < -40) {
        return JOY_DOWN_LEFT;
    }
    
    
    if (abs(pctY) > abs(pctX)) {
        return (pctY > 0) ? JOY_UP : JOY_DOWN;
    } else {
        return (pctX > 0) ? JOY_RIGHT : JOY_LEFT;
    }
}
