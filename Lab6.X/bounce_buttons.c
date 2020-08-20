// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Buttons.h"
#include "Leds_Lab06.h"
// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****
struct Button{
    uint8_t event;//store button's event
    uint8_t state;//store if there is button event
};
// **** Define global, module-level, or external variables here ****
struct Button Button={0x00,FALSE};

//define sets of led to light up
#define LED1 0x03
#define LED2 0x0C
#define LED3 0x30
#define LED4 0xC0
// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 1; // 1:8 prescaler
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
    printf("Welcome to xzhan214's lab6 part5 (bounce_buttons).  Compiled on %s %s.\n", __TIME__, __DATE__);
    LEDS_INIT();
    while(1){
        uint8_t switchState=SWITCH_STATES();
        uint8_t out=0x00;
        if(Button.state){
            if((switchState & SWITCH_STATE_SW1)&&Button.event&BUTTON_EVENT_1UP){
                out^=LED1;
            }else if(!(switchState & SWITCH_STATE_SW1)&&Button.event&BUTTON_EVENT_1DOWN){
                out^=LED1;
            }
            if((switchState & SWITCH_STATE_SW2)&&Button.event&BUTTON_EVENT_2UP){
                out^=LED2;
            }else if(!(switchState & SWITCH_STATE_SW2)&&Button.event&BUTTON_EVENT_2DOWN){
                out^=LED2;
            }
            if((switchState & SWITCH_STATE_SW3)&&Button.event&BUTTON_EVENT_3UP){
                out^=LED3;
            }else if(!(switchState & SWITCH_STATE_SW3)&&Button.event&BUTTON_EVENT_3DOWN){
                out^=LED3;
            }
            if((switchState & SWITCH_STATE_SW4)&&Button.event&BUTTON_EVENT_4UP){
                out^=LED4;
            }else if(!(switchState & SWITCH_STATE_SW4)&&Button.event&BUTTON_EVENT_4DOWN){
                out^=LED4;
            }
            Button.state=FALSE;
        }
        LEDS_SET(out);
    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

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
    Button.event=ButtonsCheckEvents();
    if(Button.event !=  BUTTON_EVENT_NONE ){
        //Button.event=event;
        Button.state=TRUE;
    }
    
    

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}