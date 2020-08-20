// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
#include <GenericTypeDefs.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Leds_Lab06.h"


// **** Declare any datatypes here ****

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****

#define MaxTimeA 2*38
#define MaxTimeB 3*38
#define MaxTimeC 5*38

struct Timer TimerA={FALSE,MaxTimeA};
struct Timer TimerB={FALSE,MaxTimeB};
struct Timer TimerC={FALSE,MaxTimeC};
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
    printf("Welcome to xzhan214's lab6 part1 (timers).  Compiled on %s %s.\n", __TIME__, __DATE__);
    
    LEDS_INIT();
    unsigned char out;

    while (1) {
        if(TimerA.event){
            printf("A ");
            out=LEDS_GET()^0x01;
            LEDS_SET(out);
            TimerA.event=FALSE;
            
        }
            //react to timer A events
            //clear timer A event flag
        if(TimerB.event){
            printf("B ");
            out=LEDS_GET()^0x02;
            LEDS_SET(out);
            TimerB.event=FALSE;
            
        }
        if(TimerC.event){
            printf("C ");
            out=LEDS_GET()^0x04;
            LEDS_SET(out);
            TimerC.event=FALSE;
            
        }
    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}

/**
 * This is the interrupt for the Timer1 peripheral. It will trigger at the frequency of the peripheral
 * clock, divided by the timer 1 prescaler and the interrupt interval.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;
    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    
    //update timerA
    TimerA.timeRemaining--;
    //if timerA has counted down,
    if(TimerA.timeRemaining==0 && TimerA.event==FALSE){
        TimerA.event=TRUE;
        TimerA.timeRemaining=MaxTimeA;
    }
        //generate timerA event
        //reset timerA
    TimerB.timeRemaining--;
    //if timerB has counted down,
    if(TimerB.timeRemaining==0&&TimerB.event==FALSE){
        TimerB.event=TRUE;
        TimerB.timeRemaining=MaxTimeB;
    }
    TimerC.timeRemaining--;
    //if timerC has counted down,
    if(TimerC.timeRemaining==0&&TimerC.event==FALSE){
        TimerC.event=TRUE;
        TimerC.timeRemaining=MaxTimeC;
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}