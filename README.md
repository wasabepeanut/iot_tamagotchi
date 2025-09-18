# iot_tamagotchi
Repository for our digital pet project for our IoT-course.


## To-Do
* Menu System
* Hunger, Happiness, Gooning stats and logic
* Draw the character
* Your animal died screen

# Tamagotchi Logic

A Tamagotchi-style virtual pet works as a **finite state machine** with needs, timers, and interactions. The core idea is to simulate life by tracking stats that change over time and can be influenced by the player.

---

## 1. Core Stats / Attributes
Typical needs tracked by a Tamagotchi:

- **Hunger** → how full the pet is  
- **Happiness** → how entertained the pet is  
- **Energy / Sleepiness** → how tired it is  
- **Health / Cleanliness** → sometimes tracked separately  

Each stat has a **numeric range** (e.g., `0–100`).  
- Stats **decrease over time** (hunger rises, happiness falls).  
- Player actions **increase stats**.  
- Ignoring needs leads to **negative consequences** (sadness, sickness, or death).  

---

## 2. Timers & Decay
Each need decreases at a different rate:

- Every **5 minutes** → hunger decreases by 1  
- Every **10 minutes** → happiness decreases by 1  
- Every **1 hour** → sleepiness increases  

This ensures the pet feels “alive” even without interaction.

---

## 3. User Interactions
Players can care for their pet through actions:

- **Feed** → increases hunger (overfeeding may cause sickness)  
- **Play** → increases happiness but reduces energy  
- **Sleep** → resets energy/sleepiness  
- **Medicine** → cures sickness  
- **Clean** → resets mess/poop counter  

Each action has **trade-offs** to make the system more engaging.

---

## 4. Mood & Expression
The pet’s **sprite/icon changes** depending on needs:

- 😀 Happy → hunger + happiness are good  
- 😐 Neutral → needs are slightly off  
- 😡 Sad/angry → hungry or ignored  
- 🤒 Sick → very low stats  

> Your **8×10 icons** represent these states visually.

---

## 5. Growth / Evolution
Over time, the pet evolves:

- After a certain time, the pet **grows into a new form**  
- Evolution may depend on care quality:  
  - Good care → healthy evolution  
  - Poor care → sickly or lazy evolution  

---

## 6. End Conditions
If ignored too long, possible outcomes include:

- Pet **runs away**  
- Pet **dies** (classic Tamagotchi)  
- Softer version: pet just gets sick until cared for  

---

## 🔄 Summary
The Tamagotchi logic is a **loop of time-based stat decay**, where the user restores stats through actions.  
This creates a cycle of:

**Timers → Stats Change → Mood Update → User Interaction → Growth**
