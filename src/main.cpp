#include <WiFi.h>
#include <HTTPClient.h>
#include "pet.h"
#include "controls.h"
#include "display.h"
#include "slime.h"
#include "score.h"

void setup() {
    connectWiFi();
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
