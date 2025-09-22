// monitor.h
#ifndef MONITOR_H
#define MONITOR_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define TFT_CS     5
#define TFT_DC     16
#define TFT_RST    4

#define SCREEN_WIDTH  160
#define SCREEN_HEIGHT 128

extern Adafruit_ST7735 tft;

void monitorInit();
void drawText(const char* text, uint16_t color, int x, int y, int size=2);
void clearArea(int x, int y, int w, int h);

#endif
