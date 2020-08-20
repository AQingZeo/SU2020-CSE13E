/* 
 * File:   test.c
 * Author: apple
 *
 * Created on July 24, 2020, 11:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Leds_Lab06.h"
/*
 * 
 */
int main(void) {
    LEDS_INIT();
    LEDS_SET(0xCC);
    int i;
    unsigned char x;
    x=LEDS_GET();
    for (i = 0; i < 1000000; i++); 
    LEDS_SET(0xDD);
    for (i = 0; i < 1000000; i++);
    LEDS_SET(0);
    for (i = 0; i < 1000000; i++); 
    LEDS_SET(x);
    
    return 0;
}

