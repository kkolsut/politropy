#include "calculations.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// gravitational constant
#define G 6.6726e-8

// Boltzmann constant
#define k 1.38066e-16

// atomic mass unit
#define ATOMIC_MASS 1.66054e-24

double *euler_step(double* (*f)(double,double*,double),double x,double* y,double h,int n,double index)
{
  double *result=(*f)(x,y,index);
  for(int i=0;i<n;i++)
    result[i]=(y[i]+h*result[i]);
  return result;
}

double *add(double *x,double *y,int n)
{
  double *result;
  result = (double*)malloc(n * sizeof(double));
  for(int i=0;i<n;i++)
    result[i]=x[i]+y[i];
  return result;
}

double *subtract(double *x,double *y,int n)
{
  double *result;
  result = (double*)malloc(n * sizeof(double));
  for(int i=0;i<n;i++)
    result[i]=x[i]-y[i];
  return result;
}

double *multiply(double* x,double h,int n)
{
  double *result;
  result = (double*)malloc(n * sizeof(double));
  for(int i=0;i<n;i++)
    result[i]=x[i]*h;
  return result;
}


double *adams_bashforth(double *(*f)(double, double*,double),double x,double **y,double h,int n,double index)
{
  double *result,*fun1,*fun2;
  fun1=(*f)(x-h, y[0],index);
  fun2=(*f)(x,y[1],index);
  result=add(y[1],multiply(subtract(multiply(fun2,3,n),fun1,n),h/2,n),n);
  return result;
}

struct solution solve(double *(*f)(double, double*,double), double x, double h, int steps, double index, double memory)
{
  int dim=2;
  struct solution result;
  int series_terms;
  result.size=steps;

  result.theta = (double**)malloc(steps * sizeof(double*));
  for(int i=0;i<steps;i++)
    result.theta[i] = (double*)malloc(2 * sizeof(double));

  result.xi = (double*)malloc(steps * sizeof(double));

  // start with a power series expansion to step away from the singularity at xi=0
  series_terms=(int)(steps/100+2);
  for(int i=0;i<series_terms;i++)
    {
      result.xi[i]=x;
      result.theta[i][0]=1-pow(x,2.)/6+index*pow(x,4.)/120;
      result.theta[i][1]=-x/3+index*pow(x,3.)/30;
      x=x+h;
    }


  for(int n = series_terms; n < steps; n++)
    {
      // predictor step (Adams-Bashforth)
      result.theta[n]= adams_bashforth(f,x+(n-series_terms)*h, result.theta+n-2, h, dim, index);

      // corrector step (Adams-Moulton)
      result.theta[n] = add(result.theta[n-1], multiply(add(f(x+(n-series_terms)*h, result.theta[n],index), f(x+(n-series_terms-1)*h, result.theta[n-1],index), dim), h/2, dim), dim);

      result.xi[n]=x+(n-series_terms)*h;
      if(result.theta[n-1][0]<0)
	{
	  result.size=n;
	  break;
	}
    }

  // if zero not found within initial allocation, keep doubling the search range
  if(result.size==steps)
    {
      while(1)
	{
	  // double the search range
	  int new_steps=steps*2;
	  int quit=0;
	  struct solution new_result;
	  result.size=new_steps;
	  new_result.theta = (double**)malloc(new_steps * sizeof(double*));
	  new_result.xi = (double*)malloc(new_steps * sizeof(double));
	  x=result.xi[steps-1];
	  // copy old array into new
	  for(int i=0; i < steps; i++)
	    {
	      new_result.theta[i]=result.theta[i];
	      new_result.xi[i]=result.xi[i];
	    }
	  result=new_result;

	  for(int n=steps; n<new_steps; n++)
	    {
	      // predictor step (Adams-Bashforth)
	      result.theta[n]= adams_bashforth(f,x+(n-steps+1)*h, result.theta+n-2, h, dim, index);

	      // corrector step (Adams-Moulton)
	      result.theta[n] = add(result.theta[n-1], multiply(add(f(x+(n-steps+1)*h, result.theta[n],index), f(x+(n-steps)*h, result.theta[n-1],index), dim), h/2, dim), dim);

	      result.xi[n]=x+(n-steps+1)*h;
	      if(result.theta[n-1][0]<0)
		{
		  result.size=n;
		  quit=1;
		  break;
		}
	    }
	  // enforce memory limit (relevant for index >= 5 which may never reach zero)
	  if(((new_steps*8*8)>memory))
	    {
	      result.size=new_steps;
	      break;
	    }
	  if(quit==1)
	    break;
	  steps=new_steps;
	}
    }
  // trim by 1 - the last element occasionally contains NaN (reason unknown)
  result.size=result.size-1;
  return result;
}


struct parameters compute_physical_params(struct solution sol, double mass, double const_K, double mol_weight, double index)
{
  struct parameters result;
  double central_density, an, temp_const;

  // compute intermediate scale factors
  an = sqrt((index+1)/(4*M_PI*G));

  temp_const = ATOMIC_MASS*mol_weight/k;
  double a1, a2, a3, a4;
  a1 = mass/(4*M_PI);
  a2 = pow(const_K, -3./2);
  a3 = 1/(-pow(sol.xi[sol.size-1],2.) * sol.theta[sol.size-1][1]);
  a4 = pow(an, -3.);

  central_density = pow(a1*a2*a3*a4, 2*index/(3-index));

  // allocate result arrays
  result.radius      = (double*)malloc(sol.size * sizeof(double));
  result.density     = (double*)malloc(sol.size * sizeof(double));
  result.pressure    = (double*)malloc(sol.size * sizeof(double));
  result.temperature = (double*)malloc(sol.size * sizeof(double));

  // compute physical quantities at each grid point
  for(int i = 0; i < sol.size; i++)
    {
      result.radius[i]      = an * sqrt(const_K*pow(central_density, 1./(index - 1))) * sol.xi[i];
      result.density[i]     = central_density * pow(sol.theta[i][0], index);
      result.pressure[i]    = const_K * pow(result.density[i], ((double)index+1)/index);
      result.temperature[i] = const_K * pow(result.density[i], 1./index) * temp_const;
    }

  return result;
}
