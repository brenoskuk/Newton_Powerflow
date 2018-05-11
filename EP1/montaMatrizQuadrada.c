#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "montaMatrizQuadrada.h"


//MontaMatrizQuadrada retorna um ponteiro para a matriz lida
float** montaMatrizQuadrada(){
    FILE *input;
    FILE *outputFile1;

    float **matriz;
    int i,j,k;

    int n;

    char fileName[100];
    bool fileFound  = false;
    bool teste      = true;

    int sum=0;


    printf("Entre com o nome do arquivo (extensao incluida):  ");
    scanf("%[^\n]%*c",fileName);
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
        matriz = (float **)malloc(n * sizeof(int*));
        for(i = 0; i < n; i++)
            matriz[i] = (float *)malloc(n * sizeof(int));

        i=0;

        while(!feof(input)){
            for(i=0;i<n;i++){
                for(j=0;j<n;j++){
                    fscanf(input, "%f", &matriz[i][j]);
                }
            }
        }

        i=0;
        j=0;
        printf("\n\n");
        if (teste){
            //printa a matriz (para testes apenas)
            for(i=0;i<n;i++){
                for(j=0;j<n;j++){
                    printf("%f\t",matriz[i][j]);
                }
                printf("\n");
            }
            i=0;
            k=0;
        }
        printf("\n\n");

    }
    return matriz;
}
