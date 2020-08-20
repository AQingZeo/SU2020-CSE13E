/* 
 * File:   Game.c
 * Author: Zeo Zhang(xzhan214)
 *
 * Created on August 5, 2020, 10:17 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Game.h"
#include "Player.h"
/*
 * 
 */
struct roomInfo{
    char title[GAME_MAX_ROOM_TITLE_LENGTH+1];
    char desc[GAME_MAX_ROOM_DESC_LENGTH+1];
    uint8_t east;
    uint8_t south;
    uint8_t west;
    uint8_t north;
}roomInfo;

//set macros:
static uint8_t room;
static char fileName[25];
static FILE *file;
#define EXIT_LEN 4
int Open(uint8_t room);
void PassVersion(FILE *file){
    uint8_t descLen=fgetc(file);
    fseek(file,descLen,SEEK_CUR);
    uint8_t itemLen=fgetc(file);
    fseek(file,itemLen+EXIT_LEN,SEEK_CUR);
}
int Open(uint8_t room){
    sprintf(fileName,"RoomFiles/room%d.txt",room);
    file=fopen(fileName,"rb");
    if(file==NULL){
        return STANDARD_ERROR;
    }
    fseek(file,3,SEEK_SET);
    uint8_t titleLen=fgetc(file);//length of title
    fread(roomInfo.title,titleLen,1,file);//read title
    roomInfo.title[titleLen]='\0';
    while(1){
        uint8_t requireLen=fgetc(file);//length of required item
        int i;
        uint8_t match=0;//store # of matched item
        for(i=0;i<requireLen;i++){
            if(FindInInventory(fgetc(file))){
                match++;
            }
        }
        if(match!=requireLen){
            PassVersion(file);
            continue;
        }
        uint8_t descLen=fgetc(file);//length of description
        fread(roomInfo.desc,descLen,1,file);
        roomInfo.desc[descLen]='\0';
        uint8_t containLen=fgetc(file);//length of contained items
        for(i=0;i<containLen;i++){
            if(!AddToInventory(fgetc(file))){
                return STANDARD_ERROR;
            }
        }
        roomInfo.north=fgetc(file);
        roomInfo.east=fgetc(file);
        roomInfo.south=fgetc(file);
        roomInfo.west=fgetc(file);
        fclose(file);
        return SUCCESS;
        break;
    }
    return STANDARD_ERROR;
}

int GameGoNorth(void){
    if(roomInfo.north){
        Open(roomInfo.north);
        return SUCCESS;
    }
    return STANDARD_ERROR;
}
int GameGoEast(void){
    if(roomInfo.east){
        Open(roomInfo.east);
        return SUCCESS;
    }
    return STANDARD_ERROR;
}
int GameGoSouth(void){
    if(roomInfo.south){
        Open(roomInfo.south);
        return SUCCESS;
    }
    return STANDARD_ERROR;
}
int GameGoWest(void){
    if(roomInfo.west){
        Open(roomInfo.west);
        return SUCCESS;
    }
    return STANDARD_ERROR;
}

int GameInit(void){
    room=STARTING_ROOM;
    if(Open(room)){
        return SUCCESS;
    }
    return STANDARD_ERROR;
}
int GameGetCurrentRoomTitle(char *title){
    strcpy(title,roomInfo.title);
    return strlen(title);
}
int GameGetCurrentRoomDescription(char *desc){
    strcpy(desc,roomInfo.desc);
    return strlen(desc);
}
uint8_t GameGetCurrentRoomExits(void){
    uint8_t exit='\0';
    if(roomInfo.south){
        exit|=GAME_ROOM_EXIT_SOUTH_EXISTS;
    }
    if(roomInfo.north){
        exit|=GAME_ROOM_EXIT_NORTH_EXISTS;
    }
    if(roomInfo.west){
        exit|=GAME_ROOM_EXIT_WEST_EXISTS;
    }
    if(roomInfo.east){
        exit|=GAME_ROOM_EXIT_EAST_EXISTS;
    }
    return exit;        
}


