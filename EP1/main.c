#include <stdio.h>
#include <stdlib.h>

#include "montaMatrizQuadrada.h"
#include "montaVetor.h"
#include "decomposicaoLU.h"
#include "resolveSisLin.h"

int main()
{
    float **A;
    float *B, *P, *X;

    int ordemA, ordemB;

    char enderecoA[]="../matrizes/matrizA2.txt";
    char enderecoB[]="../matrizes/vetorB2.txt";

    A = montaMatrizQuadrada(enderecoA, &ordemA);
    B = montaVetor(enderecoB, &ordemB);
    P = (int *)malloc(ordemA * sizeof(int*));
    X = (float *)malloc(ordemA * sizeof(float*));
    if (ordemA = ordemB)
    {
        //Aloca a memoria para o vetor de pivos
        decomposicaoLU(A, P,ordemA);
        resolveSisLin(A, B, ordemA);
    }
    else
    {
        printf("\n Valores fornecidas invalidas...");
    }

    return 0;
}
