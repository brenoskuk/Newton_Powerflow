#ifndef REDES_H_INCLUDED
#define REDES_H_INCLUDED

#include "barras.h"


barra** lerDadosBarras(char fileName[100], int* nBarras, int* nPQ, int* nPV);

void getMatrizAdmitancia(double **condutancias, double **susceptancias, int tam, char fileName[100]);

void Jacobiana(double **J, int n1, int n2, barra* *b, double** condutancias, double** susceptancias);

void stevenson(barra**b, int n1, int n2, double *Fx);

#endif // REDES_H_INCLUDED
