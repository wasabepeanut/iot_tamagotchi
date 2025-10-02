#ifndef PET_H
#define PET_H

#include <Arduino.h>

struct Pet {
    int energy;
    int happiness;
    int health;
};

extern Pet myPet;


void petInit();
void petUpdate();
void petSave();
void petLoad();

// Returns true if pet is alive (all stats > 0), false otherwise
bool isPetAlive();

#endif
