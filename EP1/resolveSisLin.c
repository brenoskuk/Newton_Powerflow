#include<stdio.h>
/**resolve sistema linear dada uma matriz LU e sua
respectiva matriz B permutada. Ao fim do algoritmo
a matriz B eh reconvertida para a base original
**/
void resolveSisLinPermutado(double **A, double *B, int *P, int n)
{
    double *Y = (double *)malloc(n * sizeof(double*));
    double *X = (double *)malloc(n * sizeof(double*));
    double temp;
    int i, j;

    //Permuta B

    for (j=0; j<n; j++)
    {
        temp = B[j];
        B[j] = B[P[j]];
        B[P[j]] = temp;
    }

     printf("\n\n[PB]: \n");
    for(i=0; i<n; i++)
    {
        printf("%9.3f",B[i]);
    }

    //Resolve LY=PB

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

    //Resolve o sistema UX = Y
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
