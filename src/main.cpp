#include "monitor.h"
#include <Arduino.h>
#include "button.h"

Button blueButton(25);
Button redButton(26);
Button yellowButton(27);
Button greenButton(14);

void drawButtonState(const char* label, uint16_t labelColor, int y, bool pressed) {
    int lineHeight = 15; // Adjust as needed for your font size
    clearArea(0, y, tft.width(), lineHeight * 2);
    drawText(label, labelColor, 0, y, 1); // Start at left edge
    drawText(pressed ? "PRESSED" : "RELEASED", ST77XX_WHITE, 0, y + lineHeight, 1); // Start at left edge
}

// Store previous button states
bool prevBlueState = false;
bool prevRedState = false;
bool prevYellowState = false;
bool prevGreenState = false;

void setup() {
    monitorInit();
    blueButton.begin();
    redButton.begin();
    yellowButton.begin();
    greenButton.begin();

    // Initialize previous states
    prevBlueState = blueButton.getState();
    prevRedState = redButton.getState();
    prevYellowState = yellowButton.getState();
    prevGreenState = greenButton.getState();

    // Draw all button states on boot
    drawButtonState("Blue:", ST77XX_BLUE, 0, prevBlueState);
    drawButtonState("Red:", ST77XX_RED, 30, prevRedState);
    drawButtonState("Yellow:", ST77XX_YELLOW, 60, prevYellowState);
    drawButtonState("Green:", ST77XX_GREEN, 90, prevGreenState);
}

void loop() {
    // Update button states (non-blocking)
    blueButton.update();
    redButton.update();
    yellowButton.update();
    greenButton.update();

    // Get current states
    bool blueState = blueButton.getState();
    bool redState = redButton.getState();
    bool yellowState = yellowButton.getState();
    bool greenState = greenButton.getState();

    // Only redraw if state changed
    if (blueState != prevBlueState) {
        drawButtonState("Blue:", ST77XX_BLUE, 0, blueState);
        prevBlueState = blueState;
    }
    if (redState != prevRedState) {
        drawButtonState("Red:", ST77XX_RED, 30, redState);
        prevRedState = redState;
    }
    if (yellowState != prevYellowState) {
        drawButtonState("Yellow:", ST77XX_YELLOW, 60, yellowState);
        prevYellowState = yellowState;
    }
    if (greenState != prevGreenState) {
        drawButtonState("Green:", ST77XX_GREEN, 90, greenState);
        prevGreenState = greenState;
    }

    delay(10);  // Small delay for responsiveness
}
