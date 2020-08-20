/* 
 * File:   LinkedListTest.c
 * Author: xzhan214
 *
 * Created on July 21, 2020, 11:07 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "BOARD.h"

/*
 * 
 */

int main(void) {
    BOARD_Init();
    char* words[] = {"one", "two", "three", "four", "five"};
    char* null[] = {NULL, NULL};

    printf("\n###### Beginning xzhan214's LinkedList test harness: ####\n\n");
    //LinkedlistNew
    printf("\nTesting LinkedListNew...\n"
            "Test on list with contents:\n");

    ListItem* createList = LinkedListNew(words[0]);
    if (createList == NULL) {
        printf("failed.\n");
    } else {
        printf("success!\n");
    }

    printf("test on list with NULL:\n");

    ListItem* createNull = LinkedListNew(null[0]);
    if (createNull == NULL) {
        printf("failed.\n");
    } else {
        printf("success!\n");
    }
    //LinkListCreateAfter
    printf("\nTesting LinkedListCreateAfter...\n"
            "Test on list with contents:\n");
    createList = LinkedListCreateAfter(createList, words[1]);
    if (createList == NULL) {
        printf("failed.\n");
    } else {
        printf("success!\n");
    }

    printf("test on list with NULL:\n");
    createNull = LinkedListCreateAfter(createNull, null[1]);
    if (createNull == NULL) {
        printf("failed.\n");
    } else {
        printf("success!\n");
    }
    /*Since need to use print and get size to test other functions, 
     * Test LinkedListPrint and LinkedListGetSize first*/
    printf("\nTesting LinkListSize and Print together...\n"
            "Test on list with 5 items\n");
    int i = 2;
    int size, error;
    for (i = 2; i < 5; i++) {
        createList = LinkedListCreateAfter(createList, words[i]);
    }
    size = LinkedListSize(createList);
    error = LinkedListPrint(createList);
    if (size == 5) {
        printf("get size successfully\n");
    } else {
        printf("failed to get size\n");
    }
    if (error == 1) {
        printf("print successfully\n");
    } else {
        printf("error when print\n");
    }
    printf("Test on list with 2 nulls\n");
    size = LinkedListSize(createNull);
    error = LinkedListPrint(createNull);
    if (size == 2) {
        printf("get size successfully\n");
    } else {
        printf("failed to get size\n");
    }
    if (error == 0) {
        printf("print error successfully detected\n");
    } else {
        printf("error detecting error\n");
    }



    //LinkedListGetFirst
    printf("\nTesting LinkedListGetFirst...\n"
            "Test on the list with content and pointer was point to the last\n");
    createList = LinkedListGetFirst(createList);
    if (createList->data == words[0]) {
        printf("success\n");
    } else {
        printf("failed\n");
    }
    printf("Checking for consistency of this function\n");
    createList = LinkedListGetFirst(createList);
    if (createList->data == words[0]) {
        printf("success\n");
    } else {
        printf("failed\n");
    }
    //LinkedListGetLast
    printf("\nTesting LinkedListGetLast...\n"
            "Test on the list with content and pointer was point to the head\n");
    createList = LinkedListGetLast(createList);
    printf("Expected Result: %s,  Result: %s\n", "five", createList->data);
    //there occurs an error when I tried to use word[-1] so I used five instead
    printf("Checking for consistency of this function\n");
    createList = LinkedListGetLast(createList);
    if (createList->data == "five") {
        printf("success\n");
    } else {
        printf("failed\n");
    }
    //LinkedListSwapData
    printf("\nTesting LinkedListSwapData...\n"
            "Test on the list with content and pointer was point to the last\n");
    createList = LinkedListGetLast(createList);
    error = LinkedListSwapData(createList, createList->previousItem);
    LinkedListPrint(createList);
    if (error == 1) {
        printf("success\n");
    } else {
        printf("failed\n");
    }

    printf("Test on content is NULL:\n");
    createNull = LinkedListGetFirst(createNull);
    error = LinkedListSwapData(createNull, createNull->nextItem);
    if (error == 1) {
        printf("success\n");
    } else {
        printf("failed\n");
    }
    //LinkedlistRemove
    printf("\nTesting LinkedListRemove...\n"
            "Test on Remove the last items on list with contents:\n");
    char* removed;
    createList = LinkedListGetLast(createList);
    removed = LinkedListRemove(createList);
    printf("Expected Result: %s,  Result: %s\n", words[-1], removed);

    printf("Test on Remove the last items on list with NULL:\n");
    createNull = LinkedListGetLast(createNull);
    removed = LinkedListRemove(createNull);
    if (removed == NULL) {
        printf("success\n");
    } else {
        printf("failed\n");
    }


    printf("\nTest end\n");
    BOARD_End();
    while (1);
}

