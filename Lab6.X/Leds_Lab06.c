/* 
 * File:   Leds_Lab06.c
 * Author: xzhan214
 *
 * Created on July 24, 2020, 8:57 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Leds_Lab06.h"
#include "BOARD.h"

/*
 * 
 */
void LEDS_INIT(void){
    TRISE=0x00;//Port as output 
    LATE=0x00;//Initialize port with 0
}
void LEDS_SET(char newPattern){
    LATE=newPattern;
}
char LEDS_GET(void){
    return LATE;
}