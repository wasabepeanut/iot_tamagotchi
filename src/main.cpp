#include "pet.h"
#include "controls.h"
#include "display.h"

void setup() {
    petInit();
    controlsInit();
    displayInit();
}

void loop() {
    petUpdate();
    controlsUpdate();
    displayUpdate();
    delay(50);
}
