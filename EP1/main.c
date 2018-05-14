#include <stdio.h>
#include <stdlib.h>

#include "montaMatrizQuadrada.h"
#include "decomposicaoLU.h"

int main(){
    float** A;
    float*  pB;
    float B[3] = {4, 0.5, 1.5};
    int n;
    pB = B;
    A = montaMatrizQuadrada(&n);
    decomposicaoLU(A, B, n);
    return 0;
}
