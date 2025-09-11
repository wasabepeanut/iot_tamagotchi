#ifndef BUTTON_H
#define BUTTON_H

class Button {
public:
    Button(int pin);
    void begin();
    bool isPressed();  // Just detect if pressed now

private:
    int _pin;
};

#endif
