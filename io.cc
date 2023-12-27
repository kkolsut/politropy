//io.cc

#include <stdio.h>
#include "io.h"
#include "obliczenia.h"


void wypisz(double **tab, int N1, int M2)
{
  
  for(int i=0;i<N1;i++)
    {
      for(int ii=0;ii<M2;ii++)
	{
	  //zeby zawinac macierz:)))
	  if(ii==M2-1)
	    printf("%g\n",tab[i][ii]);
	  else
	    printf("%g\t",tab[i][ii]);
	  
	}
    }
}

void wypisz_wielkosci(FILE *fp, struct parametry wielkosci, int rozmiar)
{
  for(int i = 0; i < rozmiar; i++)
    {
      fprintf(fp, "%g\t%g\t%g\t%g\n", wielkosci.promien[i], wielkosci.gestosc[i],
	      wielkosci.cisnienie[i], wielkosci.temperatura[i]);
    }
}

void wypisz_rownanie(FILE *fp, struct rozwiazanie rownanie)
{
  for(int i = 0; i < rownanie.rozmiar; i++)
    {
      fprintf(fp, "%g\t%g\t%g\n", rownanie.ksi[i], rownanie.tety[i][0],
	      rownanie.tety[i][1]);
    }
}

void wypisz_wszystko(FILE *fp, struct rozwiazanie rownanie, struct parametry wielkosci)
{
  for(int i = 0; i < rownanie.rozmiar; i++)
    {
      fprintf(fp, "%g\t%g\t%g\t%g\t%g\t%g\t%g\n",
	      rownanie.ksi[i], rownanie.tety[i][0], rownanie.tety[i][1],
	      wielkosci.promien[i], wielkosci.gestosc[i],
	      wielkosci.cisnienie[i], wielkosci.temperatura[i]);
    }
}
