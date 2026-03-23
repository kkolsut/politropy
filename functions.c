#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 20000
#define DIM 2
double const k=0.5;
double const B=2;
double const Eps = 1;


double *polytrope(double x, double *y, double index)
{
  double *result;
  result = (double*)malloc(DIM * sizeof(double));
  result[0] = y[1];
  result[1] = -pow(y[0],index) - 2*y[1]/x;
  return result;
}

double *find_zero(double **tab, int size)
{
  double *result;
  result = (double*)malloc(3 * sizeof(double));

  for(int i=0; i<size; i++)
    {
      if(tab[i][1]<0)
	  {
	    result[0]=tab[i-1][0];
	    result[1]=tab[i-1][1];
	    result[2]=tab[i-1][2];
	    break;
	  }
    }
  return result;
}
