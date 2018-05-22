#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>
#include <math.h>

#include "redes.h"



void getMatrizBarras(double **BARRA, int *tam, char fileName[100]){

    FILE *input;

    int i,j;

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
        //le ordem da matriz
        fscanf(input,"%i",&n);
    }
    *tam = n;

    /**
    if(fileFound){
        //le ordem da matriz
        fscanf(input,"%i",&n);
        //aloca a matriz

        BARRA = (double **)calloc(n , sizeof(double*));
        for(i = 0; i < n; i++)
            BARRA[i] = (double *)calloc(n , sizeof(double));


        while(!feof(input)){
            for(i=0;i<n;i++){
                for(j=0;j<n;j++){
                    fscanf(input, "%lf", &matriz[i][j]);
                }
            }
        }

        i=0;
        j=0;
        if (teste){
            printf("\n\n");
            //printa a matriz (para testes apenas)
            for(i=0;i<n;i++){
                for(j=0;j<n;j++){
                    printf("%4lf\t",matriz[i][j]);
                }
                printf("\n");
            }
            i=0;
            j=0;
        }
        printf("\n\n");
        *tam = n;
    }
    **/
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
        for(i = 0; i < n; i++)
            B[i] = (double *)calloc(tam , sizeof(double));

        G = (double **)malloc(tam * sizeof(double*));
        for(i = 0; i < n; i++)
            G[i] = (double *)malloc(tam * sizeof(double));

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






