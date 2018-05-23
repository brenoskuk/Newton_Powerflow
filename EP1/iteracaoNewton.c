#include<stdio.h>
#include<stdlib.h>
#include "resolveSisLin.h"
#include "decomposicaoLU.h"
#include "barras.h"

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
    //Resolve O s.l. JC = P(-Fx)
    resolveSisLinPermutado(J, Fx, C, P, n);
    //Resolve Xprox = X + C
    for(i=0; i<n; i++)
    {
        X[i] = X[i] + C[i];
    }
    free(P);
}


/**
Dado o Jacobiano e os valores da funcao no ponto F(X),
um vetor de barras b, um erro eps e um numero maximo de imax
roda uma iteracao do metodo de newton N dimensional
para o caso das questoes de rede
**/
void iteracaoNewtonBarra (double **J, double *Fx, barra **b, double *C, int n1, int n2)
{
    int *P, i, j, centro;
    centro = n1 + n2;
    P = (int *)calloc(centro + n1,  sizeof(int));
    //Multiplica cada elemento de Fx por -1
    for(i=0; i<centro + n1; i++)
    {
        Fx[i] = -Fx[i];
    }
    //Realiza a decomposicao LU sobre JC
    decomposicaoLU(J, P, centro + n1);
    //Resolve O s.l. JC = P(-Fx)
    resolveSisLinPermutado(J, Fx, C, P, centro + n1);
    //Resolve Xprox = X + C para i = 0 ate n1 + n2 (Theta1)
    //Lembrar que a barra de swing ocupa b[0]!!!
    for(i=0; i < centro; i++)
    {
        b[i+1]->fase = b[i+1]->fase + C[i];
    }
    //Resolve Xprox = X + C para i = 0 ate n1 + n2 (V)
    for(i=centro; i < centro + n1; i++)
    {
        b[i - centro + 1]->V = b[i - centro + 1]->V + C[i];
    }

    //Zera o vetor J
    for(i=0;i<2*n1 + n2;i++)
    {
        for(j=0; j<2*n1 + n2; j++)
        {
            J[i][j] = 0;
        }
    }
    //Zera o vetor F
    for(j=0; j<2*n1 + n2; j++)
    {
        Fx[j] = 0;
    }
    free(P);
}
