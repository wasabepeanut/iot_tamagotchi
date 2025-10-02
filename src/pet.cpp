#include "pet.h"
#include <EEPROM.h>

Pet myPet;

// Timers
static unsigned long lastHappinessUpdate = 0;
static unsigned long lastEnergyUpdate = 0;
static unsigned long lastHealthUpdate = 0;

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
}

void petUpdate() {
    unsigned long now = millis();
    if (now - lastHappinessUpdate > 600000) { myPet.happiness = max(0, myPet.happiness - 25); lastHappinessUpdate = now; petSave(); }
    if (now - lastEnergyUpdate > 3600000) { myPet.energy = max(0, myPet.energy - 25); lastEnergyUpdate = now; petSave(); }
    if (now - lastHealthUpdate > 300000) { myPet.health = max(0, myPet.health - 25); lastHealthUpdate = now; petSave(); }
}
