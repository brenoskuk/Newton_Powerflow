#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "montaMatrizQuadrada.h"
#include "montaVetor.h"
#include "decomposicaoLU.h"
#include "resolveSisLin.h"
#include "iteracaoNewton.h"
#include "redes.h"
#include "testes.h"

int main()
{

    double **B, **G, **BARRA;

    int i, j, ordem;

    char enderecoRede1Barras[]="../Redes/1_Stevenson/1_Stevenson_DadosBarras.txt";
    char enderecoRede1Y[]="../Redes/1_Stevenson/1_Stevenson_Ynodal.txt";
    char enderecoRede4[]="../Redes/4_Distribuicao_Pri_Sec/4_Distribuicao_Primaria_Secundaria_Ynodal.txt";

    //montaMatrizQuadrada(enderecoRede, &ordem);
    getMatrizBarras(BARRA, &ordem, enderecoRede1Barras);
    getMatrizAdmitancia(B, G, ordem, enderecoRede1Y);







    /**
    int teste;
    printf("**** Testes ****\n");
    printf ("0)Teste 1 - cond. iniciais = (0,0)\n");
    printf ("1)Teste 2 - cond. iniciais = (1,1,1,1)\n");
    printf ("2)Teste 3 - n = 20 - cond. iniciais nulas\n");
    printf ("3)Teste 3 - n = 40 - cond. iniciais nulas\n");
    printf ("4)Teste 3 - n = 80 - cond. iniciais nulas\n");
    printf ("Selecione um teste: ");
    scanf ("%d", &teste);
    printf("\n");
    executaTestes(teste);
    **/

    /**
    double **J;
    double *Fx, *X, *C;
    double eps, maxC;
    int i,k,n, maxIteracoes, parada;


    eps = 0.00001;
    maxIteracoes = 30;
    n = 3;

    J = (double **)malloc(n * sizeof(double*));
        for(i = 0; i < n; i++)
            J[i] = (double *)malloc(n * sizeof(double));

    Fx = (double *)calloc(n, sizeof(double));
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

        //Atualiza J, Fx e X de acordo com Stevenson
        Stevenson(J, Fx, X);

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
        else{
            k++;
        }

    }
    //Imprime os resultados
    printf("Numero de iteracoes: %d\n", k);
    printf("Erro: %3.5lf\n", eps);
    printf("\n[X]: \n");
    for(i=0; i<n; i++)
    {
        printf("%9.5f ",X[i]);
    }
    printf("\n");
    free(J);
    free(X);
    free(Fx);
    free(C);
    return 0;
}
**/


}
