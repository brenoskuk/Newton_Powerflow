#ifndef ITERACAONEWTON_H_INCLUDED
#define ITERACAONEWTON_H_INCLUDED

#include "barras.h"


void iteracaoNewton (double **J, double *Fx, double *X, double *C, int n);

void iteracaoNewtonBarra (double **J, double *Fx, barra **b, double *C, int n1, int n2);

#endif // ITERACAONEWTON_H_INCLUDED
