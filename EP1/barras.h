#ifndef BARRAS_H_INCLUDED
#define BARRAS_H_INCLUDED

#ifndef BARRAS_H
#define BARRAS_H


struct bar {

    double V;        //M�dulo da Tens�o na Barra;
    double fase;     //Fase da Tens�o na Barra;

    double ativaEsp;     //Valor Especificado da Pot�ncia Ativa injetada na barra;
    double ativaCalc;    //Valor Calculado;

    double ativaNom;
    double reativaNom;

    double reativaEsp;   //Valor Especificado da Pot�ncia Reativa injetada na barra;
    double reativaCalc;  //Valor Calculado;

    double vnominal;
    int tipo;
    int indice;

    double Fp;




};
typedef struct bar barra;

barra* newPQ    (int indice, double ativa,   double reativa,  double vNom); //representa uma carga, imped�ncia constante, inje��o externa de pot�ncia = 0;
barra* newPV    (int indice, double ativa,   double vNom); //representa um gerador;
barra* newSwing (int indice, double V,  double fase  ,   double vNom);
void copiaBarraPV (barra *b1, barra *b2);
void copiaBarraPQ (barra *b1, barra *b2);

double tensao(barra* b);

#endif
#endif // BARRAS_H_INCLUDED
