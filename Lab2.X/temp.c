/* 
 * File:   temp.c
 * Author: apple
 *
 * Created on July 21, 2020, 9:38 AM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main() {
    int x=0;
    int y=1;
    int *x0=&x;
    int **x1=&x0;
    x0=&y;
    printf("%d, %d",x1,x);

    return (EXIT_SUCCESS);
}

