// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"




// User libraries:
#include "MatrixMath.h"


// Module-level variables:
//matrix samples
float zero_matrix[3][3] = {
    {},
    {},
    {}};
float matrix1[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}};
float matrix2[3][3] = {
    {11, 12, 13},
    {21, 22, 23},
    {31, 32, 33}};
float unit[3][3] = {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}};
float linear[3][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}};
float extrem[3][3] = {
    {1.0001, 2.0001, 3.0001},
    {4.0001, 5.0001, 6.0001},
    {7.0001, 8.0001, 9.0001}};
//matrix with det=1(integer inverse matrix) 
float intInver[3][3] = {
    {1, -2, 3},
    {0, -1, 4},
    {0, 0, 1}};
//storing result matrix
float result[3][3]; //for 3x3 result
float res[2][2]; //for2x2 result

//helper functions
void Printer2x2(float mat[2][2]);
void Test(float mat1[3][3], float mat2[3][3]);
void Test2x2(float mat1[2][2], float mat2[2][2]);

int main() {
    BOARD_Init();

    printf("Beginning xzhan214's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);

    printf("Demonstrating MatrixPrint():\n");
    MatrixPrint(matrix1);

    // Add more tests here!
    //Equal test
    printf("\nDemonstrating MatrixEquals()(1for equal &0for not) :\n");
    printf("Case 1: Test on same matrix (Should Equal) \n");
    MatrixPrint(matrix1);
    MatrixPrint(matrix1);
    printf("Result: %d \n", MatrixEquals(matrix1, matrix1));
    printf("Case 2: Test on different matrix(Should not Equal)\n");
    MatrixPrint(zero_matrix);
    MatrixPrint(matrix1);
    printf("Result: %d \n", MatrixEquals(zero_matrix, matrix1));
    printf("Case 3: Test on extreme case with 0.0001 error (Should equal)\n");
    MatrixPrint(matrix1);
    MatrixPrint(extrem);
    printf("Result: %d \n", MatrixEquals(extrem, matrix1));

    //Add test
    printf("\nDemonstrating MatrixAdd():\n");
    printf("Case 1: Test on add 2 matrix\n");
    float ma1plus2[3][3] = {
        {12, 14, 16},
        {25, 27, 29},
        {38, 40, 42}};
    printf("Expected Value:\n");
    MatrixPrint(ma1plus2);
    printf("Result:\n");
    MatrixAdd(matrix1, matrix2, result);
    MatrixPrint(result);
    Test(ma1plus2, result);
    printf("Case 2: Reverse the 2 matrix in Case1 and "
            "see if result is the same\n");
    printf("Expected Value:\n");
    MatrixPrint(ma1plus2);
    printf("Result:\n");
    MatrixAdd(matrix2, matrix1, result);
    MatrixPrint(result);
    Test(ma1plus2, result);

    //Multiply test
    printf("\nDemonstrating MatrixMultiply():\n");
    printf("Case 1: Multiply by unit matrix (*1)\n");
    printf("Expected Value:\n");
    float mul1ByU[3][3] = {
        {6, 6, 6},
        {15, 15, 15},
        {24, 24, 24}};
    MatrixPrint(mul1ByU);
    printf("Result:\n");
    MatrixMultiply(matrix1, unit, result);
    MatrixPrint(result);
    Test(mul1ByU, result);
    printf("Case 2: Reverse the 2 matrix in Case1 and"
            "see if result is different\n");
    float mulUBy1[3][3] = {
        {12, 15, 18},
        {12, 15, 18},
        {12, 15, 18}};
    printf("Expected Value:\n");
    MatrixPrint(mulUBy1);
    printf("Result:\n");
    MatrixMultiply(unit, matrix1, result);
    MatrixPrint(result);
    Test(mulUBy1, result);

    //Scalar add test
    printf("\nDemonstrating MatrixScalarAdd():\n");
    printf("Case 1: add by 0, then result should= input(1-9)\n");
    printf("Expected Value:\n");
    MatrixPrint(matrix1);
    printf("Result:\n");
    MatrixScalarAdd(0, matrix1, result);
    MatrixPrint(result);
    Test(matrix1, result);
    printf("Case 2: add by 1 with empty set input, see if all element =1\n");
    printf("Expected Value:\n");
    MatrixPrint(unit);
    printf("Result:\n");
    MatrixScalarAdd(1, zero_matrix, result);
    MatrixPrint(result);
    Test(unit, result);

    //Scalar multiply test
    printf("\nDemonstrating MatrixScalarMultiply():\n");
    printf("Case 1: multiply by 1, then result should= input(1-9)\n");
    printf("Expected Value:\n");
    MatrixPrint(matrix1);
    printf("Result:\n");
    MatrixScalarMultiply(1, matrix1, result);
    MatrixPrint(result);
    Test(matrix1, result);
    printf("Case 2: multiply the empty set by 5, the result should all=0\n");
    printf("Expected Value:\n");
    MatrixPrint(zero_matrix);
    printf("Result:\n");
    MatrixScalarMultiply(5, zero_matrix, result);
    MatrixPrint(result);
    Test(zero_matrix, result);

    //trace test
    printf("\nDemonstrating MatrixTrace():\n");
    printf("Case 1: use matrix1(1-9),result should be 15\n");
    printf("Result: %.4f\n", MatrixTrace(matrix1));
    if (MatrixTrace(zero_matrix) - 15 <= FP_DELTA) {
        printf("Pass the test\n");
    } else {
        printf("Test does not pass\n");
    }
    printf("Case 2: use empty matrix, result should be 0\n");
    printf("Result: %.4f\n", MatrixTrace(zero_matrix));
    if (MatrixTrace(zero_matrix) == 0) {
        printf("Pass the test\n");
    } else {
        printf("Test does not pass\n");
    }

    //transpose test
    printf("\nDemonstrating MatrixTranspose():\n");
    printf("Case 1: use matrix2(position#),position can be shown by #s\n");
    float trans2[3][3] = {
        {11, 21, 31},
        {12, 22, 32},
        {13, 23, 33}};
    printf("Expected Value:\n");
    MatrixPrint(trans2);
    printf("Result:\n");
    MatrixTranspose(matrix2, result);
    MatrixPrint(result);
    Test(trans2, result);
    printf("Case 2: use matrix(1-9)\n");
    printf("Expected Value:\n");
    float trans1[3][3] = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}};
    MatrixPrint(trans1);
    printf("Result:\n");
    MatrixTranspose(matrix1, result);
    MatrixPrint(result);
    Test(trans1, result);

    //sub
    printf("\nDemonstrating MatrixSubmatrix():\n");
    printf("Case 1: submatrix for 0,0 on matrix2(position#s)"
            "Result should be 22,23,32,33\n");
    float sub2[2][2] = {
        {22, 23},
        {32, 33}};
    printf("Expected Value:\n");
    Printer2x2(sub2);
    printf("Result:\n");
    MatrixSubmatrix(0, 0, matrix2, res);
    Printer2x2(res);
    Test2x2(res, sub2);
    printf("Case 2: submatrix for 1,1 on empty matrix(all 0)\n");
    float sub0[2][2] = {
        {},
        {}};
    printf("Expected Value:\n");
    Printer2x2(sub0);
    printf("Result:\n");
    MatrixSubmatrix(1, 1, zero_matrix, res);
    Printer2x2(res);
    Test2x2(res, sub0);

    // Deter
    printf("\nDemonstrating MatrixDeterminant():\n");
    printf("Case 1: Test for linear(echelon), det=1\n");
    printf("det= %f\n", MatrixDeterminant(linear));
    if (MatrixDeterminant(linear) == 1) {
        printf("Pass the test\n");
    } else {
        printf("Test does not pass\n");
    }
    printf("Case 1: Test for matrix1(1-9), det=0\n");
    printf("det= %f\n", MatrixDeterminant(matrix1));
    if (MatrixDeterminant(matrix1) == 0) {
        printf("Pass the test\n");
    } else {
        printf("Test does not pass\n");
    }

    //Inverse
    printf("\nDemonstrating MatrixInverse():\n");
    printf("Case 1: Test for linear(echelon) inverse should not change\n");
    printf("Expected Value:\n");
    MatrixPrint(linear);
    printf("Result:\n");
    MatrixInverse(linear, result);
    MatrixPrint(result);
    Test(linear, result);
    printf("Case 2: Test for matrix1(1-9)\n");
    float intInverOut[3][3] = {
        {1, -2, 5},
        {0, -1, 4},
        {0, 0, 1}};
    printf("Expected Value:\n");
    MatrixPrint(intInverOut);
    printf("Result:\n");
    MatrixInverse(intInver, result);
    MatrixPrint(result);
    Test(intInverOut, result);

    BOARD_End();
    while (1);
}

void Printer2x2(float mat[2][2]) {
    int i, j;
    for (i = 0; i < 2; i++) {
        printf("\n");
        for (j = 0; j < 2; j++) {
            printf(" %4.4f", mat[i][j]);
        }
    }
    printf("\n");
    return;
}

void Test(float mat1[3][3], float mat2[3][3]) {
    int x;
    x = MatrixEquals(mat1, mat2);
    if (x == 1) {
        printf("Pass the test\n");
    } else {
        printf("Test does not pass\n");
    }
    return;
}

void Test2x2(float mat1[2][2], float mat2[2][2]) {
    int i, j;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (mat1[i][j] != mat2[i][j]) {
                printf("Test does not pass\n");
                return;
            }
        }
    }
    printf("Pass the test\n");
    return;
}
