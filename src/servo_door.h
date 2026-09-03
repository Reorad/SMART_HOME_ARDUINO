#ifndef SERVO_DOOR_H
#define SERVO_DOOR_H

enum STATE {CLOSED_DOOR, OPENING_DOOR, FULLY_OPEN_DOOR, DOOR_CLOSING};
    



// CONSTANTS TO BE USED FOR THE DOOR ANGLE
const int UNGHI_OPEN = 90;
const int UNGHI_CLOSED = 0;
const int STEP_ANGLE = 2;

const int DISTANTA_USA_MAX = 30;
const int TIME_USA_OPEN = 5000;
const int TIME_BETWEEN_STEPS = 20;

void init_servo();
void DOOR_FSM(unsigned long time, int distanta_Ultrasonic);
STATE get_door_state();

#endif