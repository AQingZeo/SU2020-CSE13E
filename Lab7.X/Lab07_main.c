// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CSE13E Support Library
#include "BOARD.h"
#include "Adc.h"
#include "Ascii.h"
#include "Buttons.h"
#include "Leds.h"
#include "Oled.h"
#include "OledDriver.h"
// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>



// **** Set any macros or preprocessor directives here ****
// Set a macro for resetting the timer, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)
#define TEMP_DEFAULT 350
#define TEMP_FIX 500
#define TIME_SECOND 5
//*between this and button comments are oven output*
#define OVEN_1_ON "|\x01\x01\x01\x01\x01|"
#define OVEN_1_OFF "|\x02\x02\x02\x02\x02|"
#define OVEN_2 "|     |"
#define OVEN_3 "|-----|"
#define OVEN_4_ON "|\x03\x03\x03\x03\x03|"
#define OVEN_4_OFF "|\x04\x04\x04\x04\x04|"
//*between this and top comments are oven output*
#define Minite(x) x/60
#define Second(x) x%60

// **** Set any local typedefs here ****

typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING
} OvenState;

typedef enum {
    BAKE, TOAST, BROIL
} MODE;

typedef enum {
    TIME, TEMP
} SELCT;

typedef struct {
    OvenState state;
    uint16_t temp; //indicate temperature
    MODE mode; //indicate cooking mode:bake,toast and broil
    //uint8_t btnTime;//indicate how long the button was pressed 
    uint16_t cookTime; //indicate the cook time left
    SELCT selector; //indicate which value is selected: temp/time 
} OvenData;

// **** Declare any datatypes here ****

struct isrRelated {
    uint8_t button;
    uint16_t runTime; //the time left to run when cooking
    uint16_t buttonTime; //temp store button pressed down FRT 
    uint8_t event; //check for event
};
struct adcEvent{
    uint8_t event;
    uint8_t adcRead;
};
// **** Define any module-level, global, or external variables here ****
static uint16_t freeRun = 0;
OvenData ovenData = {SETUP, TEMP_DEFAULT, BAKE, 0, TIME};
struct isrRelated isr = {0, 0, 0, TRUE};
struct adcEvent adc={FALSE,0};
static uint16_t setCookTime=0;//store the total cooking time
// **** Put any helper functions here ****

void updateLED(OvenData ovenData) {
    if (isr.runTime < 5) {
        LEDS_SET(0x00);
        return;
    }
    int unit = setCookTime*TIME_SECOND / 8; //time per led
    int shift = ((setCookTime*TIME_SECOND) - isr.runTime) / unit;
    if(shift==0){
        LEDS_SET(0xFF);
    }else if(isr.runTime<=TIME_SECOND){
        //because when cookTime reach to 0 jump to reset, before get to 0, led off
        LEDS_SET(0x00);
    }else{
        LEDS_SET(LEDS_GET()&(0xFF << shift));
    }
    return;
}

/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData) {
    //update OLED here
    char out[80];
    OledClear(OLED_COLOR_BLACK);
    switch (ovenData.mode) {
        case BAKE:
            if (ovenData.state == SETUP || ovenData.state == SELECTOR_CHANGE_PENDING) {
                if (ovenData.selector) {//selector at temp
                    sprintf(out, "%s Mode: BAKE\n%s Time: %d:%02d\n"
                            "%s>Temp: %d%s\n%s", OVEN_1_OFF, OVEN_2, Minite(ovenData.cookTime),
                            Second(ovenData.cookTime), OVEN_3, ovenData.temp, DEGREE_SYMBOL, OVEN_4_OFF);
                } else {//selector at time
                    sprintf(out, "%s Mode: BAKE\n%s>Time: %d:%02d\n"
                            "%s Temp: %d%s\n%s", OVEN_1_OFF, OVEN_2, Minite(ovenData.cookTime),
                            Second(ovenData.cookTime),
                            OVEN_3, ovenData.temp, DEGREE_SYMBOL, OVEN_4_OFF);
                }
            } else {//is cooking or reset pending (oven is on)
                sprintf(out, "%s Mode: BAKE\n%s Time: %d:%02d\n"
                        "%s Temp: %d%s\n%s", OVEN_1_ON, OVEN_2, Minite(ovenData.cookTime),
                        Second(ovenData.cookTime),
                        OVEN_3, ovenData.temp, DEGREE_SYMBOL, OVEN_4_ON);
            }
            break;
        case TOAST:
            if (ovenData.state == SETUP|| ovenData.state == SELECTOR_CHANGE_PENDING) {
                //no selector only oven difference 
                sprintf(out, "%s Mode: TOAST\n%s Time: %d:%02d\n"
                        "%s\n%s", OVEN_1_OFF, OVEN_2, Minite(ovenData.cookTime),
                        Second(ovenData.cookTime), OVEN_3, OVEN_4_OFF);
            } else {
                sprintf(out, "%s Mode: TOAST\n%s Time: %d:%02d\n"
                        "%s\n%s", OVEN_1_OFF, OVEN_2, Minite(ovenData.cookTime),
                        Second(ovenData.cookTime), OVEN_3, OVEN_4_ON);
            }
            break;
        case BROIL:
            if (ovenData.state == SETUP|| ovenData.state == SELECTOR_CHANGE_PENDING) {
                //no selector only oven difference 
                sprintf(out, "%s Mode: BROIL\n%s Time: %d:%02d\n"
                        "%s Temp: %d%s\n%s", OVEN_1_OFF, OVEN_2, Minite(ovenData.cookTime),
                        Second(ovenData.cookTime), OVEN_3, TEMP_FIX, DEGREE_SYMBOL, OVEN_4_OFF);
            } else {
                sprintf(out, "%s Mode: BROIL\n%s Time: %d:%02d\n"
                        "%s Temp: %d%s\n%s", OVEN_1_ON, OVEN_2, Minite(ovenData.cookTime),
                        Second(ovenData.cookTime), OVEN_3, TEMP_FIX, DEGREE_SYMBOL, OVEN_4_OFF);
            }
            break;
    }
    OledDrawString(out);
    OledUpdate();
}

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void) {
    //write your SM logic here.
    switch (ovenData.state) {
        case SETUP:
            if (adc.event) {
                if (ovenData.mode == BAKE) {
                    if (ovenData.selector == TEMP) {
                        ovenData.temp = adc.adcRead + 300;
                    } else {
                        ovenData.cookTime = adc.adcRead + 1;
                    }
                }else{
                    ovenData.cookTime=adc.adcRead + 1;
                }
                updateOvenOLED(ovenData);
                adc.event=FALSE;
                break;
            } 
            if (isr.button & BUTTON_EVENT_3DOWN) {
                isr.buttonTime = freeRun;
                ovenData.state = SELECTOR_CHANGE_PENDING;
                break;
            }
            if (isr.button & BUTTON_EVENT_4DOWN) {
                isr.runTime = ovenData.cookTime * TIME_SECOND;
                setCookTime=ovenData.cookTime;
                updateLED(ovenData);
                updateOvenOLED(ovenData);
                ovenData.state = COOKING;
                break;
            }
        case COOKING:
            if (isr.button & BUTTON_EVENT_4DOWN) {
                isr.buttonTime = freeRun;
                ovenData.state = RESET_PENDING;
                break;
            } else {
                if (isr.runTime != 0) {
                    ovenData.cookTime=isr.runTime/TIME_SECOND;
                    updateLED(ovenData);
                    updateOvenOLED(ovenData);
                    break;
                } else {//reset oven
                    ovenData.cookTime = 1; //minimum =1 second
                    isr.runTime = 0;
                    setCookTime=0;
                    updateOvenOLED(ovenData);
                    ovenData.state = SETUP;
                    ovenData.mode = BAKE;
                    break;
                }
            }
        case SELECTOR_CHANGE_PENDING:
            if (isr.button & BUTTON_EVENT_3UP) {
                if ((freeRun - isr.buttonTime) >= TIME_SECOND && ovenData.mode == BAKE) {
                    //only bake mode can switch selector
                    if (ovenData.selector == TIME) {
                        ovenData.selector = TEMP;
                    } else {
                        ovenData.selector = TIME;
                    }
                } else if((freeRun - isr.buttonTime) < TIME_SECOND){
                    if (ovenData.mode == BROIL) {
                        ovenData.mode = BAKE;
                    } else {
                        ovenData.mode++;
                    }
                }
                updateOvenOLED(ovenData);
                ovenData.state = SETUP;
                break;
            }
        case RESET_PENDING:
            if (isr.button & BUTTON_EVENT_4UP) {
                if ((freeRun - isr.buttonTime) >= TIME_SECOND) {
                    //reset oven
                    ovenData.cookTime=isr.runTime/TIME_SECOND;
                    isr.runTime = 0;
                    setCookTime=0;
                    ovenData.state = SETUP;
                    updateLED(ovenData);
                    updateOvenOLED(ovenData);
                    break;
                } else {
                    ovenData.cookTime=isr.runTime/TIME_SECOND;
                    updateLED(ovenData);
                    updateOvenOLED(ovenData);
                    ovenData.state = COOKING;
                    break;
                }
            }
    }
}

int main() {
    BOARD_Init();

    //initalize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">

    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>

    printf("Welcome to xzhan214's Lab07 (Toaster Oven).  Compiled on %s %s.", __TIME__, __DATE__);

    //initialize state machine (and anything else you need to init) here
    OledInit();
    AdcInit();
    LEDS_INIT();

    while (1) {
        if (isr.event) {
            runOvenSM();
            isr.event = FALSE;
        }
        // Add main loop code here:
        // check for events
        // on event, run runOvenSM()
        // clear event flags
    };
}

/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void) {
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;

    //add event-checking code here
    static int cnt = 0; //count if =5 a second, display changed
    freeRun++;
    if (ovenData.state == COOKING || ovenData.state == RESET_PENDING) {
        isr.runTime--;
        cnt++;
    }
    if (cnt == TIME_SECOND) {
        isr.event = TRUE;
        cnt = 0;
    }
}

/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void) {
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    //add event-checking code here
    isr.button = ButtonsCheckEvents();
    if(AdcChanged()){
        adc.event=TRUE;
        adc.adcRead=AdcRead()>>2;
    }
    if (isr.button != BUTTON_EVENT_NONE || adc.event) {
        isr.event = TRUE;
    }



}