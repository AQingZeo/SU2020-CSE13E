/* 
 * File:   part0.c
 * Author: Zeo Zhang
 *
 * Created on June 25, 2020, 00:46
 */

#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"

/*
 * 
 */
int main(void) {
    BOARD_Init();
    printf("Hello World!");
            
#ifdef PIC32
    while(1);
#else
    return 0;
#endif
}

