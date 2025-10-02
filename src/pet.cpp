#include "pet.h"
#include <EEPROM.h>


Pet myPet;
unsigned long petBirthMillis = 0;

// Timers
static unsigned long lastHappinessUpdate = 0;
static unsigned long lastEnergyUpdate = 0;
static unsigned long lastHealthUpdate = 0;

unsigned long petDeathMillis = 0;
bool petWasAlive = true;

// EEPROM addresses
#define ADDR_HAPPINESS 0
#define ADDR_ENERGY    1
#define ADDR_HEALTH    2

void petSave() {
    EEPROM.write(ADDR_HAPPINESS, myPet.happiness);
    EEPROM.write(ADDR_ENERGY, myPet.energy);
    EEPROM.write(ADDR_HEALTH, myPet.health);
    EEPROM.commit();
}

// Returns true if pet is alive (all stats > 0), false otherwise
bool isPetAlive() {
    return myPet.happiness > 0 && myPet.energy > 0 && myPet.health > 0;
}

void petLoad() {
    myPet.happiness = EEPROM.read(ADDR_HAPPINESS);
    myPet.energy = EEPROM.read(ADDR_ENERGY);
    myPet.health = EEPROM.read(ADDR_HEALTH);

    if (myPet.happiness == 0xFF || myPet.happiness == 0) myPet.happiness = 100;
    if (myPet.energy == 0xFF || myPet.energy == 0) myPet.energy = 100;
    if (myPet.health == 0xFF || myPet.health == 0) myPet.health = 100;
}

void petInit() {
    EEPROM.begin(512);
    petLoad();
    unsigned long now = millis();
    lastHappinessUpdate = now;
    lastEnergyUpdate = now;
    lastHealthUpdate = now;
    petBirthMillis = now;
    petDeathMillis = 0;
    petWasAlive = true;
}

void petUpdate() {
    int timeScale = 4; // Speed up time for testing
    unsigned long now = millis();
    if (isPetAlive()) {
        if (now - lastHappinessUpdate > 60000 / timeScale) { myPet.happiness = max(0, myPet.happiness - 25); lastHappinessUpdate = now; petSave(); }
        if (now - lastEnergyUpdate > 360000 / timeScale) { myPet.energy = max(0, myPet.energy - 25); lastEnergyUpdate = now; petSave(); }
        if (now - lastHealthUpdate > 300000 / timeScale) { myPet.health = max(0, myPet.health - 25); lastHealthUpdate = now; petSave(); }
    }

    // Track pet death time
    if (petWasAlive && !isPetAlive()) {
        petDeathMillis = now;
        petWasAlive = false;
    }
    if (!petWasAlive && isPetAlive()) {
           // Pet revived, reset birth time
           petBirthMillis = now;
           petDeathMillis = 0;
           petWasAlive = true;
           // Clear timer display on revive
           extern void clearAliveTimerDisplay();
           clearAliveTimerDisplay();
    }
}

String getPetAliveTimeString() {
    unsigned long endMillis;
    if (isPetAlive()) {
        endMillis = millis();
    } else {
        endMillis = petDeathMillis;
    }
    unsigned long aliveMillis = endMillis - petBirthMillis;
    unsigned long seconds = aliveMillis / 1000;
    unsigned long minutes = seconds / 60;
    unsigned long hours = minutes / 60;
    seconds = seconds % 60;
    minutes = minutes % 60;
    char buf[16];
    snprintf(buf, sizeof(buf), "%02lu:%02lu:%02lu", hours, minutes, seconds);
    return String(buf);
}
