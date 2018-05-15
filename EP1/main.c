#include <stdio.h>
#include <stdlib.h>

#include "montaMatrizQuadrada.h"
#include "montaVetor.h"
#include "decomposicaoLU.h"

int main()
{
    float** A;
    float* B;
    int ordemA, ordemB;
    char enderecoA[]="../matrizes/matrizA2.txt";
    char enderecoB[]="../matrizes/vetorB2.txt";

    A = montaMatrizQuadrada(enderecoA, &ordemA);
    B = montaVetor(enderecoB, &ordemB);

    if (ordemA = ordemB)
    {
        decomposicaoLU(A, B, ordemA);
    }
    else
    {
        printf("\n Valores fornecidas invalidas...");
    }

    return 0;
}
