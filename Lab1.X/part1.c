/* 
 * File:   part1.c
 * Author: Zeo Zhang
 *
 * Created on June 28, 2020, 14:46
 */
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <stdlib.h>

//Class specific libraries
#include "BOARD.h"


// User libraries

int main(void) {
    BOARD_Init();
    unsigned char vals[] = {rand(), rand(), rand(), rand(), rand()};
    int valsToBeSorted[] = {vals[0], vals[1], vals[2], vals[3], vals[4]};

    // Sort the array in place.
    /*1st: 138,135,251,15,151
     * 2nd:138,135,251,15,151
     * 3rd:135,138,251,15,151
     * 4th:135,138,251,15,151
     * 5th:15,135,138,251,151
     * 6th:15,135,138,151,251
     */
    int i, j;
    for (i = 0; i < 5; i++) {
        int aTemp = valsToBeSorted[i];
        for (j = i - 1; j >= 0; j--) {
            if (valsToBeSorted[j] <= aTemp)
                break;
            valsToBeSorted[j + 1] = valsToBeSorted[j];
        }
        valsToBeSorted [j + 1] = aTemp;
    }

    // Print out the array
    printf("[");
    for (i = 0; i < 4; i++) {
        printf("%d, ", valsToBeSorted[i]);
    }
    printf("%d]\n", valsToBeSorted[i]);

    /*
     * Returning from main() is bad form in embedded environments. So we
     * sit and spin.
     */
    while (1);
}