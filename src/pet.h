#ifndef PET_H
#define PET_H

#include <Arduino.h>

struct Pet {
    int food;
    int energy;
    int happiness;
};

extern Pet myPet;

void petInit();
void petUpdate();
void petSave();
void petLoad();

#endif
