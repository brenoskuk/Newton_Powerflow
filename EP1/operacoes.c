#include <string.h>
#include <math.h>

#include "operacoes.h"
#include "barras.h"



double fq(int j, barra**b)
{
        //igual para todas as barras
        return b[j]->reativaCalc;
return 0;
}

double fp(int j, barra**b)
{

    // se a barra eh do tipo PQ
    if (b[j]->tipo == 0)
    {
         return  b[j]->ativaCalc;
    }
    // se a barra eh do tipo PV
    if (b[j]->tipo == 1)
    {
        return  b[j]->ativaCalc - (b[j]->ativaEsp);
    }


return 0;
}

// Calcula a potencia ativa j como Re{S} usando as tensoes fases calculadas
void Pcal(int j, barra **b, int nBarras, double** G, double** B)
{

    double sum = 0;
    for(int k = 0; k < nBarras; k++)
    {
        sum = sum + ((tensao(b[k]))*(G[j][k]*cos(b[k]->fase-b[j]->fase) - B[j][k]*sin(b[k]->fase-b[j]->fase)));
    }
    b[j]->ativaCalc = sum*tensao(b[j]);
}

// Calcula a potencia aparente j como Im{S} usando as tensoes de fases calculadas
void Qcal(int j, barra **b,  int nBarras, double** G, double** B)
 {

    double sum = 0;

    for(int k = 0; k < nBarras; k++)
    {
            sum = sum + ((tensao(b[k]))*(G[j][k]*sin(b[k]->fase-b[j]->fase) + B[j][k]*cos(b[k]->fase-b[j]->fase)));
    }

    b[j]->reativaCalc = -sum*tensao(b[j]);

}

//Calcula a derivada parcial del(fpj)/del(tetak)
//Assume que Pcal e Qcal ja voram realizados para cada barra
double Dfpj_Dtetak(int j, int k, barra **b, double** G, double** B)
{

    //caso em que j = k
    if (j == k)
    {
        return -( b[j]->reativaCalc + tensao(b[j])*tensao(b[j])*B[j][j] );
    }
    //caso em que j eh diferente de k
    else
    {
        // VJVk(-Gjk.sen(thetakj) - Bjk.cos(thetakj))
        return -(tensao(b[j])*tensao(b[k]))*(G[j][k]*sin(b[k]->fase - b[j]->fase) + B[j][k]*cos(b[k]->fase - b[j]->fase) );
    }
}

//Calcula a derivada parcial del(fpj)/del(Vk)
//Assume que Pcal e Qcal ja voram realizados para cada barra
double Dfpj_DVk (int j, int k, barra**b, double** G, double** B)
{
    //se eh igual
    if (j == k)
    {
        return (b[j]->ativaCalc/tensao(b[j]) + tensao(b[j])*G[j][j]);
    }
    //se eh diferente : Vj(Gjk.cos(thetakj) - Bjk.sin(thetakj)
    else
    {
        return (tensao(b[j]))*(G[j][k]*cos(b[k]->fase-b[j]->fase) - B[j][k]*sin(b[k]->fase-b[j]->fase));
    }
}

//Calcula a derivada parcial del(fqj)/del(tetak)
//Assume que Pcal e Qcal ja voram realizados para cada barra
double Dfqj_Dthetak(int j, int k, barra**b, double** G, double** B)
{

    if (j == k)
    {
        return ( b[j]->ativaCalc - tensao(b[j])*tensao(b[j])*G[j][k]);
    }
    // -VjVk(Gjk cos(thetakj) - Bjk sin(thetakj))
    else
    {
        return -(tensao(b[j])*tensao(b[k])*(G[j][k]*cos(b[k]->fase - b[j]->fase) + B[j][k]*sin(b[k]->fase - b[j]->fase) ));
    }
}

//Calcula a derivada parcial del(fqj)/del(tetak)
//Assume que Pcal e Qcal ja voram realizados para cada barra
double Dfqj_DVk(int j, int k, barra**b, double** G, double** B)
{

    if (j == k)
    {
        return (b[j]->reativaCalc/tensao(b[j]) - tensao(b[j])*B[j][j]);
    }
    // -Vj(Gjk sin(thetakj) + Bjk cos(thetakj))
    else
    {
        return -(tensao(b[j]))*(G[j][k]*sin(b[k]->fase-b[j]->fase) + B[j][k]*cos(b[k]->fase-b[j]->fase));
    }
}
