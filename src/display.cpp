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
    int statTotal = myPet.food + myPet.energy + myPet.happiness;
    uint16_t slimeColor;
    if (statTotal > 200) {
        slimeColor = ST77XX_BLUE;
    } else if (statTotal > 100) {
        slimeColor = ST77XX_YELLOW;
    } else {
        slimeColor = ST77XX_RED;
    }
    slimeDraw(slimeColor);
}
