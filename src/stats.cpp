#include "stats.h"
#include "monitor.h"
#include "pet.h"

// --- Previous values for dirty-checking ---
static int prevHappiness = -1;
static int prevEnergy = -1;
static int prevHealth = -1;

// --- Stat icons (8x8 bitmaps) ---
static const uint8_t happinessIcon[10] = {
    0b00111100,0b01000010,0b10100101,0b10000001,
    0b10100101,0b10011001,0b01000010,0b00111100,
    0b00000000,0b00000000
};

static const uint8_t energyIcon[10] = {
    0b00000100,0b00001100,0b00111000,0b01111000,
    0b00011100,0b00011000,0b00110000,0b01000000,
    0b00000000,0b00000000
};

static const uint8_t healthIcon[10] = {
    0b01100110,0b11111111,0b11111111,0b11111111,
    0b01111110,0b00111100,0b00011000,0b00000000,
    0b00000000,0b00000000
};

// --- Draw a bar + icon ---
static void drawBar(int x, int y, int value, int prevValue, uint16_t color, const uint8_t* icon, int iconHeight) {
    if (value == prevValue) return;

    constexpr int barWidth = 40, barHeight = 10, iconSpacing = 2;
    int totalHeight = iconHeight + iconSpacing + barHeight;

    // Clear area
    tft.fillRect(x - 1, y - iconHeight, barWidth + 2, totalHeight + 2, ST77XX_BLACK);

    // Draw icon
    int iconX = x + (barWidth - 8) / 2;
    int iconY = y - iconHeight;
    for (int row = 0; row < iconHeight; row++) {
        for (int col = 0; col < 8; col++) {
            if (icon[row] & (1 << (7 - col))) {
                tft.drawPixel(iconX + col, iconY + row, color);
            }
        }
    }

    // Draw bar
    tft.drawRect(x, y, barWidth, barHeight, ST77XX_WHITE);
    tft.fillRect(x, y, map(value, 0, 100, 0, barWidth), barHeight, color);
}

// --- Draw all stats ---
static void drawStats() {
    constexpr int barWidth = 40, numBars = 3, tallestIcon = 10;
    int totalWidth = numBars * barWidth;
    int spacing = (SCREEN_WIDTH - totalWidth) / (numBars + 1);
    int y = 5 + tallestIcon;

    int xHappy  = spacing;
    int xEnergy = spacing * 2 + barWidth;
    int xHealth = spacing * 3 + barWidth * 2;

    drawBar(xHappy,  y, myPet.happiness, prevHappiness, ST77XX_GREEN,  happinessIcon, 10);
    drawBar(xEnergy, y, myPet.energy,    prevEnergy,    ST77XX_YELLOW, energyIcon,   10);
    drawBar(xHealth, y, myPet.health,    prevHealth,    ST77XX_RED,    healthIcon,   10);

    prevHappiness = myPet.happiness;
    prevEnergy = myPet.energy;
    prevHealth = myPet.health;
}

// --- Public API ---
void statsInit() {
    drawStats();
}

void statsUpdate() {
    if (myPet.happiness != prevHappiness || myPet.energy != prevEnergy || myPet.health != prevHealth) {
        drawStats();
    }
}

float getPetStatAverage() {
    return (myPet.happiness + myPet.energy + myPet.health) / 3.0f;
}
