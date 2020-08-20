// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Leds_Lab06.h"
#include "Buttons.h"
#include "Oled.h"
// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****
struct Button{
    uint8_t event;//store button's event
    uint8_t state;//store if there is button event
    uint8_t switchState;//store switch up/down up FALSE down TRUE
}; 
struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};
struct AdcResult{
    uint8_t event;
    uint16_t voltage;
};
// **** Define global, module-level, or external variables here ****
#define SIZE_WINDOW 5
#define NUM_OF_IN 8
#define Percent(x) x/10.23
#define LEFT(x) x<<1
#define RIGHT(x) x>>1
#define MaxTime 38
#define init 0x01
#define LED1 0x03
#define LED2 0x0C
#define LED3 0x30
#define LED4 0xC0
struct Button Button={0x00,FALSE,FALSE};
struct Timer TimerS={FALSE,MaxTime};												 
struct AdcResult Result={FALSE,0};
int prev=0;//store the previous detected value in ISR
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


    // Enable interrupts for the ADC
    IPC6bits.AD1IP = 2;
    IPC6bits.AD1IS = 0;
    IEC1bits.AD1IE = 1;

    // Set B2 to an input so AN2 can be used by the ADC.
    TRISBbits.TRISB2 = 1;

    // Configure and start the ADC
    AD1CHSbits.CH0SA = 2; // add B2 to the mux
    AD1PCFGbits.PCFG2 = 0; // add b2 to the ADC
    AD1CSSLbits.CSSL2 = 1; // and add b2 to the scanner

    AD1CON1 = 0; // start with 0
    AD1CON1bits.SSRC = 0b111; // auto conversion
    AD1CON1bits.ASAM = 1; // auto sample

    AD1CON2 = 0; // start with 0
    AD1CON2bits.SMPI = 7; // one interrupt per 8 samples

    AD1CON3 = 0; // start with 0
    AD1CON3bits.SAMC = 29; // long sample time
    AD1CON3bits.ADCS = 50; // long conversion time

    AD1CON1bits.ADON = 1; // and finally turn it on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to xzhan214's lab6 part6 (Extra Credit).  Compiled on %s %s.\n",__TIME__,__DATE__);
    LEDS_INIT();
    unsigned char set;
	unsigned char out=init;		
    int state=0;
    char welcome[]="Potentiometer value:\n";
    char read[50];
    OledInit();
	while(1){
        if(Result.event==TRUE){
            OledClear(OLED_COLOR_BLACK);
            OledDrawString(welcome);
            OledUpdate();
            sprintf(read,"\n%d\n%.2f %%",(int)Result.voltage,Percent((float)Result.voltage));
            OledDrawString(read);
            OledUpdate();
            read[0]='\0';
            Result.event=FALSE;
        }
        //poll timer events and react if any occur
        if(TimerS.event){
            set=LEDS_GET()^out;
            LEDS_SET(set);
            if(LATEbits.LATE7==1){//reach left end
                out=RIGHT(out);
                state=1;
            }else if(LATEbits.LATE0==1){//reach right end
                out=LEFT(out);
                state=0;
            }else if(state){
                //going right
                out=RIGHT(out);
            }else{
                //going left
                out=LEFT(out);
            }
            TimerS.event=FALSE;
        }
        if(Button.state){
            if(Button.switchState==TRUE){//down trigger
                if(Button.event&BUTTON_EVENT_1DOWN){
                    set=LEDS_GET()^LED1;
                    LEDS_SET(set);
                }
                if(Button.event&BUTTON_EVENT_2DOWN){
                    set=LEDS_GET()^LED2;
                    LEDS_SET(set);
                }
                if(Button.event&BUTTON_EVENT_3DOWN){
                    set=LEDS_GET()^LED3;
                    LEDS_SET(set);
                }
                if(Button.event&BUTTON_EVENT_4DOWN){
                    set=LEDS_GET()^LED4;
                    LEDS_SET(set);
                }
            }else{//up trigger when switch up
                if(Button.event&BUTTON_EVENT_1UP){
                    set=LEDS_GET()^LED1;
                    LEDS_SET(set);
                }
                if(Button.event&BUTTON_EVENT_2UP){
                    set=LEDS_GET()^LED2;
                    LEDS_SET(set);
                }
                if(Button.event&BUTTON_EVENT_3UP){
                    set=LEDS_GET()^LED3;
                    LEDS_SET(set);
                }
                if(Button.event&BUTTON_EVENT_4UP){
                    set=LEDS_GET()^LED4;
                    LEDS_SET(set);
                }
            }
            Button.state=FALSE;
        }
    }			


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral.
 */
void __ISR(_TIMER_1_VECTOR, IPL4AUTO) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;
    
    ButtonsInit();
    uint8_t event=ButtonsCheckEvents();
    uint8_t switchState=SWITCH_STATES();
    if(switchState&SWITCH_STATE_SW1){
        Button.switchState=TRUE;
    }
    if(event !=  BUTTON_EVENT_NONE && Button.state==FALSE ){
        Button.event=event;
        Button.state=TRUE;
    }
    


}

/**
 * This is the ISR for the ADC1 peripheral.
 */
void __ISR(_ADC_VECTOR, IPL2AUTO) AdcHandler(void)
{
    // Clear the interrupt flag.
    IFS1bits.AD1IF = 0;
    
    
    Result.voltage=(ADC1BUF0+ADC1BUF1+ADC1BUF2+ADC1BUF3\
+ADC1BUF4+ADC1BUF5+ADC1BUF6+ADC1BUF7)/NUM_OF_IN;
    if(abs(Result.voltage-prev)>=SIZE_WINDOW&&Result.event==FALSE){
        prev=Result.voltage;
        Result.event=TRUE;
    }
    int speed=MaxTime*(int)Percent((float)Result.voltage);
    TimerS.timeRemaining-=speed;
    if(TimerS.timeRemaining<=0 && TimerS.event==FALSE){
        TimerS.event=TRUE;
        TimerS.timeRemaining=MaxTime;
    }


}