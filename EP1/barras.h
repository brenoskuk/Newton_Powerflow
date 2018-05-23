#ifndef BARRAS_H_INCLUDED
#define BARRAS_H_INCLUDED

#ifndef BARRAS_H
#define BARRAS_H


struct bar {

    double V;        //Módulo da Tensão na Barra;
    double fase;     //Fase da Tensão na Barra;

    double ativaEsp;     //Valor Especificado da Potência Ativa injetada na barra;
    double ativaCalc;    //Valor Calculado;

    double ativaNom;
    double reativaNom;

    double reativaEsp;   //Valor Especificado da Potência Reativa injetada na barra;
    double reativaCalc;  //Valor Calculado;

    double vnominal;
    int tipo;

    double Fp;




};
typedef struct bar barra;

barra* newPQ    (double ativa,   double reativa,  double vNom); //representa uma carga, impedância constante, injeção externa de potência = 0;
barra* newPV    (double ativa,   double V,   double vNom); //representa um gerador;
barra* newSwing (double V,  double fase  ,   double vNom);


double tensao(barra* b);
#endif

#endif // BARRAS_H_INCLUDED
