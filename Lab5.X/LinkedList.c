/* 
 * File:   LinkedList.c
 * Author: xzhan214
 *
 * Created on July 20, 2020, 3:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "BOARD.h"

/*
 * 
 */
ListItem *LinkedListNew(char *data) {
    ListItem *newList = malloc(sizeof (ListItem));
    if (newList == NULL) {
        return NULL;
    } else {
        newList->nextItem = NULL;
        newList->previousItem = NULL;
        newList->data = data;
    }
    return newList; //if NULL will directly return NULL
}

ListItem *LinkedListCreateAfter(ListItem *item, char *data) {
    ListItem *newItem = LinkedListNew(data);
    ListItem *next = item->nextItem; //temporary point to next item
    if (item == NULL) {
        return newItem;
    } else {//logic: item<-->newItem<-->next 
        item->nextItem = newItem;
        newItem->previousItem = item;
        newItem->nextItem = next;
        if (next != NULL) {
            next->previousItem = newItem;
        }
        return newItem;
    }
}

char *LinkedListRemove(ListItem *item) {
    if (item == NULL) {
        return NULL;
    }
    char *removed = item->data;
    ListItem *last = item->previousItem;
    ListItem *next = item->nextItem;
    if (last != NULL) {
        last->nextItem = next;
    }
    if (next != NULL) {
        next->previousItem = last;
    }
    free(item);
    return removed;
}

int LinkedListSize(ListItem *list) {
    int cnt = 1;
    if (list == NULL) {
        return 0;
    }
    ListItem *count = list; //count # before item
    while (count != NULL) {
        count = count->previousItem;
        if (count != NULL) {
            cnt++;
        }
    }
    count = list; //count # after item
    while (count != NULL) {
        count = count->nextItem;
        if (count != NULL) {
            cnt++;
        }
    }
    return cnt;
}

ListItem *LinkedListGetFirst(ListItem *list) {
    if (list == NULL) {
        return NULL;
    }
    ListItem *temp = list;
    while (temp->previousItem != NULL) {
        temp = temp->previousItem;
    }
    return temp;
}

ListItem *LinkedListGetLast(ListItem *list) {
    if (list == NULL) {
        return NULL;
    }
    ListItem *temp = list;
    while (temp->nextItem != NULL) {
        temp = temp->nextItem;
    }
    return temp;
}

int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem) {
    if (firstItem == NULL || secondItem == NULL) {
        return STANDARD_ERROR;
    }
    char* data = firstItem->data;
    firstItem->data = secondItem->data;
    secondItem->data = data;

    return SUCCESS;
}

int LinkedListPrint(ListItem *list) {
    ListItem *head = LinkedListGetFirst(list);
    if (head == NULL || head->data == NULL) {
        return STANDARD_ERROR;
    }
    ListItem *temp = head;
    printf("[ %s ", temp->data);
    while (temp->nextItem != NULL) {
        temp = temp->nextItem;
        printf(", %s", temp->data);
    }
    printf("]\n");
    return SUCCESS;
}