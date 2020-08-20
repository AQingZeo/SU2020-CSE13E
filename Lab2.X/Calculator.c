/*
 *File Name: Lab2 Calculator
 * Author: Zeo Zhang
 * Date: July 1st 2020 16:15
 * 
 * File Name: Calculator.c
 */

// Standard libraries
#include <stdio.h>
#include <math.h>


//User libraries:
#include "BOARD.h"
#include <string.h>
#include <stdlib.h>



// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Subtract(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double Divide(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double CelsiusToFahrenheit(double operand);
double AverageValue(double operand1, double operand2);
double Tangent(double operand);
double Round(double operand);
//add more prototypes here
double FirstIn();
double SecondIn();

void CalculatorRun(void) {
    printf("\n\nWelcome to Zeo's calculator program! Compiled at %s %s\n", __DATE__, __TIME__);

    // Your code here
    char in;
    double a, b, out;
    do {
        printf("\nEnter a mathematical opration to perform (*,/,+,-,a,m,f,c,t,r)(q to exit):");
        scanf(" %c", &in); //put user input into in
        if (in == '+') { // add 
            a = FirstIn();
            b = SecondIn();
            out = Add(a, b);
            printf("   Result of ( %f + %f ): %f\n", a, b, out);
        } else if (in == '-') { //substract
            a = FirstIn();
            b = SecondIn();
            out = Subtract(a, b);
            printf("   Result of ( %f - %f ): %f\n", a, b, out);
        } else if (in == '*') { //multiply
            a = FirstIn();
            b = SecondIn();
            out = Multiply(a, b);
            printf("   Result of ( %f * %f ): %f\n", a, b, out);
        } else if (in == '/') { //divide
            a = FirstIn();
            b = SecondIn();
            if (b == 0) { //check if divident is 0
                printf("   Divide By Zero Error!");
                continue; //exit current loop, continue next
            }
            out = Divide(a, b);
            printf("   Result of ( %f / %f ): %f\n", a, b, out);
        } else if (in == 'm') { // average
            a = FirstIn();
            b = SecondIn();
            out = AverageValue(a, b);
            printf("   Result of avg( %f , %f ): %f\n", a, b, out);
        } else if (in == 'a') { //absolute
            a = FirstIn();
            out = AbsoluteValue(a);
            printf("   Result of | %f |: %f\n", a, out);
        } else if (in == 'c') { //Cto F
            a = FirstIn();
            out = FahrenheitToCelsius(a);
            printf("   Result of (%f deg ->C): %f\n", a, out);
        } else if (in == 'f') { //F to C
            a = FirstIn();
            out = CelsiusToFahrenheit(a);
            printf("   Result of (%f deg ->F): %f\n", a, out);
        } else if (in == 't') { //tangent
            a = FirstIn();
            out = Tangent(a);
            printf("   Result of tan(%f): %f\n", a, out);
        } else if (in == 'r') { //round
            a = FirstIn();
            out = Round(a);
            printf("   Result of round(%f): %f\n", a, out);
        } else if (in == 'q') { //exit
            printf("   Thank you & Goodbye!\n");
            return;
        } else { // print error if operation not applicable
            printf("   Invalid operation!\n");
        }
    } while (1);
    while (1); // this while(1) can be removed as needed.
}

/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2) {
    return operand1 + operand2;
}

/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2) {
    return operand1 - operand2;
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2) {
    return operand1*operand2;
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2) {
    return operand1 / operand2;
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand) {
    if (operand < 0)
        return -operand;
    return operand;
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand) {
    return (operand - 32)*5 / 9;
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand) {
    return operand * 9 / 5 + 32;
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double AverageValue(double operand1, double operand2) {
    return (operand1 + operand2) / 2;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
double Tangent(double operand) {
    return tan(operand);
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand) {
    int a;
    operand += 0.5;
    a = (int) operand;
    return a;
}

double FirstIn() {
    char in[20] = "";
    int DotNum = 0;
    int i;
    double a;
    while (1) {
        printf("   Enter the first operand:  ");
        scanf(" %s", in);
        for (i = 0; i < strlen(in); i++) {
            if (in[0] == '-') { // allow the minus situation
                continue;
            }
            if (in[i] == '.') { //only one dot is allowed
                if (DotNum == 0)
                    DotNum = 1;
                else
                    break;
            }
            if (in[i] != '.' && (in[i] < '0' || in[i] > '9')) {
                break;
            }
        }
        if (i == strlen(in)) {
            a = atof(in); // change to double
            return a;
        } else
            printf("   Invalid Input!\n");
    }
}

double SecondIn() { // exactly same as first except welcome message
    char in[20] = "";
    int DotNum = 0;
    int i;
    double a;
    while (1) {
        printf("   Enter the second operand: ");
        scanf(" %s", in);
        for (i = 0; i < strlen(in); i++) {
            if (in[0] == '-') {
                continue;
            }
            if (in[i] == '.') {
                if (DotNum == 0)
                    DotNum = 1;
                else
                    break;
            }
            if (in[i] != '.' && (in[i] < '0' || in[i] > '9')) {
                break;
            }
        }
        if (i == strlen(in)) {
            a = atof(in);
            return a;
        } else
            printf("   Invalid Input!\n");
    }
}
