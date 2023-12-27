#include "obliczenia.h"
#include <stdio.h>
#include <math.h>

//stala grawitacji
#define G 6.6726e-8

//stala boltzmana
#define k 1.38066e-16

//masa atomowa
#define masa_atomowa 1.66054e-24

double *euler_krok(double* (*f)(double,double*,double),double x,double* y,double h,int n,double index)
{
  double *wynik=(*f)(x,y,index);
  for(int i=0;i<n;i++)
    wynik[i]=(y[i]+h*wynik[i]);
  return wynik;
}

double *dodaj(double *x,double *y,int n)
{
  double *wynik;
  wynik =  new double[n];
  for(int i=0;i<n;i++)
    wynik[i]=x[i]+y[i];
  return wynik;
}

double *odejmij(double *x,double *y,int n)
{
  double *wynik;
  wynik =  new double[n];
  for(int i=0;i<n;i++)
    wynik[i]=x[i]-y[i];
  return wynik;
}


double *mnoz(double* x,double h,int n)
{
  double *wynik;
  wynik =  new double[n];
  for(int i=0;i<n;i++)
    wynik[i]=x[i]*h;
  return wynik;
}



double *bashford(double *(*f)(double, double*,double),double x,double **y,double h,int n,double index)
{
  double *wynik,*fun1,*fun2;
  fun1=(*f)(x-h, y[0],index);
  fun2=(*f)(x,y[1],index);
  wynik=dodaj(y[1],mnoz(odejmij(mnoz(fun2,3,n),fun1,n),h/2,n),n);
  return wynik;
}

struct rozwiazanie rownanie(double *(*f)(double, double*,double), double x, double h, int kroki,double index, double pamiec)
{ 
  //zmienne pomocniocze i na wynik
  int wymiar=2;
  struct rozwiazanie wynik;
  int wyrazy_szeregu;
  wynik.rozmiar=kroki;
  
 
  
  wynik.tety = new double*[kroki];
  for(int i=0;i<kroki;i++)
    wynik.tety[i] = new double[2];
  
  wynik.ksi = new double[kroki];
  
  //zaczynamy od liczenia rozwiniecia w szereg, aby opuscic
  //byc w osobliwosci
  wyrazy_szeregu=int(kroki/100+2);
  for(int i=0;i<wyrazy_szeregu;i++)
    {
      
      wynik.ksi[i]=x;
      
      wynik.tety[i][0]=1-pow(x,2.)/6+index*pow(x,4.)/120;
      wynik.tety[i][1]=-x/3+index*pow(x,3.)/30;
      x=x+h;
    }
  
  
  for(int n = wyrazy_szeregu; n < kroki; n++)
    {	
      
      //liczymy "bashfordem"...
      wynik.tety[n]= bashford(f,x+(n-wyrazy_szeregu)*h, wynik.tety+n-2, h, wymiar, index);
      
      //i poprawiamy "moltonem"
      wynik.tety[n] = dodaj(wynik.tety[n-1], mnoz(dodaj(f(x+(n-wyrazy_szeregu)*h, wynik.tety[n],index), f(x+(n-wyrazy_szeregu-1)*h, wynik.tety[n-1],index), wymiar), h/2, wymiar), wymiar);
      
      
      wynik.ksi[n]=x+(n-wyrazy_szeregu)*h;
      if(wynik.tety[n-1][0]<0)
	{
	  wynik.rozmiar=n;
	  break;
	}
      
    }
  //sprawdzamy czy znalezlismy zero
  if(wynik.rozmiar==kroki)
    {
      //bedziemy szukac doskutku:)
      while(1)
	{
	  
	  //zwiekszymy obszar poszukiwania o 2x
	  int nowe_kroki=kroki*2;
	  int quit=0;
	  rozwiazanie nowy_wynik ;
	  wynik.rozmiar=nowe_kroki;
	  nowy_wynik.tety = new double*[nowe_kroki];
	  nowy_wynik.ksi = new double[nowe_kroki];
	  x=wynik.ksi[kroki-1];
	  //przepisujemy stara tablice do nowej
	  for(int i=0; i < kroki; i++)
	    {
	      nowy_wynik.tety[i]=wynik.tety[i];
	      nowy_wynik.ksi[i]=wynik.ksi[i];
	    }
	  wynik=nowy_wynik;
	  
	  for(int n=kroki; n<nowe_kroki; n++)
	    {
	      
	      wynik.tety[n]= bashford(f,x+(n-kroki+1)*h, wynik.tety+n-2, h, wymiar, index);
	      
	      
	      //i poprawiamy "moltonem"
	      wynik.tety[n] = dodaj(wynik.tety[n-1], mnoz(dodaj(f(x+(n-kroki+1)*h, wynik.tety[n],index), f(x+(n-kroki)*h, wynik.tety[n-1],index), wymiar), h/2, wymiar), wymiar);
	      
	      wynik.ksi[n]=x+(n-kroki+1)*h;
	      if(wynik.tety[n-1][0]<0)
		{
		  wynik.rozmiar=n;
		  quit=1;
		  break;
		}
	      
	    }
	  //okreslamy maxymalny rozmiar tablicy a tym samym
	  //do ktorego miejsca liczymy dla politropy o indexie = 5
	  if(((nowe_kroki*8*8)>pamiec))// && (index >= 5))
	    {
	      wynik.rozmiar=nowe_kroki;
	      break;
	    }
	  if(quit==1)
	    break;
	  kroki=nowe_kroki;
	  
	}
    }
  //zmniejszamy o 1 - czasami w ostatnim elemencie tablicy pojawia sie "nan"
  //nie wiem dokladnie dalczego
  wynik.rozmiar=wynik.rozmiar-1;
  return wynik;
  
}


struct parametry policz_wiekosci(struct rozwiazanie rownanie, double masa, double const_K, double ciezar_czast, double index)
{
  struct parametry wynik;
  double gestosc_centralna, an, stala_do_temp;
  
  //liczymy pare wielkosci posrednich
  an = sqrt((index+1)/(4*M_PI*G));
  
  stala_do_temp = masa_atomowa*ciezar_czast/k;
  double a1, a2, a3, a4;
  gestosc_centralna = pow((masa/(4*M_PI)) * pow(const_K,-3./2) * \
			  pow(-pow(rownanie.ksi[rownanie.rozmiar-1],2.)* \
			      rownanie.tety[rownanie.rozmiar-1][1],-1.) * \
			  pow(an,-3.), 2*index/(3 - index));
  a1 = masa/(4*M_PI);
  a2 = pow(const_K, -3./2);
  a3 = 1/(-pow(rownanie.ksi[rownanie.rozmiar-1],2.) * \
	  rownanie.tety[rownanie.rozmiar-1][1]);
  a4 = pow(an, -3.);
  
 
  gestosc_centralna = pow(a1 *a2 *a3*a4,2*index/(3-index));
  
  
  //alokujemy pamiec na wyniki
  wynik.promien = new double[rownanie.rozmiar];
  wynik.gestosc = new double[rownanie.rozmiar];
  wynik.cisnienie = new double[rownanie.rozmiar];
  wynik.temperatura = new double[rownanie.rozmiar];
 
 //   //i liczymy...
  for(int i = 0; i < rownanie.rozmiar; i++)
    {
      wynik.promien[i] = an * sqrt(const_K*pow(gestosc_centralna, 
					       1./(index - 1))) * rownanie.ksi[i];
      wynik.gestosc[i] = gestosc_centralna * pow(rownanie.tety[i][0], index);
      wynik.cisnienie[i] = const_K * pow(wynik.gestosc[i], ((double)index+1)/index);
      wynik.temperatura[i] = const_K * pow(wynik.gestosc[i],1./index) * stala_do_temp;
    }
 
    
  return wynik;
}




