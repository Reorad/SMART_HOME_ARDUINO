#include "senzor_ultrasonic_parc.h"
#include "pini.h"
#include <NewPing.h>

static NewPing sonar(Trig_PIN, Echo_PIN, DISTANTA_MAX_cm);

static unsigned long ultima_citire = 0;
static unsigned int ultima_distanta = 0;


void ultrasonic_init() {
  ultima_citire = 0;
  ultima_distanta = 0;
}

void ultrasonic_update(unsigned long time) {
  if (time - ultima_citire >= Interval_Ultrasonic) {
    ultima_citire = time;
    ultima_distanta = sonar.ping_cm();
  }
}

unsigned int ultrasonic_distance_cm() {
  return ultima_distanta;
}