#ifndef MONITOR_H
#define MONITOR_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// Pin definitions
#define TFT_CS     5
#define TFT_DC     16
#define TFT_RST    4

extern Adafruit_ST7735 tft;

void monitorInit();
void drawText(const char* text, uint16_t color, int x, int y, int size=2);
void clearArea(int x, int y, int w, int h);

#endif
