#include<stdio.h>
#include<stdlib.h>
/**resolve sistema linear dada uma matriz LU e sua
respectiva matriz B permutada. Ao fim do algoritmo
a matriz B eh reconvertida para a base original
**/
void resolveSisLinPermutado(double **A, double *B, double *X, int *P, int n)
{
    double *Y;
    double temp;
    int i, j;

    Y = (double *)malloc(n * sizeof(double));
    //Permuta B

    for (j=0; j<n; j++)
    {
        if(j != P[j])
        {
            temp = B[j];
            B[j] = B[P[j]];
            B[P[j]] = temp;
        }

    }

    /** Print de teste PB

     printf("\n\n[PB]: \n");
    for(i=0; i<n; i++)
    {
        printf("%9.3f",B[i]);
    }
    **/

    //Resolve LY=PB
    for(i=0; i<n; i++)
    {
        Y[i]=B[i];
        for(j=0; j<i; j++)
        {
            Y[i] = Y[i] - A[i][j]*Y[j];
        }
    }

    /** Print de teste Y

    printf("\n\n[Y]: \n");
    for(i=0; i<n; i++)
    {
        printf("%9.3f",Y[i]);
    }

    **/

    //Resolve o sistema UX = Y
    for(i=n-1; i>=0; i--)
    {
        X[i]= Y[i];
        for(j=i+1; j<n; j++)
        {
            X[i] = X[i] - A[i][j]*X[j];
        }
        //Caso A[i][i] seja 0 o sistema possui infinitas sol
        if (A[i][i] == 0)
        {
            printf("\n\nErro: Sistema Indeterminado\n");
            return;
        }
        X[i]= X[i]/A[i][i];
    }

    /** Print de teste X
    printf("\n\n[X]: \n");
    for(i=0; i<n; i++)
    {
        printf("%9.3f",X[i]);
    }
    **/

    free(Y);
}
