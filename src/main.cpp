#include "monitor.h"
#include <Arduino.h>
#include "button.h"

Button blueButton(25);
Button redButton(26);
Button yellowButton(27);
Button greenButton(14);

int blueCount = -1;
int redCount = -1;
int yellowCount = -1;
int greenCount = -1;

void drawCounter(const char* label, uint16_t color, int y, int oldCount, int newCount) {
    if (oldCount == newCount) return;

    // Clear the area behind the counter
    tft.fillRect(0, y, tft.width(), 30, ST77XX_BLACK);

    // Draw the label
    tft.setTextColor(color, ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setCursor(15, y);
    tft.print(label);

    // Prepare number
    char buffer[10];
    sprintf(buffer, "%d", newCount);

    // Calculate right-aligned X
    int textWidth = strlen(buffer) * 6 * 2; // 6 px per char * text size=2
    int x = tft.width() - textWidth - 10;

    // Draw the number
    tft.setTextSize(2);
    tft.setCursor(x, y);
    tft.print(buffer);
}

void setup() {
    monitorInit();
    blueButton.begin();
    redButton.begin();
    yellowButton.begin();
    greenButton.begin();
}

void loop() {
    blueButton.isPressed();
    redButton.isPressed();
    yellowButton.isPressed();
    greenButton.isPressed();

    int blueCurrentCount = blueButton.getPressCount();
    int redCurrentCount = redButton.getPressCount();
    int yellowCurrentCount = yellowButton.getPressCount();
    int greenCurrentCount = greenButton.getPressCount();

    // Each line stacked from the top of the display
    drawCounter("Blue:", ST77XX_BLUE,   0,  blueCount,   blueCurrentCount);
    drawCounter("Red:",  ST77XX_RED,   30,  redCount,    redCurrentCount);
    drawCounter("Yellow:", ST77XX_YELLOW, 60, yellowCount, yellowCurrentCount);
    drawCounter("Green:", ST77XX_GREEN, 90, greenCount,  greenCurrentCount);

    // Update stored counts
    blueCount   = blueCurrentCount;
    redCount    = redCurrentCount;
    yellowCount = yellowCurrentCount;
    greenCount  = greenCurrentCount;

    delay(50);
}
