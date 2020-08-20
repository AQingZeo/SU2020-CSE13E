// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CSE013E Support Library
#include "UNIXBOARD.h"
#include "Game.h"


// User libraries


// **** Set any macros or preprocessor directives here ****
// **** Declare any data types here ****

struct Room {
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char desc[GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t exit;
    char next; //store the user's next direction option 
} room;
// **** Define any global or external variables here ****
static uint8_t gameState = 1;
// **** Declare any function prototypes here ****

int main() {



    /******************************** Your custom code goes below here ********************************/
    printf("Welcome to xzhan214's RPG game\n");
    if (!GameInit()) {
        FATAL_ERROR();
    }
    while (gameState) {
        if(!GameGetCurrentRoomTitle(room.title)){
            FATAL_ERROR();
        }
        if(!GameGetCurrentRoomDescription(room.desc)){
            FATAL_ERROR();
        }
        printf("\n\n%s\n%s\n\n", room.title, room.desc);
        room.exit = GameGetCurrentRoomExits();
        printf("exit:");
        if (room.exit & GAME_ROOM_EXIT_NORTH_EXISTS) {
            printf("N ");
        }
        if (room.exit & GAME_ROOM_EXIT_EAST_EXISTS) {
            printf("E ");
        }
        if (room.exit & GAME_ROOM_EXIT_SOUTH_EXISTS) {
            printf("S ");
        }
        if (room.exit & GAME_ROOM_EXIT_WEST_EXISTS) {
            printf("W ");
        }
        while (1) {
            printf("\nEnter direction(n,e,s,w) to go forward, or q to quit: ");
            room.next = getchar();
            getchar(); //to clear the empty one
            if (room.next == 'n') {
                if(!(room.exit&GAME_ROOM_EXIT_NORTH_EXISTS)){
                    printf("\nInvalid direction!\n");
                }
                else if (!GameGoNorth()) {
                    FATAL_ERROR();
                } else {
                    break;
                }
            } else if (room.next == 'e') {
                if(!(room.exit&GAME_ROOM_EXIT_EAST_EXISTS)){
                    printf("\nInvalid direction!\n");
                }
                else if (!GameGoEast()) {
                    FATAL_ERROR();
                } else {
                    break;
                }
            } else if (room.next == 's') {
                if(!(room.exit&GAME_ROOM_EXIT_SOUTH_EXISTS)){
                    printf("\nInvalid direction!\n");
                }
                else if (!GameGoSouth()) {
                    FATAL_ERROR();
                } else {
                    break;
                }
            } else if (room.next == 'w') {
                if(!(room.exit&GAME_ROOM_EXIT_WEST_EXISTS)){
                    printf("\nInvalid direction!\n");
                }
                else if (!GameGoWest()) {
                    FATAL_ERROR();
                } else {
                    break;
                }
            } else if (room.next == 'q') {
                printf("\nThank you Goodbye\n");
                gameState = 0;
                break; //just to make sure
            } else {
                printf("\nInvalid input: %c\n", room.next);
            }
        }
    }


    /**************************************************************************************************/
}

