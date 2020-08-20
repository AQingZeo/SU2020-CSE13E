// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "stack.h"

int main() {
    BOARD_Init();

    printf("\n###### Beginning xzhan214's stack test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!
    int x = 1, y; //x is input y is return value
    double out; //out carry result
    printf("Does StackInit() set the currentItemIndex appropriately?\n");
    struct Stack stack = {};
    StackInit(&stack);
    if (stack.currentItemIndex == -1) {
        printf("passed");
    } else {
        printf("failed");
    }
    //since need StackGetSize() to test other functions test it first
    printf("\nDoes StackGetSize() show 0 element for stack initialized above?\n");
    printf("Number of element in stack: %d\n", StackGetSize(&stack));
    if (StackGetSize(&stack) == 0) {
        printf("passed");
    } else {
        printf("failed");
    }
    //test push and use get size to see if there is an additional item on stack
    printf("\nDoes StackPush() store a value to the stack?\n");
    y = StackPush(&stack, x);
    if (y == 1) {
        printf("passed");
    } else {
        printf("failed");
    }
    printf("\nDoes StackPush() adjust index correctly?\n");
    printf("Index result: %d,  expected index=0", stack.currentItemIndex);
    //test pop to see if pop works and if pushed in the value appropriately
    printf("\nDoes StackPop() pop a value from the stack?\n");
    y = StackPop(&stack, &out);
    if (y == 1) {
        printf("passed");
    } else {
        printf("failed");
    }
    //test if the pop command pop correct value
    printf("\nResult of popped: %f\nExpected result: 1\n", out);
    if (out == 1.) {
        printf("passed");
    } else {
        printf("failed");
    }
    //test if the stack is empty 
    printf("\nDoes StackPop() return 0 if stack is empty?\n");
    y = StackPop(&stack, &out);
    if (y == 0) {
        printf("passed");
    } else {
        printf("failed");
    }
    //use the empty stack to see if IsEmpty work fine
    printf("\nDoes StackIsEmpty() return true if stack is empty?\n");
    y = StackIsEmpty(&stack);
    if (y == 1) {
        printf("passed");
    } else {
        printf("failed");
    }
    //use the empty stack to see if IsFull return false
    printf("\nDoes StackIsFull() return false if stack is empty?\n");
    y = StackIsFull(&stack);
    if (y == 0) {
        printf("passed");
    } else {
        printf("failed");
    }
    //fill the stack to check push/isfull().
    int i;
    for (i = 0; i < STACK_SIZE; i++) {
        StackPush(&stack, x);
    }
    printf("\nThe stack is filled with 20 1s\n"
            "Check if StackIsFull() return True\n");
    y = StackIsFull(&stack);
    if (y == 1) {
        printf("passed");
    } else {
        printf("failed");
    }
    printf("\nCheck if StackPush() return error appropriately\n");
    x = 2;
    y = StackPush(&stack, x);
    if (y == 0) {
        printf("passed");
    } else {
        printf("failed");
    }
    printf("\nLast Push tried to push a different number(2),"
            "Test with Pop to see if last value was still 1\n");
    StackPop(&stack, &out);
    if (out == 1) {
        printf("passed");
    } else {
        printf("failed");
    }
    printf("\nafter popped one item from full stack, see if index=18\n");
    printf("Index result: %d, expected index=18", stack.currentItemIndex);

    //push a different number in and see if pop deduct index correctly
    printf("\nDoes Pop pops correctly if call it more than one time?");
    StackPush(&stack, x);
    StackPop(&stack, &out);
    printf("\nFirst pop, expected value=2.0, result: %f", out);
    StackPop(&stack, &out);
    printf("\nFirst pop, expected value=1.0, result: %f", out);

    BOARD_End();
    //test stackInit:
    while (1);
    return 0;
}


