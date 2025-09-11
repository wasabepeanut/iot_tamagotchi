#include "monitor.h"
#include <SPI.h>

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void monitorInit() {
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST77XX_BLACK);
}

void drawText(const char* text, uint16_t color, int x, int y, int size) {
    tft.setTextColor(color, ST77XX_BLACK);
    tft.setTextSize(size);
    tft.setCursor(x, y);
    tft.print(text);
}

void clearArea(int x, int y, int w, int h) {
    tft.fillRect(x, y, w, h, ST77XX_BLACK);
}
