#include<stdio.h>
#include<stdlib.h>
#include "resolveSisLin.h"
#include "decomposicaoLU.h"

/**
Dado o Jacobiano e os valores da funcao no ponto F(X),
um ponto inicial X, um erro eps e um numero maximo de imax
roda uma iteracao do metodo de newton N dimensional
**/
void iteracaoNewton (double **J, double *Fx, double *X, double *C, int n)
{
    int *P, i;
    P = (int *)calloc(n,  sizeof(int));
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
        X[i] = X[i] + C[i];
    }
    free(P);
}
