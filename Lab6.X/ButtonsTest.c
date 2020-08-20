// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Buttons.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****
struct ButtonState{
    uint8_t event; //store the event to print
    uint8_t state; //store T/F (if there is a event to print)
};
// **** Define global, module-level, or external variables here ****
struct ButtonState Button={0x00,FALSE};
// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 2; // 1:64 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to xzhan214's lab6 part4 (ButtonsTest).  Compiled on %s %s.\n", __TIME__, __DATE__);

    
    printf("Please press some buttons!\n");
    while(1){
        char one[]="----";
        char two[]="----";
        char three[]="----";
        char four[]="----";
        
        if(Button.state==TRUE){
            if(Button.event&BUTTON_EVENT_1UP){
                sprintf(one,"UP");
            }
            if(Button.event&BUTTON_EVENT_1DOWN){
                sprintf(one,"DOWN");
            }
            if(Button.event&BUTTON_EVENT_2UP){
                sprintf(two,"UP");
            }
            if(Button.event&BUTTON_EVENT_2DOWN){
                sprintf(two,"DOWN");
            }
            if(Button.event&BUTTON_EVENT_3UP){
                sprintf(three,"UP");
            }
            if(Button.event&BUTTON_EVENT_3DOWN){
                sprintf(three,"DOWN");
            }
            if(Button.event&BUTTON_EVENT_4UP){
                sprintf(four,"UP");
            }
            if(Button.event&BUTTON_EVENT_4DOWN){
                sprintf(four,"DOWN");
            }
            printf("EVENT:1.%s 2.%s 3.%s 4.%s\n",one,two,three,four);
            Button.state=FALSE;
        }
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. It should check for button events and stores them in a
 * module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    ButtonsInit();
    uint8_t event=ButtonsCheckEvents();
    if(event !=  BUTTON_EVENT_NONE && Button.state==FALSE ){
        Button.event=event;
        Button.state=TRUE;
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}