#ifndef DERIVADASPARCIAIS_H_INCLUDED
#define DERIVADASPARCIAIS_H_INCLUDED

#include "barras.h"

double Dfp_Dtetak(int j, int k, barra**b, int nBarras, double** condutancias, double** susceptancias);

double Dfp_DVk (int j, int k, barra**b, int nBarras, double** condutancias, double** susceptancias);

double Dfq_Dthetak(int j, int k, barra**b, int nBarras, double** condutancias, double** susceptancias);

double Dfq_DVk(int j, int k, barra**b, int nBarras, double** condutancias, double** susceptancias);
#endif // DERIVADASPARCIAIS_H_INCLUDED
