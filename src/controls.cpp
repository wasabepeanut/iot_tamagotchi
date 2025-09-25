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

    bool blueState = blueButton.getState();
    if (blueState && !prevBlueState) { myPet.food = myPet.energy = myPet.happiness = 10; petSave(); }
    prevBlueState = blueState;

    bool redState = redButton.getState();
    if (redState && !prevRedState) { myPet.food = min(100, myPet.food + 10); petSave(); }
    prevRedState = redState;

    bool yellowState = yellowButton.getState();
    if (yellowState && !prevYellowState) { myPet.energy = min(100, myPet.energy + 10); petSave(); }
    prevYellowState = yellowState;

    bool greenState = greenButton.getState();
    if (greenState && !prevGreenState) { myPet.happiness = min(100, myPet.happiness + 10); petSave(); }
    prevGreenState = greenState;
}
