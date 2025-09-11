#ifndef BUTTON_H
#define BUTTON_H

class Button {
public:
    Button(int pin);
    void begin();
    bool isPressed();
    int getPressCount();  // Returns total button presses

private:
    int _pin;
    int _pressCount = 0;
};

#endif
