#ifndef SLIME_H
#define SLIME_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "monitor.h"

// --- Constants ---
constexpr int SLIME_WIDTH = 60;
constexpr int SLIME_HEIGHT = 50;
constexpr int SLIME_SCALE = 1;
constexpr int SLIME_OFFSET_Y = 10;

// --- Functions ---
void slimeDraw(uint16_t color = ST77XX_BLUE);

#endif
