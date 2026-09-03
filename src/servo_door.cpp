#include "servo_door.h"
#include "pini.h"
#include <Servo.h>

static Servo servo_motor;
static STATE stare_cur;
static int UNGHI_CURR = 0;
static unsigned long ultimul_time = 0;
static unsigned long ultima_deschidere = 0;

static void update_angle(int angle_to_reach, unsigned long time){
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


void init_servo(){
  servo_motor.attach(Servo_Usa_PIN);
  servo_motor.write(UNGHI_CLOSED);

  stare_cur = CLOSED_DOOR;
  UNGHI_CURR = 0;
  ultimul_time = 0;

  ultima_deschidere = 0;
}



STATE get_door_state(){
  return stare_cur;
}