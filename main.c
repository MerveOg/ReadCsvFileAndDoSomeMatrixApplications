/*
Author: Merve Öğ 
Mail: merve.og@stu.fsm.edu.tr
Date:28/12/2022
File:FILEPROJECT2.c
Description: Bu projede dosya okuma işlemi gerçekleştirdim ve belirli hesaplamalar yaptım.
Assisgnment: 2.proje
*/

#include "matrixLib.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max_Char 1024

typedef enum
{
    Irissetosa = 1,
    Irisversicolor,
    Irisvirginica

} Species;

typedef struct
{

    float SepalLengthCm;
    float SepalWidthCm;
    float PetalLengthCm;
    float PetalWidthCm;
    int species;

} IrisDataType;

int main()
{

    IrisDataType *iris;
    FILE *irisFile = fopen("Iris.csv", "r");
    char store[Max_Char];

    FILE *resultFile = fopen("IrisStatistic.txt", "w");

    //Burada verilen veri setindeki ilk satırdan oluşacak matrisin satır değerini almak istedim.
    int dataSize = atoi(fgets(store, Max_Char, irisFile));

    iris = (IrisDataType *)malloc(sizeof(IrisDataType) * dataSize);
    int columnCount = 0;
    int rowCount = 0;
    int i = 0, j = 0;

    //Dosya eğer boş ise okunacak değer olmayacağından uyarı vermek istedim.
    if (irisFile == NULL)
    {
        printf("This file is empty!");
        exit(0);
    }

    //Bu bölümde dosyayı okuma işlemini gerçekleştirdim. Bu işlemi yaparken strtok isimli fonksiyondan yararlandım.
    //Bu fonksiyon ile her virgül geldiğinde değerleri aldım ve olulturduğum struct'taki bazı değişkenlere bu değerleri atadım.
    //Dosya bitene kadar bu file çalışacak ve dosya okunmuş olacak.
    while (fgets(store, Max_Char, irisFile))
    {

        columnCount = 0;
        rowCount++;

        //Burada matris oluştururken işime yaramayacak olan satırı atladım.
        if (rowCount == 1)
        {
            continue;
        }

        char *divide = strtok(store, ",");
        //Bir columCount değeri tuttum ve bu değer veri setinde bulunan özellik sayısını yansıtıyor. Her virgül öncesinde
        //hangi özelliğin değeri varsa o değişkene o değeri atadım.
        while (divide)
        {
            if (columnCount == 1)
            {
                iris[i].SepalLengthCm = (float)atof(divide);
            }
            if (columnCount == 2)
            {
                iris[i].SepalWidthCm = (float)atof(divide);
            }
            if (columnCount == 3)
            {
                iris[i].PetalLengthCm = (float)atof(divide);
            }
            if (columnCount == 4)
            {
                iris[i].PetalWidthCm = (float)atof(divide);
            }

            if (columnCount == 5)
            {
                //Burada veri setindeki bitki değişkenlerini enum'dan yararlanarak belirli sayılar ile ifade ettim.
                //Karşılaştırma kısmında her isim değeri sonunda alt satıra geçtiği için \n sorun oluyordu ve bunu araştırıp yazdığım
                //Trim fonksiyonu ile hallettim.
                if (strcmp(trim(divide), "Iris-setosa") == 0)
                {
                    iris[i].species = Irissetosa;
                }
                if (strcmp(trim(divide), "Iris-versicolor") == 0)
                {
                    iris[i].species = Irisversicolor;
                }
                if (strcmp(trim(divide), "Iris-virginica") == 0)
                {
                    iris[i].species = Irisvirginica;
                }
            }

            divide = strtok(NULL, ",");
            columnCount++;
        }
        i++;
    }

    //Burada veri setimi bitki isimlerini sayılar ile ifade ettikten sonra başka bir dosyaya yazdım.
    for (int i = 0; i < dataSize; i++)
    {
        fprintf(resultFile, "SepalL: %f , SepalW: %f ,PetalL: %f ,PetalW: %f ,Species: %d\n", iris[i].SepalLengthCm, iris[i].SepalWidthCm, iris[i].PetalLengthCm, iris[i].PetalWidthCm, iris[i].species);
    }

    //Burada 150*4'lük matrisimi oluşturdum.
    float **irisDataMatrix = returnMatrix(dataSize, 4);
    for (int i = 0; i < dataSize; i++)
    {
        irisDataMatrix[i][0] = iris[i].SepalLengthCm;
        irisDataMatrix[i][1] = iris[i].SepalWidthCm;
        irisDataMatrix[i][2] = iris[i].PetalLengthCm;
        irisDataMatrix[i][3] = iris[i].PetalWidthCm;
    }

    fprintf(resultFile, "\nIrıs data matrix:\n\n");

    //Burada 150*4'lük matrisimi başka bir dosyaya bastım.

    for (i = 0; i < dataSize; i++)
    {
        for (j = 0; j < 4; j++)
        {
            fprintf(resultFile, "%.2f ", irisDataMatrix[i][j]);
        }
        fprintf(resultFile, "\n");
    }

    float *sepalLengthArr = returnVector(150);
    float *sepalWidthhArr = returnVector(150);
    float *petalLengthArr = returnVector(150);
    float *petalWidthArr = returnVector(150);

    for (int i = 0; i < dataSize; i++)
    {
        sepalLengthArr[i] = irisDataMatrix[i][0];
        sepalWidthhArr[i] = irisDataMatrix[i][1];
        petalLengthArr[i] = irisDataMatrix[i][2];
        petalWidthArr[i] = irisDataMatrix[i][3];
    }

    //Burada projede istenilen bazı istatistiksel hesaplamaları başka bir dosyaya yazdırıyorum.
    fprintf(resultFile, "\nMean of Sepal Lengths: %f - Variance of Sepal Lengths: %f\n", mean(sepalLengthArr, 150), variance(sepalLengthArr, 150));
    fprintf(resultFile, "Mean of Sepal Widths: %f - Variance of Sepal Widths: %f\n", mean(sepalWidthhArr, 150), variance(sepalWidthhArr, 150));
    fprintf(resultFile, "Mean of Petal Lengths: %f - Variance of Petal Lenghts: %f\n", mean(petalLengthArr, 150), variance(petalLengthArr, 150));
    fprintf(resultFile, "Mean of Petal Widths: %f - Variance of Petal Widths: %f\n", mean(petalWidthArr, 150), variance(petalWidthArr, 150));

    fprintf(resultFile, "\nCorrelation of  Sepal Lengths and Sepal Widths: %f\n", correlation(sepalLengthArr, sepalWidthhArr, 150));
    fprintf(resultFile, "Correlation of  Petal Lengths and Petal Widths: %f\n", correlation(petalLengthArr, petalWidthArr, 150));
    fprintf(resultFile, "Correlation of  Sepal Lengths and Petal Length: %f\n", correlation(sepalLengthArr, petalLengthArr, 150));
    fprintf(resultFile, "\nCovariance Matrix of Given Data: \n");

    float **covarianceMatrixOfData = returnMatrix(4, 4);

    covarianceMatrixOfData = covarianceMatrix(irisDataMatrix, dataSize, 4);

    //Burada 150*4'lük matrisimin covariance matrix'ini başka bir dosyaya yazdırıyorum.
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {

            fprintf(resultFile, "%.2f ", covarianceMatrixOfData[i][j]);
        }
        fprintf(resultFile, "\n");
    }

    fclose(irisFile);
    fclose(resultFile);

    free(sepalLengthArr);
    free(sepalWidthhArr);
    free(petalLengthArr);
    free(petalWidthArr);
    freeMatrix(irisDataMatrix, dataSize);

    return 0;
}
