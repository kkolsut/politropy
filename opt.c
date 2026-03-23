#include <stdio.h>
#include "opt.h"


void help()
{
  printf("Program builds polytropic models of stars\n\n");
  printf("Usage: ./politropy [<options + parameters>]\n");
  printf("Available options:\n");
  printf("-i, --index     polytropic index - physical models exist\n");
  printf("                for 0<index<5 - default value 3.5\n");
  printf("-s, --const     sets the constant K in the polytropic equation,\n");
  printf("                default value 4.5339e14\n");
  printf("-k, --step      integration step size, for large indices\n");
  printf("                a larger step is worthwhile; default value 0.001\n");
  printf("-m, --mass      star mass in solar masses for which to\n");
  printf("                build the model - default value 1\n");
  printf("-f, --file      output file to write results to,\n");
  printf("                default is stdout\n");
  printf("-z, --output    sets the data output mode:\n");
  printf("                  0 - write everything (default)\n");
  printf("                  1 - write only the Lane-Emden equation solution\n");
  printf("                  2 - write only physical parameters\n");
  printf("                more information in README\n");
  printf("-p, --memory    maximum memory the program may use\n");
  printf("                WARNING!! use only for indices >= 5 (or close to 5)\n");
  printf("                otherwise may produce an incorrect model!\n");
  printf("                this is an approximate value, not exact!! default ~10MB\n");
  printf("-h, --help      display this help\n");
  printf("-v, --version   display program version\n");
  printf("\n");
  printf("author: Krzysztof Kolsut\n");
  printf("        kolsut@antares.astrouw.edu.pl\n");
  printf("\n");
  printf("<report bugs and comments to the above address>\n");
}

void option_error()
{
  printf("invalid option\n");
  printf("try -h or --help for more information\n");
}
