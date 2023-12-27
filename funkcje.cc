#include <stdio.h>
#include <math.h>

#define N 20000
#define WYM 2
double const k=0.5;
double const B=2;
double const Eps = 1;


double *politropa(double x, double *y,double index)
{
  double *wynik;
  wynik = new double[WYM];
  wynik[0] = y[1];
  wynik[1] = -pow(y[0],index) - 2*y[1]/x;
  return wynik;
}

double *zero(double **tab, int wielkosc)
{
 
  //double wynik=-1;
  double *wynik;
  wynik = new double[3];
  
  for(int i=0; i<wielkosc;i++)
    {
      if(tab[i][1]<0)
	  {
	    wynik[0]=tab[i-1][0];
	    wynik[1]=tab[i-1][1];
	    wynik[2]=tab[i-1][2];
	    break;
	  }
    }
  return wynik;
}


