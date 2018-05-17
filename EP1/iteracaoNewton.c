#include<stdio.h>
#include "resolveSisLin.h"

/**
Dado o Jacobiano e os valores da funcao no ponto F(X),
um ponto inicial X, um erro eps e um numero maximo de imax
roda uma iteracao do metodo de newton N dimensional
**/
void iteracaoNewton (double **J, double *Fx, double *X, double *Xprox, int n)
{
    double *C;
    int *P, i;
    C = (double *)malloc(n * sizeof(double*));
    P = (int *)malloc(n * sizeof(int*));
    //Multiplica cada elemento de Fx por -1
    for(i=0; i<n; i++)
    {
        Fx[i] = -Fx[i];
    }
    //Realiza a decomposicao LU sobre JC
    decomposicaoLU(J, P, n);
    //Resolve O SL JC = P-Fx
    resolveSisLinPermutado(J, Fx, C, P, n);
    //Resolve Xprox = X + C
    for(i=0; i<n; i++)
    {
        Xprox[i] = X[i] + C[i];
    }

}
