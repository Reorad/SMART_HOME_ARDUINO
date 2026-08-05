#include "senzor_ultrasonic_parc.h"

// Obiectul și variabilele private stau doar aici
NewPing sonar(Trig_PIN, Echo_PIN, max_distance);

unsigned long last_time_ultra_senzor = 0;
unsigned long LED_TIMER = 0;

#define LED_ON 1
#define LED_OFF 0
int Led_State = LED_OFF;

void setup_Hardware() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void Run_Ultrasonic() {
    unsigned long current_time = millis(); 
    if(current_time - last_time_ultra_senzor >= TIME_Ultrasonic) { 
      last_time_ultra_senzor = current_time;
      unsigned int dist = sonar.ping_cm();
      Serial.print(dist);
      Serial.println("cm");

      if(dist > 0 && dist <= 10 ) {
        digitalWrite(LED_PIN, HIGH);
        Led_State = LED_ON;
        LED_TIMER = current_time;
      }
    }
}

void Timer_Led() {
    unsigned long current_time = millis(); 
    if(Led_State == LED_ON && current_time - LED_TIMER >= LED_ON_TIMER) {
      Led_State = LED_OFF;
      digitalWrite(LED_PIN, LOW);
    }
}