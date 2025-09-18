#include "tamagotchi.h"
#include "monitor.h"
#include "button.h"
#include <EEPROM.h>
#include <Arduino.h>

// Buttons
Button blueButton(25);   // Reset
Button redButton(26);    // Play
Button yellowButton(27); // Sleep
Button greenButton(14);  // Feed

// Pet state
int food, energy, happiness;
unsigned long lastUpdate;

// Simple 8x8 "sprites" for resources
// Food icon (8x8)
const uint8_t foodIcon[10] = {
  0b01100110, //  **  **
  0b11111111, // ********
  0b11111111, // ********
  0b11111111, // ********
  0b01111110, //  ******
  0b00111100, //   ****
  0b00011000, //    **
  0b00000000,  //
  0b00000000,
  0b00000000      
};



// Happiness icon (8x8 smiley)
const uint8_t happinessIcon[10] = {
  0b00111100, //   ****
  0b01000010, //  *    *
  0b10100101, // * *  * *
  0b10000001, // *      *
  0b10100101, // * *  * *
  0b10011001, // *  **  *
  0b01000010, //  *    *
  0b00111100, //   ****
  0b00000000,
  0b00000000
};


// Energy icon (8x10 lightning bolt)
const uint8_t energyIcon[10] = {
  0b00000100, //       *
  0b00001100, //      **
  0b00111000, //     ***
  0b01111000, //   ****
  0b00011100, //      ***
  0b00011000, //     **
  0b00110000, //    **
  0b01000000  //   *
};





// Previous values (to prevent flicker)
int prevFood = -1;
int prevEnergy = -1;
int prevHappiness = -1;

// Button previous states (edge detection)
bool prevBlueState = false;
bool prevRedState = false;
bool prevYellowState = false;
bool prevGreenState = false;

// EEPROM addresses
#define ADDR_FOOD      0
#define ADDR_ENERGY    1
#define ADDR_HAPPINESS 2

// Save state to EEPROM (ESP32)
void saveState() {
    EEPROM.write(ADDR_FOOD, food);
    EEPROM.write(ADDR_ENERGY, energy);
    EEPROM.write(ADDR_HAPPINESS, happiness);
    EEPROM.commit();
}

// Load state from EEPROM
void loadState() {
    food = EEPROM.read(ADDR_FOOD);
    energy = EEPROM.read(ADDR_ENERGY);
    happiness = EEPROM.read(ADDR_HAPPINESS);

    // Default values on first run
    if (food == 0xFF) food = 50;
    if (energy == 0xFF) energy = 50;
    if (happiness == 0xFF) happiness = 50;
}

// Update pet state automatically
void updatePet() {
    unsigned long nowMillis = millis();
    if (nowMillis - lastUpdate > 2000) { // every 2 seconds
        food = max(0, food - 1);
        energy = max(0, energy - 1);
        happiness = max(0, happiness - 1);

        lastUpdate = nowMillis;
        saveState();
    }
}

void drawIcon(int x, int y, const uint8_t icon[8], uint16_t color) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (icon[row] & (1 << (7 - col))) {
                tft.drawPixel(x + col, y + row, color);
            }
        }
    }
}


// Draw a compact horizontal bar with top-aligned icon
void drawBar(int x, int y, int value, int prevValue, uint16_t color, const uint8_t* icon, int iconHeight) {
    if (value == prevValue) return; // no redraw if unchanged

    int barWidth = 40;
    int barHeight = 10;
    int iconSpacing = 2;  // space between icon and bar

    // Total height needed: icon + spacing + bar
    int totalHeight = iconHeight + iconSpacing + barHeight;

    // Clear area for icon + bar
    clearArea(x - 1, y - iconHeight, barWidth + 2, totalHeight + 2);

    // Draw icon above bar
    int iconX = x + (barWidth - 8) / 2;  // center icon horizontally
    int iconY = y - iconHeight;

    for (int row = 0; row < iconHeight; row++) {
        for (int col = 0; col < 8; col++) {
            if (icon[row] & (1 << (7 - col))) {
                tft.drawPixel(iconX + col, iconY + row, color);
            }
        }
    }

    // Draw the bar below the icon
    tft.drawRect(x, y, barWidth, barHeight, ST77XX_WHITE);
    tft.fillRect(x, y, map(value, 0, 100, 0, barWidth), barHeight, color);
}






// Draw all stats at the top row
void drawStats() {
    int barWidth = 40;
    int numBars = 3;
    int totalWidth = numBars * barWidth;
    int spacing = (tft.width() - totalWidth) / (numBars + 1);

    int tallestIcon = 10; // lightning bolt height

    // y position for top of bar
    int y = 5 + tallestIcon; // top margin + tallest icon

    // Reordered positions: happiness (left), energy (center), food (right)
    int xHappy  = spacing;
    int xEnergy = spacing * 2 + barWidth;
    int xFood   = spacing * 3 + barWidth * 2;

    // Draw bars with icons
    drawBar(xHappy, y, happiness, prevHappiness, ST77XX_GREEN, happinessIcon, 8); // Smiley
    drawBar(xEnergy, y, energy, prevEnergy, ST77XX_YELLOW, energyIcon, 10);       // Lightning
    drawBar(xFood, y, food, prevFood, ST77XX_RED, foodIcon, 8);         // Heart

    prevFood = food;
    prevHappiness = happiness;
    prevEnergy = energy;
}


// Public init function
void tamagotchiInit() {
    EEPROM.begin(512); // required on ESP32
    monitorInit();

    blueButton.begin();
    redButton.begin();
    yellowButton.begin();
    greenButton.begin();

    loadState();
    lastUpdate = millis();

    drawStats();
}

// Public update function
void tamagotchiUpdate() {
    updatePet();

    blueButton.update();
    redButton.update();
    yellowButton.update();
    greenButton.update();

    // Edge detection (pressed now, not pressed before)

    bool blueState = blueButton.getState();
    if (blueState && !prevBlueState) {
        food = happiness = energy = 50; // Reset all stats
        saveState();
    }
    prevBlueState = blueState;

    bool redState = redButton.getState();
    if (redState && !prevRedState) {
        if (food < 100) food = min(100, food + 10); // Health
        saveState();
    }
    prevRedState = redState;

    bool yellowState = yellowButton.getState();
    if (yellowState && !prevYellowState) {
        if (energy < 100) energy = min(100, energy + 10); // Stamina
        saveState();
    }
    prevYellowState = yellowState;

    bool greenState = greenButton.getState();
    if (greenState && !prevGreenState) {
        if (happiness < 100) happiness = min(100, happiness + 10); // Happiness
        saveState();
    }
    prevGreenState = greenState;

    drawStats();
}
