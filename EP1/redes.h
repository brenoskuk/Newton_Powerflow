#ifndef REDES_H_INCLUDED
#define REDES_H_INCLUDED

#include "barras.h"


barra** lerDadosBarras(char endereco[100], int* nBarras, int* nPQ, int* nPV, int *posPV, int *posSW);

barra** reorganizaBarras(barra **b, int nBarras);

void getMatrizAdmitancia(double **G, double **B, int tam, char fileName[100]);

void Jacobiana(double **J, int n1, int n2, barra* *b, double** condutancias, double** susceptancias);

void termoConhecido(barra **b, int n1,int n2, double *Fx);

#endif // REDES_H_INCLUDED
