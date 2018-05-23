#ifndef OPERACOES_H_INCLUDED
#define OPERACOES_H_INCLUDED

#include "barras.h"


double fq(int j, barra**b);

double fp(int j, barra**b);

void Pcal(int j, barra* *b, int nBarras, double** G, double** B);

void Qcal(int j, barra* *b, int nBarras, double** G, double** B);

double Dfp_Dtetak(int j, int k, barra**b, double** G, double** B);

double Dfp_DVk (int j, int k, barra**b, double** G, double** B);

double Dfq_Dthetak(int j, int k, barra**b, double** G, double** B);

double Dfq_DVk(int j, int k, barra**b, double** G, double** B);
#endif // OPERACOES_H_INCLUDED
