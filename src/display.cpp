#include "display.h"
#include "monitor.h"
#include "slime.h"
#include "stats.h"
#include "pet.h"

void displayInit() {
    monitorInit();
    slimeDraw(ST77XX_BLUE);
    statsInit();
}

void displayUpdate() {
    statsUpdate();

    // Slime color depends on total stats
        float statAvg = (myPet.food + myPet.energy + myPet.happiness) / 3.0;
        uint16_t slimeColor;
        if (statAvg > 66.6) {
            slimeColor = ST77XX_BLUE;
        } else if (statAvg > 33.3) {
            slimeColor = ST77XX_YELLOW;
        } else {
            slimeColor = ST77XX_RED;
        }
        slimeDraw(slimeColor);
}
