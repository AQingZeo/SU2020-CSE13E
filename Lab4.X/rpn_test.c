// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

int main() {
    BOARD_Init();
    int error;

    printf("\n###### Beginning xzhan214's rpn test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!
    //Test calculation
    char test0[] = "1 1 +";
    double result0;
    double expected0 = 2;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test0);
    error = RPN_Evaluate(test0, &result0);
    printf("\nResult: %f", result0);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result0 != expected0) {
        printf("   Failed, expected = %f , result = %f\n", expected0, result0);
    } else {
        printf("   Success!\n");
    }
    char test1[] = "3 3 / 2 + 6 * 2 / 4 - 2.5 /";
    double expected1 = 2;
    printf("\nTesting RPN_Evaluate with \"%s\"... \n ", test1);
    error = RPN_Evaluate(test1, &result0);
    printf("\nResult: %f", result0);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result0 != expected1) {
        printf("   Failed, expected = %f , result = %f\n", expected1, result0);
    } else {
        printf("   Success!\n");
    }
    //Test Error
    char test2[] = " 3 3 3 +";
    printf("\nTesting RPN_Evaluate with too many items error \n ");
    error = RPN_Evaluate(test2, &result0);
    if (error == 6) {
        printf("Success!\n");
    } else {
        printf("Failed\n");
    }
    char test3[] = " ";
    printf("\nTesting RPN_Evaluate with too few items error \n ");
    error = RPN_Evaluate(test3, &result0);
    if (error == 5) {
        printf("Success!\n");
    } else {
        printf("Failed\n");
    }
    char test4[] = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21";
    printf("\nTesting RPN_Evaluate with overflow error \n ");
    error = RPN_Evaluate(test4, &result0);
    if (error == 1) {
        printf("Success!\n");
    } else {
        printf("Failed\n");
    }
    char test5[] = "+";
    printf("\nTesting RPN_Evaluate with underflow error \n ");
    error = RPN_Evaluate(test5, &result0);
    if (error == 2) {
        printf("Success!\n");
    } else {
        printf("Failed\n");
    }
    char test6[] = "hello 7";
    printf("\nTesting RPN_Evaluate with invalid token error \n ");
    error = RPN_Evaluate(test6, &result0);
    if (error == 3) {
        printf("Success!\n");
    } else {
        printf("Failed\n");
    }
    char test7[] = "9 0 /";
    printf("\nTesting RPN_Evaluate with divide by zero error \n ");
    error = RPN_Evaluate(test7, &result0);
    if (error == 4) {
        printf("Success!\n");
    } else {
        printf("Failed\n");
    }


    printf("Testing ProcessBackspaces:\n");
    printf("Test with 1 backspace at middle\n");
    char test_pb1[] = "123\b34";
    ProcessBackspaces(test_pb1);
    printf("result    : %s\n", test_pb1);
    printf("should be : 1234\n");

    printf("Test with 1 backspace at beginning\n");
    char test_pb2[] = "\b1234";
    ProcessBackspaces(test_pb2);
    printf("result    : %s\n", test_pb2);
    printf("should be : 1234\n");

    printf("Test with 2 continuous backspace in middle\n");
    char test_pb3[] = "12\b\b1234";
    ProcessBackspaces(test_pb3);
    printf("result    : %s\n", test_pb3);
    printf("should be : 1234\n");

    printf("Test with 2 backspace one will exceed (one useless)\n");
    char test_pb4[] = "1\b\b1234";
    ProcessBackspaces(test_pb4);
    printf("result    : %s\n", test_pb4);
    printf("should be : 1234\n");
    BOARD_End();
    while (1);
}


