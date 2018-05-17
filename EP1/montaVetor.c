#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "montaVetor.h"


//MontaMatrizVetor retorna um ponteiro para o vetor lido
double* montaVetor(char fileName[100], int* tam){
    FILE *input;


    double *vetor;
    int i;
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
        printf("Erro: Arquivo de vetor nao encontrado!\n");
        fileFound=false;
    }

    if(fileFound){
        //le tamanho do vetor
        fscanf(input,"%i",&n);
        //aloca o tamanho do vetor

        vetor = (double *)malloc(n * sizeof(double*));

        while(!feof(input)){
            for(i=0;i<n;i++){
                fscanf(input, "%lf", &vetor[i]);
                }
            }
        }

        i=0;

        if (teste){
            printf("\n\n");
            //printa o vetor (para testes apenas)
            for(i=0;i<n;i++){
                printf("%4lf\t",vetor[i]);
            }
            printf("\n");

        }
        printf("\n\n");
        *tam = n;

    return vetor;
}
