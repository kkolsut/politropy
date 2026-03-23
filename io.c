//io.c

#include <stdio.h>
#include "io.h"
#include "calculations.h"


void print_matrix(double **tab, int rows, int cols)
{
  for(int i=0; i<rows; i++)
    {
      for(int ii=0; ii<cols; ii++)
	{
	  // newline after last column to wrap the matrix
	  if(ii==cols-1)
	    printf("%g\n",tab[i][ii]);
	  else
	    printf("%g\t",tab[i][ii]);
	}
    }
}

void print_parameters(FILE *fp, struct parameters params, int size)
{
  for(int i = 0; i < size; i++)
    {
      fprintf(fp, "%g\t%g\t%g\t%g\n", params.radius[i], params.density[i],
	      params.pressure[i], params.temperature[i]);
    }
}

void print_equation(FILE *fp, struct solution sol)
{
  for(int i = 0; i < sol.size; i++)
    {
      fprintf(fp, "%g\t%g\t%g\n", sol.xi[i], sol.theta[i][0],
	      sol.theta[i][1]);
    }
}

void print_all(FILE *fp, struct solution sol, struct parameters params)
{
  for(int i = 0; i < sol.size; i++)
    {
      fprintf(fp, "%g\t%g\t%g\t%g\t%g\t%g\t%g\n",
	      sol.xi[i], sol.theta[i][0], sol.theta[i][1],
	      params.radius[i], params.density[i],
	      params.pressure[i], params.temperature[i]);
    }
}
