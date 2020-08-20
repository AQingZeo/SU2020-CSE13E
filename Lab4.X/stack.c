/* 
 * File:   stack.c
 * Author: xzhan214 
 *
 * Created on July 13, 2020, 12:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "BOARD.h"
/*
 * 
 */
//Initialize stack

void StackInit(struct Stack *stack) {
    stack->currentItemIndex = -1;
    stack->initialized = TRUE;
    return;
}
//Push an element

int StackPush(struct Stack *stack, double value) {
    if (stack->currentItemIndex < STACK_SIZE - 1 && stack->initialized == TRUE) {
        stack->currentItemIndex++;
        stack->stackItems[stack->currentItemIndex] = value;
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}
//Pop an element

int StackPop(struct Stack *stack, double *value) {
    if (stack->currentItemIndex>-1 && stack->initialized == TRUE) {
        *value = stack->stackItems[stack->currentItemIndex];
        stack->currentItemIndex--;
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}
//Check if its empty

int StackIsEmpty(const struct Stack *stack) {
    if (StackGetSize(stack) == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}
//check if full

int StackIsFull(const struct Stack *stack) {
    if (StackGetSize(stack) == STACK_SIZE) {
        return TRUE;
    } else {
        return FALSE;
    }
}
//get # of elements

int StackGetSize(const struct Stack *stack) {
    if (stack->initialized == TRUE) {
        return stack->currentItemIndex + 1;
    } else {
        return SIZE_ERROR;
    }
}