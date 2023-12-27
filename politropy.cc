#include "funkcje.h"
#include "obliczenia.h"
#include "io.h"
#include "opt.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define N 1024
#define WYM 2
#define masa_slonca  1.9891e33




int main(int argc, char *argv[])
{
  //miejsce poczatkowe i krok
  double x=0.0, h;
  double index, const_K, masa, ciezar_czasteczkowy, pamiec;
  int tryb_wypisywania;
  FILE *fp;
  //ustawiamy wartosci domyslne - jesli uzytkownik zechce moze je zmienic 
  //przez parametry wywolania programu
  h=0.001;
  index=3.5;
  const_K = 4.5339e14;
  fp = stdout;
  masa = 1; //w masach slonca
  ciezar_czasteczkowy = 0.5; //dla czystego wodoru
  pamiec = 1e7; //mamy do dyspozyzji ok 10MB dla n>=5,
                //dla innych liczymy do skutku
  tryb_wypisywania=0;
 

  for(int i = 1; i < argc; i+=2)
    {
      if(strcmp(argv[i],"-k") == 0 || strcmp(argv[i],"--krok") == 0)
	{
	  h = atof(argv[i+1]); 
	}
      else if(strcmp(argv[i],"-i") == 0 || strcmp(argv[i],"--index") == 0)
	{
	  index = atof(argv[i+1]);
	}
      else if(strcmp(argv[i],"-s") == 0 || strcmp(argv[i],"--stala") == 0)
	{
	  const_K = atof(argv[i+1]);
	}
      else if(strcmp(argv[i],"-m") == 0 || strcmp(argv[i],"--masa") == 0)
	{
	  masa = atof(argv[i+1]);
	}
      else if(strcmp(argv[i],"-f") == 0 || strcmp(argv[i],"--file") == 0)
	{
	  if((fp = fopen(argv[i+1], "w"))==NULL)
	    {
	      printf("blad podczas otwieranie pliku %s\n", argv[i+1]);
	      exit(1);
	    }
	}
      else if(strcmp(argv[i],"-p") == 0 || strcmp(argv[i],"--pamiec") == 0)
	{
	  pamiec = atoi(argv[i+1])*1e6; //w megabajtach
	}
      else if(strcmp(argv[i], "-z") == 0 || strcmp(argv[i],"--zapis") == 0)
	{
	  if(atoi(argv[i+1])>=0 && atoi(argv[i+1]) <=2)
	    tryb_wypisywania = atoi(argv[i+1]);
	  else
	    {
	      blad_opcji();
	      exit(1);
	    }
	}
      else if(strcmp(argv[i],"-h") == 0 || strcmp(argv[i],"--help") == 0)
	{
	  if(i==1)
	    {
	      help();
	      exit(0);
	    }
	  else 
	    {
	      blad_opcji();
	      exit(1);
	    }
	}
      else if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i],"--version") == 0)
	{
	  printf("wersja 0.6\n");
	  exit(0);
	}
      else
	{
	  blad_opcji();
	  exit(1);
	  
	}
    }
  //zmianiamy mase slonca na mase w cgs
  masa=masa*masa_slonca;
  

 
  //zmienna na wynik rozwiazania rownanie
  rozwiazanie wynik;
  
  //rozwiazujemy rownanie
  wynik = rownanie(politropa,x,h, N, index, pamiec);
  
  //zmienna na wielkosci fizyczne
  parametry wielkosci;
  //obliczany je
  wielkosci = policz_wiekosci(wynik, masa, const_K, ciezar_czasteczkowy, index);

  //wypisujemy w zaleznosci od podanej opcji
  if(tryb_wypisywania == 0)
    wypisz_wszystko(fp, wynik, wielkosci);
  else if(tryb_wypisywania == 1)
    wypisz_rownanie(fp, wynik);
  else
    wypisz_wielkosci(fp, wielkosci, wynik.rozmiar);
  
      
 
  return 0;
}







