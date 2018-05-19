#include <stdio.h>
#include <math.h>


//Elementos relativos ao teste 1
void F1(double **J, double *Fx, double *X)
{
    Fx[0] = 2*X[0]-4;
    Fx[1] = 2*X[1]-6;
    J[0][0] = 2;
    J[0][1] = 0;
    J[1][0] = 0;
    J[1][1] = 2;
}

void F2(double **J, double *Fx, double *X)
{
    Fx[0] = 4*X[0]-X[1]+X[2]-X[0]*X[3];
    Fx[1] = -X[0]+3*X[1]-2*X[2]-X[1]*X[3];
    Fx[2] = X[0]-2*X[1]+3*X[2]-X[2]*X[3];
    Fx[3] = X[0]*X[0]+X[1]*X[1]+X[2]*X[2]-1;
    J[0][0] = 4-X[3];
    J[0][1] = -1;
    J[0][2] = 1;
    J[0][3] = -X[0];
    J[1][0] = -1;
    J[1][1] = 3-X[3];
    J[1][2] = -2;
    J[1][3] = -X[1];
    J[2][0] = 1;
    J[2][1] = -2;
    J[2][2] = 3-X[3];
    J[2][3] = -X[2];
    J[3][0] = 2*X[0];
    J[3][1] = 2*X[1];
    J[3][2] = 2*X[2];
    J[3][3] = 0;
}

void F3(double **J, double *Fx, double *X, int n)
{
    int i,j;
    //Vetor de F(X)
    //A primeira linha da matriz eh feita manualmente
    Fx[0]= 2*X[0] - X[1] - exp(X[0])/pow(n,2);
    //A linha 1 ate a linha n-3 sao feitas pela iteracao
    for (i=1; i<n-2; i++)
    {
        Fx[i] = -X[i-1]+2*X[i]-X[i+1] - exp(X[i])/(pow(n,2));
    }
    //A linha n-1 eh feita manualmente
    Fx[n-2]= -X[n-3] + 2*X[n-2] - 1/(pow(n,2));

    //Jacobiano
    //A primeira linha do Jacobiano eh feita manualmente:
    J[0][0] = 2 - exp(X[0])/(pow(n,2));
    J[0][1] = -1;
    for(i=2; i<n-2; i++)
    {
        J[0][i] = 0;
    }
    //A partir da linha 2 eh feito um for
    for (i=1; i<n-2; i++)
    {
        //zera toda a linha i do jacobiano
        for (j=0; j<n-2; j++)
        {
            J[i][j] = 0;
        }
        //apenas 3 elementos serao diferentes de zero
        J[i][i-1] = -1;
        J[i][i] = 2 - exp(X[i])/(pow(n,2));
        J[i][i+1] = -1;
    }
    //Finalmente a linha n-1 eh zerada e feita manualmente
    for(i=0; i< n-2; i++)
    {
        J[n-2][i] = 0;
    }
    J[n-2][n-3] = -1;
    J[n-2][n-2] = 2 - exp(X[n-2])/(pow(n,2));
}
