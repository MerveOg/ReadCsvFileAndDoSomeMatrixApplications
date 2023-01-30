/*
Author: Merve Öğ 
Mail: merve.og@stu.fsm.edu.tr
Date:28/12/2022
File:FILEPROJECT2.c
Description: Bu projede dosya okuma işlemi gerçekleştirdim ve belirli hesaplamalar yaptım.
Assisgnment: 2.proje
*/
#ifndef MYLIB_H
#define MYLIB_H
float *returnVector(int);
float **returnMatrix(int, int);
void freeMatrix(float **, int);
float *columnMeans(float **, int, int);
float *rowMeans(float **, int, int);
float mean(float *, int);
float correlation(float *, float *, int);
float **covarianceMatrix(float **, int, int);
char *trim(char *);
float variance(float *, int);
float **matrixMultiplication(float **, float **, int, int, int, int);
float **matrixTranspose(float **, int, int);
float covariance(float *, float *, int);
#endif
