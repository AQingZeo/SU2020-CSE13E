/* 
 * File:   MatrixMath.c
 * Author: Zeo Zhang
 *
 * Created on July 7 2020, 10:16
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MatrixMath.h"

/*
 * 
 */
//Print out matrix
float MatrixDeterminant2x2(float mat[2][2]);
void MatrixPrint(float mat[3][3]){
    int i,j;
    for(i=0;i<DIM;i++){
        printf("\n");
        for(j=0;j<DIM;j++){
            printf(" %4.4f",mat[i][j]);
        }
    }
    printf("\n");
    return;
}
//test if 2 matrix equal
int MatrixEquals(float mat1[3][3], float mat2[3][3]){
    int i,j;
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            if(abs(mat1[i][j]-mat2[i][j])>FP_DELTA){
                return 0;
            }
        }
    }
    return 1;
}
//add 2 matrix
void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3]){
    int i,j;
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            result[i][j]=mat1[i][j]+mat2[i][j];
        }
    }
    return;
}
//times 2 matrix
void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3]){
    int i,j,k;
    //to clear the result array
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            result[i][j]=0;
        }
    }
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            for(k=0;k<DIM;k++){
                result[i][j]+=mat1[i][k]*mat2[k][j];
            }
        }
    }
    return;
}
//add each element in the matrix with x
void MatrixScalarAdd(float x, float mat[3][3], float result[3][3]){
    int i,j;
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            result[i][j]=mat[i][j]+x;
        }
    }
    return;
}
//multiply each element in the matrix by x
void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3]){
    int i,j;
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            result[i][j]=mat[i][j]*x;
        }
    }
    return;
}
//return trace of the matrix
float MatrixTrace(float mat[3][3]){
    int i;
    float tr=0.; //tr stores sum value
    for(i=0;i<DIM;i++){
        tr+= mat[i][i];
    }
    return tr;
}
//transpose mat
void MatrixTranspose(float mat[3][3], float result[3][3]){
    int i,j;
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            result[j][i]=mat[i][j];
        }
    }
    return;
}
//find submatrix with exclusion of i-row and j-column
void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2]){
    int x,y;
    int r=0,c=0;//specific position for result
    for(x=0;x<2;x++){
        c=0;
        if(x==i){
            r++;
        }
        for(y=0;y<2;y++){
            if(y==j){
                c++;
            }
            result[x][y]=mat[r][c];
            c++;
        }
        r++;
    }
    return;
}
//calculate the determinant
float MatrixDeterminant(float mat[3][3]){
    float sub[2][2];
    int j;
    float deter[3];
    for(j=0;j<DIM;j++){
        MatrixSubmatrix(0,j,mat,sub);
        deter[j]=mat[0][j]*MatrixDeterminant2x2(sub);
    }
    return deter[0]-deter[1]+deter[2];
}
float MatrixDeterminant2x2(float mat[2][2]){
    return (mat[0][0]*mat[1][1])-(mat[0][1]*mat[1][0]);
}
//Inverse
void MatrixInverse(float mat[3][3], float result[3][3]){
    int i,j,k;
    float det;
    float res[2][2];
    float temp[3][3];
    det=MatrixDeterminant(mat);
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            if((i+j)%2==0){
                k=1;
            }else{
                k=-1;
            }
            MatrixSubmatrix(i, j, mat, res);
            temp[i][j]=k*MatrixDeterminant2x2(res);
        }
    }
    MatrixTranspose(temp,result);
    MatrixScalarMultiply(1/det, result, result);
    return;
}