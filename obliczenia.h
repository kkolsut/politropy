
struct rozwiazanie
{
  double **tety;
  double *ksi; 
  int rozmiar;
};

struct parametry
{
  double *promien;
  double *gestosc;
  double *cisnienie;
  double *temperatura;
};

double *euler_krok(double* (*f)(double,double*,double),double x,double* y,double h,int n,double index);

double **EN(double x0,double* y0,double* (*f)(double,double*,double),double h,int n
	    ,double* (*krok)(double* (*f)(double,double*,double),double,double*,double,int),int wym);

double *kutta_krok(double* (*f)(double,double*,double),double x,double* y,double h,int n,double index);

double *heuna_krok(double* (*f)(double,double*,double),double x,double* y,double h,int n,double index);

double *bashford(double *(*f)(double, double*,double),double x,double **y,double h,int n,double index);

struct rozwiazanie rownanie(double *(*f)(double, double*,double), double x, double h, int kroki,double index, double pamiec);

struct parametry policz_wiekosci(struct rozwiazanie rownanie, double masa, double const_K, double ciezar_czast, double index);


