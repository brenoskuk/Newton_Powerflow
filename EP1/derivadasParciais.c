#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>
#include <math.h>

#include "barras.h"

double Fq(int v, barra**b){
        if (b[v]->tipo == 0)
            return b[v]->reativaCalc;

        else
            printf("erro! A barra não é PQ");
return 0;
}

double Fp(int v, barra**b){

    //printf("dentro de Fp:%lf\n", Pativa);
    if (b[v]->tipo == 0)
        return  b[v]->ativaCalc;
       // printf("dentro da funcao fp:%lf\n", fp);

    if (b[v]->tipo == 1)
        return  b[v]->ativaCalc - (b[v]->ativaEsp);
      //  printf("%lf\n", fp):

    if (b[v]->tipo == 2)
        printf("Erro! A barra passada é tipo Swing");

return 0;
}

void Pcal(int j, barra* *b,  int nBarras, double** condutancias, double** susceptancias) {

    double A = 0;
    for(int k = 0; k < nBarras; k++) {
            A += ((modulo(b[k]))*(condutancias[j][k]*cos(b[k]->fase-b[j]->fase) - susceptancias[j][k]*sin(b[k]->fase-b[j]->fase)));
    }
    b[j]->ativaCalc = modulo(b[j])*A;
}

void Qcal(int j, barra* *b,  int nBarras, double** condutancias, double** susceptancias) {

    double A = 0;

    for(int k = 0; k < nBarras; k++) {
            A += ((modulo(b[k]))*(condutancias[j][k]*sin(b[k]->fase-b[j]->fase) + susceptancias[j][k]*cos(b[k]->fase-b[j]->fase)));
    }

    b[j]->reativaCalc = -modulo(b[j])*A;

}

double Dfp_Dtetak(int j, int k, barra**b, int nBarras, double** condutancias, double** susceptancias) {

    if (j == k){
        Qcal(j, b, nBarras, condutancias, susceptancias);
        return -( b[j]->reativaCalc + modulo(b[j])*modulo(b[j])*susceptancias[j][j] );
    }
    else {
        /*printf("\n********************\nDfp_Dtetak(j = %d,k = %d)\n\n", j, k);
        printf("V[j=%d]*V[k=%d]*(G[j=%d][k=%d]*sen(T[k=%d]-T[j=%d])+B[j=%d][k=%d]*cos(.)", j, k, j, k, k, j, j, k);
        printf("\n-(%f)*(%f)*((%f)*sin(%f - %f)+(%f)*cos(%f - %f))", modulo(b[j]), modulo(b[k]), condutancias[j][k], b[k]->fase, b[j]->fase, susceptancias[j][k], b[k]->fase, b[j]->fase);
        printf("\n\n******************");*/
        return -(modulo(b[j])*modulo(b[k]))*(condutancias[j][k]*sin(b[k]->fase - b[j]->fase) + susceptancias[j][k]*cos(b[k]->fase - b[j]->fase) );
    }

    return 265;
}

double Dfp_DVk (int j, int k, barra**b, int nBarras, double** condutancias, double** susceptancias) {

    if (j == k) {
        Pcal(j, b, nBarras, condutancias, susceptancias);
        return (b[j]->ativaCalc/modulo(b[j]) + modulo(b[j])*condutancias[j][j]);
    } else {
        /*printf("\n********************\nDfp_DVk(j = %d,k = %d)\n\n", j, k);
        printf("V[j=%d]*(G[j=%d][k=%d]*cos(T[k=%d]-T[j=%d])-B[j=%d][k=%d]*sen(.))", j, j, k, k, j, j, k);
        printf("\n(%f)*[(%f)*cos(%f - %f)-(%f)*sen(%f - %f)]", modulo(b[j]), condutancias[j][k], b[k]->fase, b[j]->fase, susceptancias[j][k], b[k]->fase, b[j]->fase);
        printf("\n\n******************");*/
        return (modulo(b[j]))*(condutancias[j][k]*cos(b[k]->fase-b[j]->fase) - susceptancias[j][k]*sin(b[k]->fase-b[j]->fase));
    }
}

double Dfq_Dthetak(int j, int k, barra**b, int nBarras, double** condutancias, double** susceptancias){

    if (j == k){
        Pcal(j, b, nBarras, condutancias, susceptancias);
        return ( b[j]->ativaCalc - modulo(b[j])*modulo(b[j])* (condutancias[j][k]*cos(b[k]->fase - b[j]->fase) - susceptancias[j][k]*sin(b[k]->fase - b[j]->fase)) );
    }
    else {
        /*printf("\n********************\nDfq_Dthetak(j = %d,k = %d)\n\n", j, k);
        printf("-V[j=%d]*V[k=%d]*(G[j=%d][k=%d]*cos(T[k=%d]-T[j=%d])+B[j=%d][k=%d]*sen(.)", j, k, j, k, k, j, j, k);
        printf("\n-(%f)*(%f)*((%f)*cos(%f - %f)+(%f)*sin(%f - %f))", modulo(b[j]), modulo(b[k]), condutancias[j][k], b[k]->fase, b[j]->fase, susceptancias[j][k], b[k]->fase, b[j]->fase);
        printf("\n\n******************");*/
        return -(modulo(b[j])*modulo(b[k])*(condutancias[j][k]*cos(b[k]->fase - b[j]->fase) + susceptancias[j][k]*sin(b[k]->fase - b[j]->fase) ));
    }

    return 0;
}

double Dfq_DVk(int j, int k, barra**b, int nBarras, double** condutancias, double** susceptancias){
    if (j == k) {
        Qcal(j, b, nBarras, condutancias, susceptancias);
        return (b[j]->reativaCalc/modulo(b[j]) - modulo(b[j])*susceptancias[j][j]);
    } else {
        return -(modulo(b[j]))*(condutancias[j][k]*sin(b[k]->fase-b[j]->fase) + susceptancias[j][k]*cos(b[k]->fase-b[j]->fase));
    }
}
