#ifndef BARRAS_H_INCLUDED
#define BARRAS_H_INCLUDED

#ifndef BARRA_H
#define BARRA_H


struct mfar {

    double modulo;   //Módulo da Tensão na Barra;
    double fase;     //Fase da Tensão na Barra;

    double ativaEsp;     //Valor Especificado da Potência Ativa injetada na barra;
    double ativaCalc;    //Valor Calculado;

    double reativaEsp;   //Valor Especificado da Potência Reativa injetada na barra;
    double reativaCalc;  //Valor Calculado;

    double vnominal;
    int tipo;

    double tensaoPU;

    double Fp;




};
typedef struct mfar barra;

barra* newPQ    (double ativa,   double reativa,  double vNom); //representa uma carga, impedância constante, injeção externa de potência = 0;
barra* newPV    (double ativa,   double modulo,   double vNom); //representa um gerador;
barra* newSwing (double modulo,  double fase  ,   double vNom);

double modulo(barra* b);

#endif

#endif // BARRAS_H_INCLUDED
