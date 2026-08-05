#include <Arduino.h>
#include <NewPing.h>
#include "senzor_ultrasonic_parc.h"

// PINS USED FOR ULTRASONIC SENSOR :
// #define Trig_PIN 6
// #define Echo_PIN 7 
// #define LED_PIN 2
// #define max_distance 200



void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN , LOW);
}


void loop() {
  Run_Ultrasonic();
  Timer_Led();
}