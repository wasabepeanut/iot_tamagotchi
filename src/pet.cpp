#include "pet.h"
#include <EEPROM.h>

Pet myPet;

// Timers
static unsigned long lastHungerUpdate = 0;
static unsigned long lastEnergyUpdate = 0;
static unsigned long lastHappinessUpdate = 0;

// EEPROM addresses
#define ADDR_FOOD      0
#define ADDR_ENERGY    1
#define ADDR_HAPPINESS 2

void petSave() {
    EEPROM.write(ADDR_FOOD, myPet.food);
    EEPROM.write(ADDR_ENERGY, myPet.energy);
    EEPROM.write(ADDR_HAPPINESS, myPet.happiness);
    EEPROM.commit();
}

void petLoad() {
    myPet.food = EEPROM.read(ADDR_FOOD);
    myPet.energy = EEPROM.read(ADDR_ENERGY);
    myPet.happiness = EEPROM.read(ADDR_HAPPINESS);

    if (myPet.food == 0xFF || myPet.food == 0) myPet.food = 100;
    if (myPet.energy == 0xFF || myPet.energy == 0) myPet.energy = 100;
    if (myPet.happiness == 0xFF || myPet.happiness == 0) myPet.happiness = 100;
}

void petInit() {
    EEPROM.begin(512);
    petLoad();
    unsigned long now = millis();
    lastHungerUpdate = now;
    lastEnergyUpdate = now;
    lastHappinessUpdate = now;
}

void petUpdate() {
    unsigned long now = millis();
    if (now - lastHungerUpdate > 300000) { myPet.food = max(0, myPet.food - 25); lastHungerUpdate = now; petSave(); }
    if (now - lastHappinessUpdate > 600000) { myPet.happiness = max(0, myPet.happiness - 25); lastHappinessUpdate = now; petSave(); }
    if (now - lastEnergyUpdate > 3600000) { myPet.energy = max(0, myPet.energy - 25); lastEnergyUpdate = now; petSave(); }
}
