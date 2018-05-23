#ifndef REDES_H_INCLUDED
#define REDES_H_INCLUDED

#include "barras.h"


barra** lerDadosBarras(char fileName[100], int* nBarras, int* nPQ, int* nPV);

void getMatrizAdmitancia(double **condutancias, double **susceptancias, int tam, char fileName[100]);

double** Jacobiana(int n1, int n2, barra* *b, double** condutancias, double** susceptancias);

void montaF(barra**b, int n1, int n2, double *F);

#endif // REDES_H_INCLUDED
