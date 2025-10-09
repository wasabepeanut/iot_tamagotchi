// --- Cooldown settings (ms) ---
constexpr unsigned long BUTTON_COOLDOWN = 2000; // 2 seconds
static unsigned long lastBluePress = 0;
static unsigned long lastRedPress = 0;
static unsigned long lastYellowPress = 0;
static unsigned long lastGreenPress = 0;
#include "controls.h"
#include "button.h"
#include "pet.h"

// Buttons
static Button blueButton(25);
static Button redButton(26);
static Button yellowButton(27);
static Button greenButton(14);

// Previous states
static bool prevBlueState = false;
static bool prevRedState = false;
static bool prevYellowState = false;
static bool prevGreenState = false;

void controlsInit() {
    blueButton.begin();
    redButton.begin();
    yellowButton.begin();
    greenButton.begin();
}

void controlsUpdate() {
    blueButton.update();
    redButton.update();
    yellowButton.update();
    greenButton.update();

    unsigned long now = millis();
    bool blueState = blueButton.getState();
    if (blueState && !prevBlueState && (now - lastBluePress > BUTTON_COOLDOWN)) {
        int points = random(5, 16); // 5 to 15
        myPet.happiness = myPet.energy = myPet.health = points;
        petSave();
        lastBluePress = now;
    }
    prevBlueState = blueState;

    if (isPetAlive()) {
        bool redState = redButton.getState();
        if (redState && !prevRedState && (now - lastRedPress > BUTTON_COOLDOWN)) {
            int points = random(5, 16);
            myPet.health = min(100, myPet.health + points);
            petSave();
            lastRedPress = now;
        }
        prevRedState = redState;

        bool yellowState = yellowButton.getState();
        if (yellowState && !prevYellowState && (now - lastYellowPress > BUTTON_COOLDOWN)) {
            int points = random(5, 16);
            myPet.energy = min(100, myPet.energy + points);
            petSave();
            lastYellowPress = now;
        }
        prevYellowState = yellowState;

        bool greenState = greenButton.getState();
        if (greenState && !prevGreenState && (now - lastGreenPress > BUTTON_COOLDOWN)) {
            int points = random(5, 16);
            myPet.happiness = min(100, myPet.happiness + points);
            petSave();
            lastGreenPress = now;
        }
        prevGreenState = greenState;
    } else {
        prevRedState = redButton.getState();
        prevYellowState = yellowButton.getState();
        prevGreenState = greenButton.getState();
    }
}
