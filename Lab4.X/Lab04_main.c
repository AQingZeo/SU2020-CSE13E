// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60

int main() {
    BOARD_Init();

    //What follows is starter code.  You will need to modify it!

    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;
    int er; //store error number

    printf("Welcome to xzhan214'S RPN calculator.  Compiled on %s %s", __DATE__, __TIME__);
    while (1) {

        printf("Enter floats and + - / * in RPN format:\n");

        fgets(rpn_sentence, sizeof (rpn_sentence), stdin);
        
        if(sizeof(rpn_sentence)>MAX_INPUT_LENGTH){
            printf("Entered too many characters(>60)!");
            break;
        }
        ProcessBackspaces(rpn_sentence);
        er = RPN_Evaluate(rpn_sentence, &result);
        switch (er) {
            case '0':
                printf("result = %f\n", result);
                break;
            case '1':
                printf("Stack Overflow: Entered too many values!\n");
                break;
            case '2':
                printf("Stack Underflow: No Operand to Calculate!\n");
                break;
            case '3':
                printf("Invalid Token: invalid inputs!\n");
                break;
            case '4':
                printf("Divide by zero!\n");
                break;
            case '5':
                printf("Too Few Item: Not enough operand to calculate!\n");
                break;
            case '6':
                printf("Too Many Item: Entered more than 2 operand for 1 calculation!\n");
                break;
            default:
                printf("There is an undetected error");
        }

    }

    while (1);
}
