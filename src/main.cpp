#include "pet.h"
#include "controls.h"
#include "display.h"
#include "slime.h"

void setup() {
    petInit();
    controlsInit();
    displayInit();
}

void loop() {
    petUpdate();
    controlsUpdate();
    displayUpdate();
    if (isPetAlive()) {
        slimeAnimate();
    }
}
