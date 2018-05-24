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
#include "barras.h"
#include "operacoes.h"


int main()
{
    barra **b, **br;
    double **B, **G, **J, **BARRA;

    double *Fx, *C, *X;

    double eps, maxC;

    // btamanho en n1 + n2, tam eh 2n1 + n2
    int i, j, k, nPQ, nPV, btamanho, tam, maxIteracoes, parada, posPV, posSW;

    eps = 0.001;
    maxIteracoes = 30;

    //enderecos das redes
    char enderecoRede1Barras[]="../Redes/1_Stevenson/1_Stevenson_DadosBarras.txt";
    char enderecoRede1Y[]="../Redes/1_Stevenson/1_Stevenson_Ynodal.txt";
    char enderecoRede2Barras[]="../Redes/2_Reticulada/2_Reticulada_DadosBarras.txt";
    char enderecoRede2Y[]="../Redes/2_Reticulada/2_Reticulada_Ynodal.txt";
    char enderecoRede3Barras[]="../Redes/3_Distribuicao_Primaria/3_Distribuicao_Primaria_DadosBarras.txt";
    char enderecoRede3Y[]="../Redes/3_Distribuicao_Primaria/3_Distribuicao_Primaria_Ynodal.txt";
    char enderecoRede4Y[]="../Redes/4_Distribuicao_Pri_Sec/4_Distribuicao_Primaria_Secundaria_Ynodal.txt";
    char enderecoRede4Barras[]="../Redes/4_Distribuicao_Pri_Sec/4_Distribuicao_Primaria_Secundaria_DadosBarras.txt";


    // ordem en n1 + n2
    //montaMatrizQuadrada(enderecoRede, &ordem);
    b = lerDadosBarras( enderecoRede1Barras, &btamanho, &nPQ, &nPV ,&posPV, &posSW);
    tam = 2*nPQ + nPV;

    //aloca as matrizes e vetores que serao utilizados
    //tam eh 2n1 + n2 ... ordem eh n1 + n2
    Fx = (double *)calloc(tam, sizeof(double));

    C = (double *)calloc(tam, sizeof(double));

    J = (double **)calloc(tam, sizeof(double*));
        for(i = 0; i < 2*nPQ + nPV; i++)
        {
            J[i] = (double *)calloc(tam, sizeof(double));
        }


    G = (double **)calloc(btamanho , sizeof(double*));
        for(i = 0; i < btamanho; i++)
        {
             G[i] = (double *)calloc(btamanho , sizeof(double));
        }


    B = (double **)calloc(btamanho , sizeof(double*));
        for(i = 0; i < btamanho; i++)
        {
            B[i] = (double *)calloc(btamanho , sizeof(double));
        }

    getMatrizAdmitancia(G, B, btamanho, enderecoRede1Y);


    for(i=0; i<btamanho; i++)
    {
        for(j=0; j<btamanho; j++)
            printf("%9.5lf ", G[i][j]);
        printf("\n");
    }


    //O struct barra inicializa as barras nas condicoes inciais
    //Calcula Pesp e Qesp com base nos valores atuais
    for(j=0; j< btamanho; j++)
    {
        Pcal(j, b, btamanho, G, B);
        Qcal(j, b, btamanho, G, B);
    }

    parada = 0;
    k = 0;
    while ((parada == 0)&&(k < maxIteracoes))
    {
        br = reorganizaBarras(b, btamanho);

        //Calcula o termo conhecido rearranjado:
        termoConhecido(br, nPQ, nPV, Fx);

        //Calcula o Jacobiano rearranjado
        Jacobiana(J, nPQ, nPV, br , G, B);
        //Resolve uma iteracao do metodo de newton
        iteracaoNewtonBarra(J, Fx, br, b, C, nPQ, nPV);

        double guarda = fp(3,b);
        //Atualiza Pcal e Qcal
        for(j=0; j< btamanho; j++)
        {
            Pcal(j, b, btamanho, G, B);
            Qcal(j, b, btamanho, G, B);
        }
        printf("diff = %lf\n",guarda - fp(3,b));
        //Captura o maior modulo de residuo
        maxC = fabs(C[0]);
        for (i=0; i<tam; i++)
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
    printf("\n[tensoes]: \n");
    for(i=0; i<btamanho; i++)
    {
        printf("%d : %9.5lf /_ %9.5lf \n",i ,tensao(b[i]), b[i]->fase);
    }
    printf("\n");

    return 0;


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
