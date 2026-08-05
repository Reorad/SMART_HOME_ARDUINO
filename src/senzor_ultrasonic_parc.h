#ifndef SENZOR_PARCARE_H // Protecție standard împotriva includerii multiple
#define SENZOR_PARCARE_H

#include <Arduino.h>
#include <NewPing.h>

// PINS USED FOR ULTRASONIC SENSOR :
#define Trig_PIN 6
#define Echo_PIN 7 
#define LED_PIN 2
#define max_distance 200


const unsigned long TIME_Ultrasonic = 50;
const unsigned long LED_ON_TIMER = 2000;

// --- DECLARAȚII FUNCȚII (Să știe main.cpp că ele există) ---
void setup_Hardware();
void Run_Ultrasonic();
void Timer_Led();

#endif