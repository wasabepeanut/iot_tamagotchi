#ifndef SLIME_H
#define SLIME_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "monitor.h"

// --- Constants ---
constexpr int SLIME_WIDTH = 60;
constexpr int SLIME_HEIGHT = 60;
constexpr int SLIME_OFFSET_Y = 10;
// No scaling used

// --- Functions ---
void slimeDraw(uint16_t color);
void slimeAnimate();

#endif
