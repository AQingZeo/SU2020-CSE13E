/* 
 * File:   Buttons.c
 * Author: xzhan214
 *
 * Created on July 26, 2020, 5:29 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include "Buttons.h"
/*
 * 
 */

void ButtonsInit(void){
    //enable  the  D5/6/7  and  F1    pins  as  inputs
    TRISD=0x00E0;
    TRISF=0x0002;
}

uint8_t ButtonsCheckEvents(void){
    
    static uint8_t pre=0x00;
    static int count=0;
    count++;
    if(count<BUTTONS_DEBOUNCE_PERIOD){
        return BUTTON_EVENT_NONE;
    }
    count=0;
    uint8_t state=BUTTON_STATES();
    //if value changed the corresponding bit becomes 1
    uint8_t changed=state^pre; 
    //store output 
    uint8_t out=0x00;
    if(!(changed)){
        return BUTTON_EVENT_NONE;
    }
    if(changed&BUTTON_STATE_1){
        if(state&BUTTON_STATE_1){
            out |= BUTTON_EVENT_1DOWN;
        }else{
            out |= BUTTON_EVENT_1UP;
        }
    }
    if(changed&BUTTON_STATE_2){
        if(state&BUTTON_STATE_2){
            out |= BUTTON_EVENT_2DOWN;
        }else{
            out |= BUTTON_EVENT_2UP;
        }
    }
    if(changed&BUTTON_STATE_3){
        if(state&BUTTON_STATE_3){
            out |= BUTTON_EVENT_3DOWN;
        }else{
            out |= BUTTON_EVENT_3UP;
        }
    }
    if(changed&BUTTON_STATE_4){
        if(state&BUTTON_STATE_4){
            out |= BUTTON_EVENT_4DOWN;
        }else{
            out |= BUTTON_EVENT_4UP;
        }
    }
    pre=state;
    return out;
}