#include "display.h"
#include "monitor.h"
#include "slime.h"
#include "stats.h"
#include "pet.h"

void displayInit() {
    monitorInit();
    statsInit();
}

void displayUpdate() {
    statsUpdate();

    // Slime color depends on total stats
    float statAvg = getPetStatAverage();
    uint16_t slimeColor;
    if (statAvg > 66.6) {
        slimeColor = ST77XX_BLUE;
    } else if (statAvg > 33.3) {
        slimeColor = ST77XX_YELLOW;
    } else {
        slimeColor = ST77XX_ORANGE;
    }
    if (!isPetAlive()) {
        slimeColor = ST77XX_RED;
    }
    slimeDraw(slimeColor);

    // Draw alive timer at bottom
    displayAliveTimer();
}

void displayAliveTimer() {
    static String lastTimerStr = "";
    static bool lastWasDead = false;
    if (!isPetAlive()) {
        String timerStr = getPetAliveTimeString();
        if (!lastWasDead || timerStr != lastTimerStr) {
            int timerHeight = 16;
            // Clear area for both timer and death message
            clearArea(0, SCREEN_HEIGHT - timerHeight - 20, SCREEN_WIDTH, timerHeight + 20);
            // Draw death message above timer, same size and color as timer text
            drawText("Your pet has died", ST77XX_WHITE, 10, SCREEN_HEIGHT - timerHeight - 18, 1);
            drawText("Alive:", ST77XX_WHITE, 10, SCREEN_HEIGHT - timerHeight + 2, 1);
            drawText(timerStr.c_str(), ST77XX_WHITE, 60, SCREEN_HEIGHT - timerHeight + 2, 1);
            lastTimerStr = timerStr;
        }
        lastWasDead = true;
    } else {
        // Clear the area so no text is visible when pet is alive
        int timerHeight = 16;
        clearArea(0, SCREEN_HEIGHT - timerHeight - 20, SCREEN_WIDTH, timerHeight + 20);
        lastWasDead = false;
        lastTimerStr = "";
    }
}

void clearAliveTimerDisplay() {
    int timerHeight = 16;
    clearArea(0, SCREEN_HEIGHT - timerHeight, SCREEN_WIDTH, timerHeight);
}
