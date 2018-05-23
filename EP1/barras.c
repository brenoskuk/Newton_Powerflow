#include <stdlib.h>
#include "barras.h"

barra* newPQ    (double ativa,   double reativa,  double vNom){
    barra* p = malloc(sizeof(barra));

    p->ativaEsp     = ativa;
    p->reativaEsp   = reativa;
    p->vnominal     = vNom;

    p->fase         = 0;
    p->modulo       = vNom;
    p->tensaoPU     = 1.0;
    p->tipo         = 0;

    return p;
}

barra* newPV    (double ativa,   double modulo,  double vNom){
    barra* p = malloc(sizeof(barra));

    p->ativaEsp     = ativa;
    p->modulo       = modulo;
    p->vnominal     = vNom;
    p->tensaoPU     = modulo/vNom;

    p->fase         = 0;
    p->tipo         = 1;

    return p;
}

barra* newSwing (double modulo,  double fase  ,  double vNom){
    barra* p = malloc(sizeof(barra));

    p->modulo   = modulo;
    p->fase     = fase;
    p->vnominal = vNom;
    p->tensaoPU = modulo/vNom;
    p->tipo     = 2;

    return p;
}


