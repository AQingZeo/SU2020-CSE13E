/* 
 * File:   Player.c
 * Author: Zeo Zhang(xzhan214)
 *
 * Created on August 5, 2020, 10:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Player.h"

/*
 * 
 */
uint8_t inventory[INVENTORY_SIZE];
int AddToInventory(uint8_t item){
    int i;
    for(i=0;i<INVENTORY_SIZE;i++){
        if(inventory[i]=='\0'){
            inventory[i]=item;
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}
int FindInInventory(uint8_t item){
    int i;
    for(i=0;i<INVENTORY_SIZE;i++){
        if(inventory[i]==item){
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}
