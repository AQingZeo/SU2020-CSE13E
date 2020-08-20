
// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>					


//CMPE13 Support Library
#include "BOARD.h"
#include "Leds_Lab06.h"
// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// **** Declare any datatypes here ****
struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
#define LEFT(x) x<<1
#define RIGHT(x) x>>1
#define MaxTime 38
#define init 0x01

struct Timer TimerS={FALSE,MaxTime};												 

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
    printf("Welcome to xzhan214's lab6 part2 (bounce_switch).  Compiled on %s %s.\n",__TIME__,__DATE__);
    LEDS_INIT();
	unsigned char out=init;		
    int state=0;
	while(1){
        //poll timer events and react if any occur
        if(TimerS.event){
            LEDS_SET(out);
            if(LATEbits.LATE7==1){//reach left end
                out=RIGHT(out);
                state=1;
            }else if(LATEbits.LATE0==1){//reach right end
                out=LEFT(out);
                state=0;
            }else if(LATEbits.LATE7!=1&&LATEbits.LATE0!=1&&state){
                //going right
                out=RIGHT(out);
            }else{
                //going left
                out=LEFT(out);
            }
            TimerS.event=FALSE;
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
    int state = SWITCH_STATES();
    int speed=MaxTime;
    if(state!=0){
        speed=MaxTime/(state*2);
    }
    TimerS.timeRemaining-=speed;
    if(TimerS.timeRemaining<=0 && TimerS.event==FALSE){
        TimerS.event=TRUE;
        TimerS.timeRemaining=MaxTime;
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/									
	 
}