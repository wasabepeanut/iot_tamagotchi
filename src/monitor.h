#ifndef MONITOR_H
#define MONITOR_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// Pin definitions
#define TFT_CS     5   // Chip Select
#define TFT_DC     16  // Data/Command
#define TFT_RST    4   // Reset

// Expose TFT display object
extern Adafruit_ST7735 tft;

// Functions
void monitorInit();
void drawColoredWord(const char* word, uint16_t colors[], int set_x, int set_y);

#endif
