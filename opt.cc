#include <stdio.h>
#include "opt.h"


void help()
{
  printf("to jest pomoc\n");
  printf("Program buduje modele politropowe gwiazd\n\n");
  printf("Uzycie programu: ./plitropy [<opcje + parametry>]\n");
  printf("dostepne opcje:\n");
  printf("-i, --index     podajemy indeks politropy - modele fizyczne istnieja\n");
  printf("                dla 0<index<5 - wartosc domyslna 3.5\n");
  printf("-s, --stala     ustawia stala K wystepujaca w rownaiau politropy,\n");
  printf("                wartosc domyslna  4.5339e14\n");
  printf("-k, --krok      wielkosc kroku calkowania, dla duzych indeksow\n");
  printf("                oplaca sie dac wiekszy krok; warkosc domyslna 0.001\n");
  printf("-m, --masa      podajemy masa gwiazdy w masach slonca dla ktorej chcemy\n");
  printf("                zbudowac model - wartosc domyslna 1\n");
  printf("-f, --file      podajemy plik do ktorego chcemy zapisac dane\n");
  printf("                domyslnie stdout\n");
  printf("-z, --zapis     ustawiamy tryb zapisu danych:\n");
  printf("                  0 - zapisuje wszyskto (domyslne)\n");
  printf("                  1 - zapisuje tylko rozwiazanie rownania Lane'a - Emdena\n");
  printf("                  2 - zapsuje tylko wielkosci fizyczne\n");
  printf("                wiecej informacji w README\n");
  printf("-p, --pamiec    podajemy ilosc pamieci jaka program moze wykozystac\n");
  printf("                UWAGA!! uzywac tylko dla indeksow >= 5 (lub bliskich 5)\n");
  printf("                w przeciwnym wypadku moze spowodowac wyliczenie bladnego modelu!\n");
  printf("                jest to wartosc orientacyja a nie dokladna!! domyslnie ok 10MB\n");
  printf("-h, --help      wyswietla te pomoc\n");
  printf("-v, --version   wyswietla informacje o wersji programu\n");
  printf("\n");
  printf("autor: Krzysztof Kolsut\n");
  printf("       kolsut@antares.astrouw.edu.pl\n");
  printf("\n");
  printf("<zglaszanie bledow i uwag na w/w adres>\n");
  
  
}

void blad_opcji()
{
  printf("bladnie podana opcja\n");
  printf("sprobuj z opcja -h lub --help dla uzyskania wiecej informacji\n");
}
