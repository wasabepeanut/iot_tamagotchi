#include <Arduino.h>
#include "button.h"

Button::Button(int pin) {
    _pin = pin;
}

void Button::begin() {
    pinMode(_pin, INPUT_PULLUP);
    _state = false;
    _lastState = false;
    _pressedEvent = false;
}

void Button::update() {
    _lastState = _state;
    _state = (digitalRead(_pin) == LOW);  // LOW = pressed

    // Detect press event (released → pressed)
    _pressedEvent = (!_lastState && _state);
}

bool Button::isPressed() {
    return _pressedEvent;  // True only on the loop when pressed
}

bool Button::getState() {
    return _state;          // True while button is held down
}
