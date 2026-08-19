#include <Arduino.h>
#include "pini.h"
#include "senzor_ultrasonic_parc.h"
#include "proxi_alerta.h"
#include <Servo.h>



int UNGHI_CURR = 0;
unsigned long ultimul_time = 0;
unsigned long ultima_deschidere = 0;
Servo servo_motor;

// CONSTANTS TO BE USED FOR THE DOOR ANGLE
int UNGHI_OPEN = 90;
int UNGHI_CLOSED = 0;
int DISTANTA_USA_MAX = 30;
int TIME_USA_OPEN = 5000;
int STEP_ANGLE = 2;
int TIME_BETWEEN_STEPS = 20;

enum STATE {CLOSED_DOOR, OPENING_DOOR, FULLY_OPEN_DOOR, DOOR_CLOSING};

STATE stare_cur;

void init_servo(){
  servo_motor.attach(Servo_Usa_PIN);
  servo_motor.write(UNGHI_CLOSED);

  stare_cur = CLOSED_DOOR;
  UNGHI_CURR = 0;
  ultimul_time = 0;

  ultima_deschidere = 0;
}

void update_angle(int angle_to_reach, unsigned long time){
    if(time - ultimul_time < TIME_BETWEEN_STEPS)
      return;
    ultimul_time = time; 
    if(UNGHI_CURR < angle_to_reach){
       UNGHI_CURR += STEP_ANGLE;
       if(UNGHI_CURR >= angle_to_reach)
        UNGHI_CURR = angle_to_reach;
    }
    else{
      UNGHI_CURR -= STEP_ANGLE;
      if(UNGHI_CURR <= angle_to_reach)
        UNGHI_CURR = angle_to_reach;
    }

    servo_motor.write(UNGHI_CURR);

}

void DOOR_FSM(unsigned long time, int distanta_Ultrasonic){

    bool OBJECT_PROXI = false;

    if(distanta_Ultrasonic > 0 && distanta_Ultrasonic <= DISTANTA_USA_MAX)
      OBJECT_PROXI = true;
    else
      OBJECT_PROXI = false;
    
    switch(stare_cur){
      case CLOSED_DOOR:
        if(OBJECT_PROXI){
          stare_cur = OPENING_DOOR;
        }
        break;

      case OPENING_DOOR:
        update_angle(UNGHI_OPEN, time );
        if(UNGHI_CURR == UNGHI_OPEN ){
          ultima_deschidere = time;
          stare_cur = FULLY_OPEN_DOOR;
        }
        break;

      case FULLY_OPEN_DOOR:
        if(OBJECT_PROXI){
            ultima_deschidere = time;    
        }
        else if (time - ultima_deschidere > TIME_USA_OPEN){
          stare_cur = DOOR_CLOSING;
        }
        break;

      case DOOR_CLOSING:
        if(OBJECT_PROXI){
          stare_cur = OPENING_DOOR;
        }
        else{
          update_angle(UNGHI_CLOSED, time);
            if(UNGHI_CURR == UNGHI_CLOSED)
              stare_cur = CLOSED_DOOR;
        }
        
        break;
    }

}

STATE get_door_state(){
  return stare_cur;
}

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