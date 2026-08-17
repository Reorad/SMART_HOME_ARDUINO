#include <Arduino.h>
#include "pini.h"
#include "senzor_ultrasonic_parc.h"
#include "proxi_alerta.h"


void setup() {
  Serial.begin(9600);
  
  pinMode(LED_Proxy_PIN, OUTPUT);
  digitalWrite(LED_Proxy_PIN, LOW);

  ultrasonic_init();
  alerta_init();

  Serial.println("Start_ultrasonic sensor");

}


void loop() {
    const unsigned long current_time = millis();
    ultrasonic_update(current_time);
    alerta_update(current_time, ultrasonic_distance_cm());

    if(alerta_activata()){
      digitalWrite(LED_Proxy_PIN, HIGH);
    }
    else{
      digitalWrite(LED_Proxy_PIN, LOW);
    }
      
    
}