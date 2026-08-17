#ifndef SENZOR_PARCARE_H // Protecție standard împotriva includerii multiple
#define SENZOR_PARCARE_H

#include <Arduino.h>

const unsigned int DISTANTA_MAX_cm = 100;
const unsigned long Interval_Ultrasonic = 50;

// --- DECLARAȚII FUNCȚII (Să știe main.cpp că ele există) ---
void ultrasonic_init();
void ultrasonic_update(unsigned long time);

unsigned int ultrasonic_distance_cm();

#endif