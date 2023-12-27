//io.h

#include <stdio.h>
void wypisz(double **tab, int N1, int M2);


void wypisz_wielkosci(FILE *fp, struct parametry wielkosci, int rozmair);

void wypisz_rownanie(FILE *fp, struct rozwiazanie rownanie);

void wypisz_wszystko(FILE *fp, struct rozwiazanie rownanie, struct parametry wielkosci);
