#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "montaMatrizQuadrada.h"
#include "montaVetor.h"
#include "decomposicaoLU.h"
#include "resolveSisLin.h"
#include "iteracaoNewton.h"


int main()
{
    double **J;
    double *Fx, *X, *C;
    double eps, maxC;
    int i,k,n, maxIteracoes, parada;


    eps = 0.001;
    maxIteracoes = 30;
    n = 2;
    J = (double **)malloc(n * sizeof(double*));
        for(i = 0; i < n; i++)
            J[i] = (double *)malloc(n * sizeof(double));

    Fx = (double *)calloc(n,  sizeof(double));
    X =  (double *)calloc(n, sizeof(double));
    C =  (double *)calloc(n, sizeof(double));
    //Define valores iniciais:

    X[0] = 0;
    X[1] = 0;
    parada = 0;
    k = 1;
    while ((parada == 0)&&(k < maxIteracoes))
    {

        Fx[0] = pow(X[0]-2, 2);
        Fx[1] = pow(X[1]-3, 2);
        J[0][0] = 2*X[0] - 4;
        J[0][1] = 0;
        J[1][0] = 0;
        J[1][1] = 2*X[1] - 6;

        printf("\nIteracao: %d\n", k);
        printf("\n[X]: \n");
        for(i=0; i<n; i++)
        {
            printf("%9.5f ",X[i]);
        }
        printf("\n");
        //Resolve uma iteracao do metodo de newton
        iteracaoNewton(J, Fx, X, C, n);

        //Captura o maior modulo de residuo
        maxC = fabs(C[0]);
        for (i=0; i<n; i++)
        {
            if(maxC < fabs(C[i]))
            {
                maxC = fabs(C[i]);
            }
        }
        //Verifica se o criterio de parada foi satisfeito
        if(maxC < eps)
        {
            parada = 1;
        }
        k++;
    }
    return 0;
}
