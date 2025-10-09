#include <string.h>
#include "slime.h" // For extern slimeMessage
char slimeMessage[16] = "";
static unsigned long messageExpire = 0;
// --- Universal Cooldown settings (ms) ---
constexpr unsigned long BUTTON_COOLDOWN = 2000; // 2 seconds
static unsigned long lastButtonPress = 0;
#include "controls.h"
#include "button.h"
#include "pet.h"

// Buttons (no blue button)
static Button redButton(26);
static Button yellowButton(27);
static Button greenButton(14);

// Previous states
static bool prevRedState = false;
static bool prevYellowState = false;
static bool prevGreenState = false;

void controlsInit() {
    redButton.begin();
    yellowButton.begin();
    greenButton.begin();
}

// Message pools for each button
const char* redMessages[] = {"Yummy", "Delicious!", "Tasty!", "Nom nom", "So good!"};
const int redMsgCount = sizeof(redMessages)/sizeof(redMessages[0]);
const char* yellowMessages[] = {"Zzz...", "Sleepy", "Rest time", "Dreaming", "Good night"};
const int yellowMsgCount = sizeof(yellowMessages)/sizeof(yellowMessages[0]);
const char* greenMessages[] = {"I love jumping", "Fun!", "Let's play!", "Whee!", "Yay!"};
const int greenMsgCount = sizeof(greenMessages)/sizeof(greenMessages[0]);

void controlsUpdate() {
    redButton.update();
    yellowButton.update();
    greenButton.update();

    unsigned long now = millis();
    bool redState = redButton.getState();
    bool yellowState = yellowButton.getState();
    bool greenState = greenButton.getState();

    if (isPetAlive()) {
        if (redState && !prevRedState && (now - lastButtonPress > BUTTON_COOLDOWN)) {
            int rare = random(0, 100) < 5; // 5% chance
            int points;
            if (rare) {
                points = 50;
                strncpy(slimeMessage, "RARE FEAST! +50", sizeof(slimeMessage));
                slimeMessage[sizeof(slimeMessage)-1] = '\0';
            } else {
                points = random(5, 16);
                int msgIdx = random(0, redMsgCount);
                strncpy(slimeMessage, redMessages[msgIdx], sizeof(slimeMessage));
                slimeMessage[sizeof(slimeMessage)-1] = '\0';
            }
            myPet.health = min(100, myPet.health + points);
            petSave();
            lastButtonPress = now;
            messageExpire = now + BUTTON_COOLDOWN;
        }
        prevRedState = redState;

        if (yellowState && !prevYellowState && (now - lastButtonPress > BUTTON_COOLDOWN)) {
            int rare = random(0, 100) < 5; // 5% chance
            int points;
            if (rare) {
                points = 50;
                strncpy(slimeMessage, "POWER NAP! +50", sizeof(slimeMessage));
                slimeMessage[sizeof(slimeMessage)-1] = '\0';
            } else {
                points = random(5, 16);
                int msgIdx = random(0, yellowMsgCount);
                strncpy(slimeMessage, yellowMessages[msgIdx], sizeof(slimeMessage));
                slimeMessage[sizeof(slimeMessage)-1] = '\0';
            }
            myPet.energy = min(100, myPet.energy + points);
            petSave();
            lastButtonPress = now;
            messageExpire = now + BUTTON_COOLDOWN;
        }
        prevYellowState = yellowState;

        if (greenState && !prevGreenState && (now - lastButtonPress > BUTTON_COOLDOWN)) {
            int rare = random(0, 100) < 5; // 5% chance
            int points;
            if (rare) {
                points = 50;
                strncpy(slimeMessage, "SUPER JUMP! +50", sizeof(slimeMessage));
                slimeMessage[sizeof(slimeMessage)-1] = '\0';
            } else {
                points = random(5, 16);
                int msgIdx = random(0, greenMsgCount);
                strncpy(slimeMessage, greenMessages[msgIdx], sizeof(slimeMessage));
                slimeMessage[sizeof(slimeMessage)-1] = '\0';
            }
            myPet.happiness = min(100, myPet.happiness + points);
            petSave();
            lastButtonPress = now;
            messageExpire = now + BUTTON_COOLDOWN;
        }
        prevGreenState = greenState;
    } else {
        // When pet is dead, any of the three buttons resets the pet
        if (((redState && !prevRedState) || (yellowState && !prevYellowState) || (greenState && !prevGreenState)) && (now - lastButtonPress > BUTTON_COOLDOWN)) {
            int points = random(5, 16); // 5 to 15
            myPet.happiness = myPet.energy = myPet.health = points;
            petSave();
            lastButtonPress = now;
        }
        prevRedState = redState;
        prevYellowState = yellowState;
        prevGreenState = greenState;
    }
    // Clear message after cooldown (always runs)
    if (slimeMessage[0] && now > messageExpire) {
        slimeMessage[0] = '\0';
    }
}
