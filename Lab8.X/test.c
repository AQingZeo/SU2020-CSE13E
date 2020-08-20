/* 
 * File:   test.c
 * Author: apple
 *
 * Created on August 8, 2020, 12:58 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Player.h"

/*
 * 
 */
void main() {
    int i,out;
    for(i=0;i<4;i++){
        out=AddToInventory(i);
        printf("%d",out);
    }
    out=FindInInventory(3);
    printf("%d",out);
    return;

}

