#include "display.h"
#include "monitor.h"
#include "pet.h"

// Previous values (to prevent flicker)
static int prevFood = -1;
static int prevEnergy = -1;
static int prevHappiness = -1;

// Simple 8x8 icons
static const uint8_t foodIcon[10] = {
  0b01100110,0b11111111,0b11111111,0b11111111,
  0b01111110,0b00111100,0b00011000,0b00000000,
  0b00000000,0b00000000
};
static const uint8_t happinessIcon[10] = {
  0b00111100,0b01000010,0b10100101,0b10000001,
  0b10100101,0b10011001,0b01000010,0b00111100,
  0b00000000,0b00000000
};
static const uint8_t energyIcon[10] = {
  0b00000100,0b00001100,0b00111000,0b01111000,
  0b00011100,0b00011000,0b00110000,0b01000000
};

// Draw a bar + icon
static void drawBar(int x, int y, int value, int prevValue, uint16_t color, const uint8_t* icon, int iconHeight) {
    if (value == prevValue) return;

    int barWidth = 40, barHeight = 10, iconSpacing = 2;
    int totalHeight = iconHeight + iconSpacing + barHeight;

    clearArea(x - 1, y - iconHeight, barWidth + 2, totalHeight + 2);

    // Draw icon
    int iconX = x + (barWidth - 8) / 2;
    int iconY = y - iconHeight;
    for (int row = 0; row < iconHeight; row++)
        for (int col = 0; col < 8; col++)
            if (icon[row] & (1 << (7 - col))) tft.drawPixel(iconX + col, iconY + row, color);

    // Draw bar
    tft.drawRect(x, y, barWidth, barHeight, ST77XX_WHITE);
    tft.fillRect(x, y, map(value, 0, 100, 0, barWidth), barHeight, color);
}

// Draw all stats
static void drawStats() {
    int barWidth = 40;
    int numBars = 3;
    int totalWidth = numBars * barWidth;
    int spacing = (tft.width() - totalWidth) / (numBars + 1);
    int tallestIcon = 10;
    int y = 5 + tallestIcon;

    int xHappy  = spacing;
    int xEnergy = spacing * 2 + barWidth;
    int xFood   = spacing * 3 + barWidth * 2;

    drawBar(xHappy, y, myPet.happiness, prevHappiness, ST77XX_GREEN, happinessIcon, 10);
    drawBar(xEnergy, y, myPet.energy, prevEnergy, ST77XX_YELLOW, energyIcon, 10);
    drawBar(xFood, y, myPet.food, prevFood, ST77XX_RED, foodIcon, 10);

    prevFood = myPet.food;
    prevHappiness = myPet.happiness;
    prevEnergy = myPet.energy;
}

void displayInit() {
    monitorInit();
    drawStats();
}

void displayUpdate() {
    drawStats();
}
