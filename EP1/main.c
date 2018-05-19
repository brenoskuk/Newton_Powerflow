#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "montaMatrizQuadrada.h"
#include "montaVetor.h"
#include "decomposicaoLU.h"
#include "resolveSisLin.h"
#include "iteracaoNewton.h"
#include "testes.h"

int main()
{
    double **J;
    double *Fx, *X, *C;
    double eps, maxC;
    int i,k,n, maxIteracoes, parada;


    eps = 0.001;
    maxIteracoes = 30;
    n = 19;

    J = (double **)malloc(n * sizeof(double*));
        for(i = 0; i < n; i++)
            J[i] = (double *)malloc(n * sizeof(double));

    Fx = (double *)calloc(n,  sizeof(double));
    X =  (double *)calloc(n, sizeof(double));
    C =  (double *)calloc(n, sizeof(double));
    //Define valores iniciais:
    for (i=0;i<n;i++)
    {
        X[i] = 0;
    }

    parada = 0;
    k = 0;
    while ((parada == 0)&&(k < maxIteracoes))
    {
        F3(J, Fx, X, n+1);
        printf("\n[J]: \n");
        for(i=0; i<n; i++)
        {
            int j;
            for(j=0; j<n;j++)
                printf("%9.3f ",J[i][j]);
            printf("\n");
        }
        printf("\n");
        printf("\n[Fx]: \n");
        for(i=0; i<n; i++)
        {
            printf("%9.3f ",Fx[i]);
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
        else
        {
            k++;
        }
    }
    //Imprime os resultados
    printf("Numero de iteracoes: %d", k);
    printf("\n[X]: \n");
    for(i=0; i<n; i++)
    {
        printf("%9.5f ",X[i]);
    }
    printf("\n");

    return 0;
}
