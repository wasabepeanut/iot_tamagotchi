#ifndef BUTTON_H
#define BUTTON_H

class Button {
public:
    Button(int pin);
    void begin();
    void update();          
    bool isPressed();       
    bool getState();        

private:
    int _pin;
    bool _state = false;
    bool _lastState = false;
    bool _pressedEvent = false;
};

#endif
