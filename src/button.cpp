#include <Arduino.h>
#include "button.h"

Button::Button(int pin) {
    _pin = pin;
}

void Button::begin() {
    pinMode(_pin, INPUT_PULLUP);
}

bool Button::isPressed() {
    if (digitalRead(_pin) == LOW) { // Button pressed
        // Wait for release to avoid multiple triggers
        while (digitalRead(_pin) == LOW) {
            delay(10);
        }
        _pressCount++;  // Increment counter
        return true;
    }
    return false;
}

int Button::getPressCount() {
    return _pressCount;
}
