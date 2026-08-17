#include "proxi_alerta.h"

static uint8_t citiri_confirmate = 0;
static bool alerta_activata_flag = false;
static unsigned long start_time = 0;

void alerta_init() {
    citiri_confirmate = 0;
    alerta_activata_flag = false;
    start_time = 0;
}

void alerta_update(unsigned long time, unsigned int distanta){

    bool distance_range ;

    if (distanta > 0 && distanta <= ALERTA_DISTANTA) {
        distance_range = true;
    } else {
        distance_range = false;
    }

    if(distance_range){
        if(citiri_confirmate < Confirm_trigger){
            citiri_confirmate++;
        }
        
    }
    else{
            citiri_confirmate = 0;
        }

    if(citiri_confirmate >= Confirm_trigger){
        alerta_activata_flag = true;
        start_time = time;
    }
    else if(alerta_activata_flag && (time - start_time >= Durata_Alerta)){
        alerta_activata_flag = false;
    }
}

bool alerta_activata(){
    return alerta_activata_flag;
}