
struct solution
{
  double **theta;
  double *xi;
  int size;
};

struct parameters
{
  double *radius;
  double *density;
  double *pressure;
  double *temperature;
};

double *euler_step(double* (*f)(double,double*,double),double x,double* y,double h,int n,double index);

double **EN(double x0,double* y0,double* (*f)(double,double*,double),double h,int n
	    ,double* (*step)(double* (*f)(double,double*,double),double,double*,double,int),int dim);

double *runge_kutta_step(double* (*f)(double,double*,double),double x,double* y,double h,int n,double index);

double *heun_step(double* (*f)(double,double*,double),double x,double* y,double h,int n,double index);

double *adams_bashforth(double *(*f)(double, double*,double),double x,double **y,double h,int n,double index);

struct solution solve(double *(*f)(double, double*,double), double x, double h, int steps,double index, double memory);

struct parameters compute_physical_params(struct solution sol, double mass, double const_K, double mol_weight, double index);
