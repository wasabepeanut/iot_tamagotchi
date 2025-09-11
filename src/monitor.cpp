#include "monitor.h"
#include <SPI.h>

// Create TFT object
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void monitorInit() {
    // Initialize the TFT display
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextSize(2);  // Adjust size as needed
}

void drawColoredWord(const char* word, uint16_t colors[], int set_x, int set_y) {
    tft.setTextColor(colors[0]); // Only use first color
    tft.setCursor(set_x, set_y);
    tft.print(word);
}
