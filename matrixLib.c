/*
Author: Merve Öğ 
Mail: merve.og@stu.fsm.edu.tr
Date:28/12/2022
File:FILEPROJECT2.c
Description: Bu projede dosya okuma işlemi gerçekleştirdim ve belirli hesaplamalar yaptım.
Assisgnment: 2.proje
*/

#include <stdlib.h>
#include <stdio.h>
#include "matrixLib.h"
#include <math.h>
#include <ctype.h>
#include <string.h>

//Bu fonksiyon dinamik olarak bir vektör oluşturuyor.
float *returnVector(int size)
{

    float *arr = (float *)malloc(size * sizeof(float));

    return arr;
}

//Bu fonksiyon dinamik olarak matris oluşturuyor.
float **returnMatrix(int row, int col)
{

    float **twoDimensionalArray = (float **)malloc(sizeof(float *) * row);

    for (int i = 0; i < row; i++)
    {
        twoDimensionalArray[i] = (float *)malloc(sizeof(float) * col);
    }

    return twoDimensionalArray;
}

//Bu fonksiyon heap'ten matris için alınan alanı geri iade ediyor.
//Bu işlemi gerçekleştirirken önce satırları geri iade ediyoruz.
//Ardından yeniden free işlemini gerçekleştirmemiz gerekiyor.
void freeMatrix(float **mat, int row)
{

    for (int i = 0; i < row; i++)
    {
        free(mat[i]);
    }
    free(mat);
}

//Bu fonksiyon verilen matrisin satır ortalamasını hesaplıyor.
float *rowMeans(float **mat, int row, int col)
{

    float *result = returnVector(row);
    float sum = 0;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            sum += mat[i][j]; //sum değişkenine satır değerlerini ekledim.
        }

        result[i] = sum / col; // sum/col ile satır ortalamasını hesapladım ve vektöre atadım.
        sum = 0;               // Farklı bir satıra geçtiğinde toplamı 0 yaptım ki satırların ayrı ayrı ortalamalarını bulabileyim.
    }

    return result;
}

float *columnMeans(float **mat, int row, int col)
{

    float *result = returnVector(col);

    //verilen matrisin transpozesini aldıktan sonra o matrisin satırlarının satır ortalamasını hesapladım ve değerleri vektörde tuttum.
    //Böylelikle matrisin sütun ortalamasını bulmuş oldum.
    result = rowMeans(matrixTranspose(mat, row, col), col, row);

    return result;
}

float mean(float *vec, int size)
{

    float sum = 0, result = 0;

    for (int i = 0; i < size; i++)
    {
        sum += vec[i];
    }

    result += sum / size;
    return result;
}

float correlation(float *vec, float *vec2, int size)
{

    float sumx = 0, sumy = 0;
    float resultx = 0, resulty = 0;
    float correlationResult = 0;

    for (int i = 0; i < size; i++)
    {
        //Burada elemanlardan vector ortalamasını cıkarıp karesini alıyorum ve değişkene atıyorum.
        sumx += pow((vec[i] - mean(vec, size)), 2);
        sumy += pow((vec2[i] - mean(vec2, size)), 2);
    }

    resultx = sqrt(sumx / (size - 1)); //Sonucu size-1 'e bölüyorum ve karekökünü alıyorum.
    resulty = sqrt(sumy / (size - 1)); //Sonucu size-1'e bölüyorum ve karekökünü alıyorum.

    //Burada iki vectörün covariance değerini bulduğum iki değerin çarpımına bölüp değere atıyorum.
    correlationResult = (covariance(vec, vec2, size)) / (resultx * resulty);

    return correlationResult;
}

char *trim(char *word)
{
    char *ptr1;
    if (!word)
    {
        return NULL;
    }
    if (!*word)
    {
        return word;
    }
    //Kelimede yer alan belirli boşlukları alıyorum ve sadece o kelimeyi döndürüyorum.
    for (ptr1 = word + strlen(word) - 1; (ptr1 >= word) && isspace(*ptr1); --ptr1)
        ;

    ptr1[1] = '\0';

    return word;
}

float variance(float *vec, int size)
{

    float sumx = 0;
    float resultx = 0;

    for (int i = 0; i < size; i++)
    {
        //Burada elemanlardan vector ortalamasını cıkarıp karesini alıyorum ve değişkene atıyorum.
        sumx += pow((vec[i] - mean(vec, size)), 2);
    }

    resultx = (sumx / (size));

    return resultx;
}

//Bu fonksiyon verilen matrisin transpozesini return ediyor.
//Böylelikle yeni oluşturulan matrisin sütunları ilk matrisin satır değerleri olmuş oluyor ve ilk matrisin transpozesi bulunuyor.
float **matrixTranspose(float **mat, int row, int col)
{

    float **result = returnMatrix(col, row);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            result[j][i] = mat[i][j];
        }
    }

    return result;
}

float covariance(float *vec, float *vec2, int size)
{

    float sum = 0;
    float result = 0;

    for (int i = 0; i < size; i++)
    {
        //Verilen vectörlerdeki her bir elemandan o vektörün ortalamasını çıkardım ve bu değerleri her defasında çarpıp toplama ekledim.
        sum += (vec[i] - mean(vec, size)) * (vec2[i] - mean(vec2, size));
    }
    //Ardından bu değeri (vectör boyutu -1) 'e bölerek hesapladım.
    result += sum / (size - 1);

    return result;
}

float **matrixMultiplication(float **mat1, float **mat2, int row1, int col1, int row2, int col2)
{

    float **multiMatrix = returnMatrix(row1, col2);
    float multiResult = 0;

    if (col1 == row2) //İlk matrisin sütun sayısı ile 2.matrisin satır sayısı aynı ise çarpım hesaplanabilir.
    {
        int i, j;
        //Her satırdaki belli indeksteki değerle diğer matrisin sütunundaki belli indeksteki değeri
        //Çarpmamız gerektiği için 3.bir for daha gerekti.
        int x;

        for (i = 0; i < row1; i++)
        {
            for (j = 0; j < col2; j++)
            {
                multiMatrix[i][j] = 0;

                for (int x = 0; x < row2; x++)
                {
                    //Matris çarpımında bir matrisin satırdaki a indeksindeki değer ile diğer matrisin
                    //Sütunundaki a indeksindeki değer çarpılır ve bir değere eklenir.(a -> örnek indeks).
                    multiMatrix[i][j] += mat1[i][x] * mat2[x][j];
                }
            }
        }
        return multiMatrix;
    }
    else
    {
        exit(1);
    }
}

float **covarianceMatrix(float **mat, int row, int col)
{

    float *vector = returnVector(col);
    vector = columnMeans(mat, row, col);
    float **result = returnMatrix(col, col);
    float **temp = returnMatrix(row, col);
    float **product = returnMatrix(col, col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            temp[i][j] = mat[i][j] - vector[j]; //Elemanlardan bulunduğu sütunun sütun ortalamasını çıkardım.
        }
    }

    //temp matrisinin transpozesini aldım ve temp matrisi ile matrix çarpımı uyguladım
    product = matrixMultiplication(matrixTranspose(temp, row, col), temp, col, row, row, col);

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < col; j++)
        {
            //product matrisindeki her bir elemanı row değerine böldüm ve yeni bir matrise atadım.
            result[i][j] = product[i][j] / (float)row;
        }
    }
    return result;
}
