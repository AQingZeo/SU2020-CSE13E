/* 
 * File:   rpn.c
 * Author: xzhan214
 *
 * Created on July 14, 2020, 1:38 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rpn.h"
#include "stack.h"

int RPN_Evaluate(char * rpn_string, double * result) {
    char *token;
    double operand1 = 0.0, operand2 = 0.0; //operand to be calculated
    int x; //check if the input is integer or float x for error checking
    double f; //store float value
    struct Stack stack = {};
    StackInit(&stack);
    //push/identify the first item
    token = strtok(rpn_string, " ");
    if (token==NULL){
        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
    }
    f = atof(token);
    if (f != 0 || *token == '0') {
        StackPush(&stack, f);
    } else if (*token == '+' || *token == '-' || *token == '*' || *token == '/') {
        return RPN_ERROR_STACK_UNDERFLOW;
    } else {
        return RPN_ERROR_INVALID_TOKEN;
    }
    while (1) {
        token = strtok(NULL, " ");
        if (token == NULL) {
            break;
        }
        f = atof(token);
        if (f != 0 || *token == '0') {
            x = StackPush(&stack, f);
            if (x != 1) {
                return RPN_ERROR_STACK_OVERFLOW;
            }
        } else if (*token == '+' || *token == '-' || *token == '*' || *token == '/') {
            x = StackPop(&stack, &operand1);
            if (x != 1) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            x = StackPop(&stack, &operand2);
            if (x != 1) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            x = StackIsEmpty(&stack);
            if (x != 1) {
                return RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
            }
            switch (*token) {
                case '+':
                    *result = operand1 + operand2;
                    break;
                case '-':
                    *result = operand2 - operand1;
                    break;
                case '*':
                    *result = operand1*operand2;
                    break;
                case '/':
                    if (operand1 == 0) {
                        return RPN_ERROR_DIVIDE_BY_ZERO;
                    }
                    *result = operand2 / operand1;
                    break;
            }
            x = StackPush(&stack, *result);
            if (x != 1) {
                return RPN_ERROR_STACK_OVERFLOW;
            }
        } else {
            return RPN_ERROR_INVALID_TOKEN;
        }
    }
    if(StackGetSize(&stack)<1){
        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
    }
    return RPN_NO_ERROR;
}

int ProcessBackspaces(char *rpn_sentence) {
    struct Stack back = {};
    StackInit(&back);
    double trash; //store deleted items
    double temp; //temporarily store popped value
    int i=0, s; //s=size of modified array
    while (rpn_sentence[i] != 0x00) {
        if (rpn_sentence[i] == 0x08) {
            if (StackIsEmpty(&back)) {
                i++;
                continue;
            }
            StackPop(&back,&trash);
        } else {
            StackPush(&back, rpn_sentence[i]);
        }
        rpn_sentence[i] = 0x00; //clear the array
        i++;
    }
    s = StackGetSize(&back);
    for (i = 0; i < s; i++) {
        StackPop(&back, &temp);
        rpn_sentence[s - 1 - i] = temp;
    }
    return s;
}