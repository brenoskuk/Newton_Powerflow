#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>
#include <math.h>

#include "derivadasParciais.h"
#include "barras.h"
#include "redes.h"


barra** lerDadosBarras(char endereco[100], int* nBarras, int* nPQ, int* nPV){
    int q = 0; //nPQ
    int v = 0; //nPV
    FILE* dadosBarras;
    dadosBarras = fopen(endereco, "r");
    fscanf(dadosBarras, "%d", nBarras);

    barra **b = malloc(*nBarras * sizeof(barra*));

    int i, tipo;
    double vNominal, leitura4, leitura5;
    for (int c = 0; c < *nBarras; c++){

        fscanf(dadosBarras, "%d", &i);
        if (i != c){
            printf("Erro !");
        }

        fscanf(dadosBarras, "%d", &tipo);
        fscanf(dadosBarras, "%lf", &vNominal);
        fscanf(dadosBarras, "%lf", &leitura4);
        fscanf(dadosBarras, "%lf", &leitura5);

        switch (tipo){
            case 0: //É PQ
                b[c] = newPQ((double)leitura4, (double)leitura5, vNominal);
                q++;
                break;

            case 1: //É PV
                b[c] = newPV((double)leitura4, (double)leitura5, vNominal);
                v++;
                break;

            case 2: //É Swing
                b[c] = newSwing((double)leitura4, (double)leitura5, vNominal);
                break;

            default:
                printf("Erro na leitura do tipo de barra");
                break;
        }
    }

    fclose(dadosBarras);
    *nPQ = q;
    *nPV = v;

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
Preenche o vetor F dado um estado de barras previo

obs: Assume que F tem tamanho 2n1 + n2
**/
void montaF(barra**b, int n1, int n2, int ordem,  double *F){
    int k, j, w, nBarras;

    nBarras = n1 + n2 + 1;
    //encontra a posição da barra PV e guarda em w.
    for(int i = 0; i < nBarras; i++)
    {
        if(b[i]->tipo==1)
            w=i;
       // printf("%d\n", w);
    }
    //preenche a parte de FP de F
    for(int i = 1;ordem<;i++)
    {
        F[j] = Fp(i,b);
        j++;
    }


   //preenche a parte de FQ de F
    for(int i = n1+n2+1;i<2*n1+n2+1;i++){

       if(i>=w+(n1+n2))         //pula a PV
            k = i-(n1+n2)+1;
       else
            k = i-(n1+n2);
        F[j] = Fq(k,b);
        j++;
     //   printf ("k: %d\n", k);
    }

   for(int i =0;i<2*n1+n2;i++){
        F[i] = -F[i];
        printf("F[%d]: %lf\n", i, F[i]);
    }
}

double** Jacobiana(int n1, int n2, barra* *b, double** condutancias, double** susceptancias) {
    int nBarras = n1+n2+1;
    int tamanhoJ = 2*n1 + n2;

    double **J = malloc(tamanhoJ * sizeof(double*));

    for (int i = 0; i < tamanhoJ; i++) {
        J[i] = calloc(tamanhoJ, sizeof(double));
    }

    //i -> coluna (vai pra direita)
    //j -> linha  (vai pra baixo)

    //1ª Parte
    int limI = n1 + n2;
    int limJ = n1 + n2;
    for (int j = 1; j <= limJ; j++) {
        for (int i = 1; i <= limI; i++) {
            J[i-1][j-1] = Dfp_Dtetak(j, i, b, nBarras, condutancias, susceptancias);
            //printf("J[%d][%d] = %.3e\t", i-1, j-1, J[i-1][j-1]);
        }
        //printf("\n");
    }

    //printf("\n\n");

    //2ª Parte
    limI = nBarras;
    limJ = n1 + n2;
    int l = n1 + n2;
    for (int j = 1; j <= limJ; j++) {
        int contaPQ = 0;
        for (int i = 0; i < limI; i++) {
            if (b[i]->tipo == 0) {
                J[l+contaPQ][j-1] = Dfp_DVk(j, i, b, nBarras, condutancias, susceptancias);
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
                J[i-1][contaPQ] = Dfq_Dthetak(j, i, b, nBarras, condutancias, susceptancias);
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
                    J[contaI+l][contaJ+l] = Dfq_DVk(j, i, b, nBarras, condutancias, susceptancias);
                    //printf("J[%d][%d] = %.3e\t", contaI+l, contaJ+l, J[contaI+l][contaJ+l]);
                    contaJ++;
                }
            }
            contaJ = 0;
            contaI++;
            //printf("\n");
        }
    }

    return J;


}




