#include <stdlib.h>
#include "barras.h"
/**
A construcao do struct barra determina as condicoes inciais

**/

double tensao(barra* b){
    return b->V;
}

barra* newPQ    (double ativa,   double reativa,  double vNom){
    barra* p = malloc(sizeof(barra));

    p->ativaEsp     = ativa;
    p->reativaEsp   = reativa;

    p->vnominal     = vNom;

    p->ativaCalc    = 0;
    p->reativaCalc  = 0;

    //Condicoes iniciais
    p->fase         = 0;
    p->V            = vNom;

    p->tipo         = 0;

    return p;
}

barra* newPV    (double ativa,   double modulo,  double vNom){
    barra* p = malloc(sizeof(barra));

    p->ativaEsp     = ativa;
    p->V            = vNom;
    p->vnominal     = vNom;


    p->reativaCalc  = 0;
    p->ativaCalc    = 0;

    p->fase         = 0;
    p->tipo         = 1;

    return p;
}

barra* newSwing (double modulo,  double fase  ,  double vNom){
    barra* p = malloc(sizeof(barra));

    p->V        = modulo;
    p->fase     = fase;
    p->vnominal = vNom;

    p->tipo     = 2;

    return p;
}


