#include <stdio.h>
#include <stdlib.h>

#include "montaMatrizQuadrada.h"
#include "decomposicaoLU.h"

int main(){
    float** A;
    float*  pB;
    float B[4] = {1, 2, 3, 4};

    pB = B;
    A = montaMatrizQuadrada();
    decomposicaoLU(A, pB, 4);
    return 0;
}
