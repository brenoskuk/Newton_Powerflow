#include <stdio.h>
#include <stdlib.h>

#include "montaMatrizQuadrada.h"
#include "montaVetor.h"
#include "decomposicaoLU.h"
#include "resolveSisLin.h"
#include "iteracaoNewton.h"


int main()
{
    double **A;
    double *B, *P, *X;

    int ordemA, ordemB;

    char enderecoA[]="../matrizes/matrizA2.txt";
    char enderecoB[]="../matrizes/vetorB2.txt";

    A = montaMatrizQuadrada(enderecoA, &ordemA);
    B = montaVetor(enderecoB, &ordemB);
    P = (int *)malloc(ordemA * sizeof(int*));
    X = (double *)malloc(ordemA * sizeof(double*));
    if (ordemA = ordemB)
    {
        //Aloca a memoria para o vetor de pivos
        decomposicaoLU(A, P,ordemA);
        //Note que B esta permutada
        resolveSisLinPermutado(A, B, X, P, ordemA);
    }
    else
    {
        printf("\n Valores fornecidas invalidas...");
    }

    return 0;
}
