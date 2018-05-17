#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "montaMatrizQuadrada.h"


//MontaMatrizQuadrada retorna um ponteiro para a matriz lida
double** montaMatrizQuadrada(char fileName[100], int* tam){
    FILE *input;

    double **matriz;
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
        //aloca a matriz

        matriz = (double **)malloc(n * sizeof(double*));
        for(i = 0; i < n; i++)
            matriz[i] = (double *)malloc(n * sizeof(double));

        i=0;

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
    return matriz;
}
