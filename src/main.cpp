#include <Arduino.h>
#include "pini.h"
#include "senzor_ultrasonic_parc.h"
#include "proxi_alerta.h"
#include "servo_door.h"


void setup() {
  Serial.begin(9600);
  
  pinMode(LED_Proxy_PIN, OUTPUT);
  digitalWrite(LED_Proxy_PIN, LOW);

  pinMode(LED_SERVO_USA_VERDE, OUTPUT);
  digitalWrite(LED_SERVO_USA_VERDE, LOW);

  pinMode(LED_SERVO_USA_ALBASTRU, OUTPUT);
  digitalWrite(LED_SERVO_USA_ALBASTRU, LOW);

  pinMode(LED_SERVO_USA_ROSU, OUTPUT);
  digitalWrite(LED_SERVO_USA_ROSU, LOW);

  ultrasonic_init();
  alerta_init();
  init_servo();
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
    
    DOOR_FSM(current_time, ultrasonic_distance_cm());

    STATE s = get_door_state();

    static unsigned long ultima_tel = 0;
    if(current_time - ultima_tel >= 250){
      ultima_tel = current_time;
      Serial.print(F("dist="));
      Serial.print(ultrasonic_distance_cm());
      Serial.print(F("  stare="));
      Serial.println(s);
    }

    digitalWrite(LED_SERVO_USA_VERDE, LOW);
    digitalWrite(LED_SERVO_USA_ALBASTRU, LOW);
    digitalWrite(LED_SERVO_USA_ROSU, LOW);

    switch (s)
    {
    case OPENING_DOOR:
      digitalWrite(LED_SERVO_USA_VERDE, HIGH);
      break;
    case DOOR_CLOSING:
      digitalWrite(LED_SERVO_USA_VERDE, HIGH);
      break;
    case CLOSED_DOOR:
      digitalWrite(LED_SERVO_USA_ROSU, HIGH);
      break;
    case FULLY_OPEN_DOOR:
      digitalWrite(LED_SERVO_USA_ALBASTRU, HIGH);
    break;
    default:
      break;
    }

}