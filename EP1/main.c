#include <stdio.h>
#include <stdlib.h>

#include "montaMatrizQuadrada.h"
#include "montaVetor.h"
#include "decomposicaoLU.h"

int main()
{
    float **A;
    float *B, *P;
    int ordemA, ordemB;

    char enderecoA[]="../matrizes/matrizA2.txt";
    char enderecoB[]="../matrizes/vetorB2.txt";

    A = montaMatrizQuadrada(enderecoA, &ordemA);
    B = montaVetor(enderecoB, &ordemB);
    P = (int *)malloc(ordemA * sizeof(int*));
    if (ordemA = ordemB)
    {
        //Aloca a memoria para o vetor de pivos
        decomposicaoLU(A, B, P,ordemA);
    }
    else
    {
        printf("\n Valores fornecidas invalidas...");
    }

    return 0;
}
