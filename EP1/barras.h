#ifndef BARRAS_H_INCLUDED
#define BARRAS_H_INCLUDED

#ifndef BARRA_H
#define BARRA_H


struct mfar {

    double modulo;   //M�dulo da Tens�o na Barra;
    double fase;     //Fase da Tens�o na Barra;

    double ativaEsp;     //Valor Especificado da Pot�ncia Ativa injetada na barra;
    double ativaCalc;    //Valor Calculado;

    double reativaEsp;   //Valor Especificado da Pot�ncia Reativa injetada na barra;
    double reativaCalc;  //Valor Calculado;

    double vnominal;
    int tipo;

    double tensaoPU;

    double Fp;




};
typedef struct mfar barra;

barra* newPQ    (double ativa,   double reativa,  double vNom); //representa uma carga, imped�ncia constante, inje��o externa de pot�ncia = 0;
barra* newPV    (double ativa,   double modulo,   double vNom); //representa um gerador;
barra* newSwing (double modulo,  double fase  ,   double vNom);

double modulo(barra* b);

#endif

#endif // BARRAS_H_INCLUDED
