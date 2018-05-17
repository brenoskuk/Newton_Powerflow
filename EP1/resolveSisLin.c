#include<stdio.h>
//resolve sistema linear dada uma matriz

void resolveSisLin(float **A, float *B, int n)
{
    float *Y = (float *)malloc(n * sizeof(int*));
    float *X = (float *)malloc(n * sizeof(int*));

    int i, j;

    for(i=0; i<n; i++)
    {
        Y[i]=B[i];
        for(j=0; j<i; j++)
        {
            Y[i] = Y[i] - A[i][j]*Y[j];
        }
    }
    printf("\n\n[Y]: \n");
    for(i=0; i<n; i++)
    {
        printf("%9.3f",Y[i]);
    }
    for(i=n-1; i>=0; i--)
    {
        X[i]= Y[i];
        for(j=i+1; j<n; j++)
        {
            X[i] = X[i] - A[i][j]*X[j];
        }
        X[i]= X[i]/A[i][i];
    }
    printf("\n\n[X]: \n");
    for(i=0; i<n; i++)
    {
        printf("%9.3f",X[i]);
    }
}
