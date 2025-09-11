#ifndef BUTTON_H
#define BUTTON_H

class Button {
public:
    Button(int pin);
    void begin();
    void update();          // Update button state, call every loop
    bool isPressed();       // Returns true only on the moment it is pressed
    bool getState();        // Returns current state: pressed or released

private:
    int _pin;
    bool _state = false;       // Current state
    bool _lastState = false;   // Previous state
    bool _pressedEvent = false; // True for one loop when pressed
};

#endif
