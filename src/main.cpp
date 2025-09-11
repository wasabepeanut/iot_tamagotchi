#include "monitor.h"
#include <Arduino.h>
#include "button.h"

Button blueButton(25);
Button redButton(26);
Button yellowButton(27);
Button greenButton(14);

void drawButtonState(const char* label, uint16_t labelColor, int y, bool pressed) {
    clearArea(0, y, tft.width(), 30);
    drawText(label, labelColor, 15, y, 1);
    drawText(pressed ? "PRESSED" : "RELEASED", ST77XX_WHITE, 100, y, 1);
}

void setup() {
    monitorInit();
    blueButton.begin();
    redButton.begin();
    yellowButton.begin();
    greenButton.begin();
}

void loop() {
    // Update button states (non-blocking)
    blueButton.update();
    redButton.update();
    yellowButton.update();
    greenButton.update();

    // Display current state
    drawButtonState("Blue:", ST77XX_BLUE, 0, blueButton.getState());
    drawButtonState("Red:", ST77XX_RED, 30, redButton.getState());
    drawButtonState("Yellow:", ST77XX_YELLOW, 60, yellowButton.getState());
    drawButtonState("Green:", ST77XX_GREEN, 90, greenButton.getState());

    delay(50);  // Optional small delay for UI refresh
}
