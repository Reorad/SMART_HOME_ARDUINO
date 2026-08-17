#ifndef proxi_alerta_h
#define proxi_alerta_h


#include <Arduino.h>

const unsigned int ALERTA_DISTANTA = 10; // cm
const uint8_t Confirm_trigger = 3 ;
const unsigned long Durata_Alerta = 2000; // ms

void alerta_init();

void alerta_update(unsigned long time, unsigned int distanta);

bool alerta_activata();


#endif