#include "monitor.h"
#include <Arduino.h>
#include "button.h"

Button blueButton(25);
Button redButton(26);
Button yellowButton(27);
Button greenButton(14);

int blueCount = 0;
int redCount = 0;
int yellowCount = 0;
int greenCount = 0;

void drawCounter(const char* label, uint16_t color, int y, int count) {
    clearArea(0, y, tft.width(), 30);  // Clear previous number
    drawText(label, color, 15, y, 1);

    char buffer[10];
    sprintf(buffer, "%d", count);

    int textWidth = strlen(buffer) * 6 * 2;
    int x = tft.width() - textWidth - 10;
    drawText(buffer, color, x, y, 2);
}

void setup() {
    monitorInit();
    blueButton.begin();
    redButton.begin();
    yellowButton.begin();
    greenButton.begin();
}

void loop() {
    if (blueButton.isPressed()) blueCount++;
    if (redButton.isPressed()) redCount++;
    if (yellowButton.isPressed()) yellowCount++;
    if (greenButton.isPressed()) greenCount++;

    drawCounter("Blue:", ST77XX_BLUE, 0, blueCount);
    drawCounter("Red:", ST77XX_RED, 30, redCount);
    drawCounter("Yellow:", ST77XX_YELLOW, 60, yellowCount);
    drawCounter("Green:", ST77XX_GREEN, 90, greenCount);

    delay(50);
}
