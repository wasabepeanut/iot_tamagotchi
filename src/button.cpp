#include <Arduino.h>
#include "button.h"

Button::Button(int pin) {
    _pin = pin;
}

void Button::begin() {
    pinMode(_pin, INPUT_PULLUP);
}

bool Button::isPressed() {
    if (digitalRead(_pin) == LOW) {
        // Wait for release to avoid multiple triggers
        while (digitalRead(_pin) == LOW) {
            delay(10);
        }
        return true;
    }
    return false;
}
