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
    barra **b;
    double Vnom, leitura1, leitura2;
    int i, tipo, contQ, contV;
    FILE* dadosBarras;
    dadosBarras = fopen(endereco, "r");
    fscanf(dadosBarras, "%d", nBarras);

    //atencao: o malloc recebe o tamanho do struct
    b = malloc(*nBarras * sizeof(barra*));

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

    fclose(dadosBarras);
    *nPQ = contQ;
    *nPV = contV;

    return b;
}


/**
Monta as matrizes de condutancias e suseptancias
 OBS: TOMA COMO PARAMETRO O TAMANHO OBTIDO POR getMatrizBarras
**/
void getMatrizAdmitancia(double **G, double **B, int tam, char fileName[100]){

    FILE *input;

    int i, ri, rj;

    int n;

    bool fileFound  = false;

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

        while(!feof(input)){
            //Le as linhas do arquivo
            for(i=0;i<n;i++){
                fscanf(input, "%i", &ri);
                fscanf(input, "%i", &rj);
                fscanf(input, "%lf", &G[ri][rj]);
                fscanf(input, "%lf", &B[ri][rj]);
            }
        }
    }
}

/**
Preenche o vetor F1 dado um estado de barras da rede
      Fx tem tamanho 2n1 + n2
obs:  Assume que a barra 0 eh tipo Swing
**/
void termoConhecido(barra **b, int n1,int n2, double *Fx){
    int i, j, k, nPV;


    //Captura a posicao da barra PV
    for(i=0 ; i < n1 + n2; i++)
    {
        if(b[i]->tipo == 1)
        {
            nPV=i;
        }
    }

    //Calcula a parte de FP de F
    //Note que a barra swing nao contribui com o sistema de equacoes

    for(j=1; j < n1 + n2 +1; j++)
    {
        Fx[j-1] = fp(j,b);
    }

     k=1;
   //Calcula a parte de FQ de F
    for(j = n1+n2 + 1; j < 2*n1+n2 + 1; j++)
    {
        Fx[j] = fq(k,b);
        k++;
    }


}

/**
Preenche o Jacobiano dado um estado de barras da rede

obs: Assume que a barra 0 eh tipo Swing
**/
void Jacobiana(double **J, int n1, int n2, barra **b, double **G, double **B) {
    int j, k, centro;
    centro = n1 + n2;
    //Calcula o primeiro "quadrante" do Jacobiano


    //Sao as derivadas parciais fpj com relacao a thetak
    for ( j = 1; j <= centro; j++)
    {
        for (int k = 1; k <= centro; k++)
        {
            J[j-1][k-1] = Dfpj_Dtetak(j, k, b, G, B);
        }
    }
    //Calcula o segundo "quadrante" do Jacobiano

    //Sao as derivadas parciais fpj com relacao a Vk
    for (int j = centro; j <= centro + n1; j++)
    {
        for (int k = 1; k <= centro; k++)
        {
            J[j-1][k-1] = Dfpj_DVk(j-centro, k, b, G, B);
        }
    }

    //Calcula o terceiro "quadrante" do Jacobiano

    //Sao as derivadas parciais fqj com relacao a Thetak
    for (int j = 1; j <= centro; j++)
    {
        for (int k = centro; k <= centro + n1; k++)
        {
            J[j-1][k-1] = Dfqj_Dthetak(j, k - centro, b, G, B);
        }
    }

    //Calcula o quarto "quadrante" do Jacobiano

    //Sao as derivadas parciais fqj com relacao a Vk
    for (int j = centro; j <= centro + n1; j++)
    {
        for (int k = centro; k <= centro + n1; k++)
        {
            J[j-1][k-1] = Dfqj_DVk(j-centro, k-centro, b, G, B);
        }
    }

}




