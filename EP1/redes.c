#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>
#include <math.h>

#include "operacoes.h"
#include "barras.h"
#include "redes.h"

/**
A partir do struct barra le os dados e cria um vetor de barras
**/
barra** lerDadosBarras(char endereco[100], int* nBarras, int* nPQ, int* nPV){
    double Vnom, leitura1, leitura2;
    int i, tipo, contQ, contV;
    FILE* dadosBarras;
    dadosBarras = fopen(endereco, "r");
    fscanf(dadosBarras, "%d", nBarras);

    //atencao: o malloc recebe o tamanho do struct
    barra **b = malloc(*nBarras * sizeof(barra*));

    contQ = 0;
    contV = 0;
    for (int c = 0; c < *nBarras; c++){

        fscanf(dadosBarras, "%d", &i);
        if (i != c){
            printf("Erro !");
        }

        fscanf(dadosBarras, "%d", &tipo);
        fscanf(dadosBarras, "%lf", &Vnom);
        fscanf(dadosBarras, "%lf", &leitura1);
        fscanf(dadosBarras, "%lf", &leitura2);

        switch (tipo){
            if (tipo == 0)
            {
                b[c] = newPQ((double)leitura1, (double)leitura2, Vnom);
                contQ++;
            }
            else if (tipo == 1)
            {
                b[c] = newPV((double)leitura1, (double)leitura2, Vnom);
                contV++;
            }
            else if (tipo == 2)
            {
                b[c] = newSwing((double)leitura1, (double)leitura2, Vnom);
            }
            else
            {
                printf("Erro na leitura da matriz de Barras");
            }
        }
    }

    fclose(dadosBarras);
    *nPQ = contQ;
    *nPV = contV;

    return b;
}


/**
Monta as matrizes de condutancias e suseptancias
 OBS: TOMA COMO PARAMETRO O TAMANHO OBTIDO POR getMatrizBarras
**/
void getMatrizAdmitancia(double **B, double **G, int tam, char fileName[100]){

    FILE *input;

    int i,j, ri, rj;

    int n;

    bool fileFound  = false;
    bool teste      = true;


    //printf("Entre com o nome do arquivo (extensao incluida):  ");
    //scanf("%[^\n]%*c", fileName);
    input = fopen(fileName,"r");
    if(input){
        fileFound=true;
    }
    else{
        printf("Erro: Arquivo nao encontrado!\n");
        fileFound=false;
    }

    if(fileFound){
        //le numero de linhas do .txt
        fscanf(input,"%i",&n);

        //aloca as matrizes de acordo com a ordem ja encontrada no .txt das barras
        B = (double **)calloc(tam , sizeof(double*));
        for(i = 0; i < tam; i++)

            B[i] = (double *)calloc(tam , sizeof(double));

        G = (double **)calloc(tam , sizeof(double*));
        for(i = 0; i < tam; i++)
            G[i] = (double *)calloc(tam , sizeof(double));

        while(!feof(input)){
            //Le as linhas do arquivo
            for(i=0;i<n;i++){
                fscanf(input, "%i", &ri);
                fscanf(input, "%i", &rj);
                fscanf(input, "%lf", &B[ri][rj]);
                fscanf(input, "%lf", &G[ri][rj]);
            }
        }

        if (teste){

            printf("B:\n");
            //printa a matriz (para testes apenas)
            for(i=0;i<tam;i++){
                for(j=0;j<tam;j++){
                    printf("%4lf\t",B[i][j]);
                }
                printf("\n");
            }
            printf("G:\n");
            for(i=0;i<tam;i++){
                for(j=0;j<tam;j++){
                    printf("%4lf\t",G[i][j]);
                }
                printf("\n");
            }

        }
    }
}

/**
Preenche o vetor F1 dado um estado de barras da rede 1
      Fx tem tamanho 2n1 + n2
obs:  Assume que a barra 0 eh tipo Swing
**/
void termoConhecido(barra **b, int n1,int n2, double *Fx){
    int j, k, nPV;

    //Captura a posicao da barra PV
    for(int i=0 ; i < n1 + n2 + 1; i++){
        if(b[i]->tipo == 1)
            nPV=i;
    }

    //Calcula a parte de FP de F
    //Note que a barra swing nao contribui com o sistema de equacoes

    for(int j=0; j<n1 + n2; j++)
    {
        Fx[j] = fp(j,b);
    }

   //Calcula a parte de FQ de F
    for(int j = n1+n2; j < 2*n1+n2; j++)
    {
        Fx[j] = fq(j,b);
    }


}

void Jacobiana(double **J, int n1, int n2, barra* *b, double** condutancias, double** susceptancias) {
    int nBarras = n1+n2+1;
    int tamanhoJ = 2*n1 + n2;


    //i -> coluna (vai pra direita)
    //j -> linha  (vai pra baixo)

    //1ª Parte
    int limI = n1 + n2;
    int limJ = n1 + n2;
    for (int j = 1; j <= limJ; j++) {
        for (int i = 1; i <= limI; i++) {

            J[i-1][j-1] = Dfp_Dtetak(i, j, b, condutancias, susceptancias);

            //printf("J[%d][%d] = %.3e\t", i-1, j-1, J[i-1][j-1]);
        }
        //printf("\n");
    }
    printf("\ntudo ok...\n");
    //printf("\n\n");

    //2ª Parte
    limI = nBarras;
    limJ = n1 + n2;
    int l = n1 + n2;
    for (int j = 1; j <= limJ; j++) {
        int contaPQ = 0;
        for (int i = 0; i < limI; i++) {
            if (b[i]->tipo == 0) {
                J[l+contaPQ][j-1] = Dfp_DVk(j, i, b, condutancias, susceptancias);
                //printf("J[%d][%d] = %.3e\t", l+contaPQ, j-1, J[l+contaPQ][j-1]);
                contaPQ++;
            }
        }
        //printf("\n");
    }

    //printf("\n\n");

    //3ª Parte
    limI = n1 + n2;
    limJ = n1 + n2;
    for (int i = 1; i <= limI; i++) {
        int contaPQ = n1+n2;
        for (int j = 1; j <= limJ; j++) {
            if (b[j]->tipo == 0) {
                J[i-1][contaPQ] = Dfq_Dthetak(j, i, b, condutancias, susceptancias);
                //printf("J[%d][%d] = %.3e\t", i-1, contaPQ, J[i-1][contaPQ]);
                contaPQ++;
            }
        }
        //printf("\n");
    }

    //printf("\n\n");

    //4ª Parte
    limI = nBarras; //(2*n1 + n2) - (n1 + n2)
    limJ = nBarras; //(2*n1 + n2) - (n1 + n2)
    l = n1 + n2;
    int contaI = 0, contaJ = 0;
    for (int i = 1; i < limI; i++) {
        if (b[i]->tipo == 0) {
            for (int j = 1; j < limJ; j++) {
                if(b[j]->tipo == 0){
                    J[contaI+l][contaJ+l] = Dfq_DVk(j, i, b, condutancias, susceptancias);
                    //printf("J[%d][%d] = %.3e\t", contaI+l, contaJ+l, J[contaI+l][contaJ+l]);
                    contaJ++;
                }
            }
            contaJ = 0;
            contaI++;
            //printf("\n");
        }
    }

}




