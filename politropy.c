#include "functions.h"
#include "calculations.h"
#include "io.h"
#include "opt.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define N 1024
#define DIM 2
#define SOLAR_MASS 1.9891e33




int main(int argc, char *argv[])
{
  // starting position and step size
  double x=0.0, h;
  double index, const_K, mass, mol_weight, memory;
  int output_mode;
  FILE *fp;
  // set default values - the user may override them via command-line options
  h=0.001;
  index=3.5;
  const_K = 4.5339e14;
  fp = stdout;
  mass = 1; // in solar masses
  mol_weight = 0.5; // for pure hydrogen
  memory = 1e7; // ~10MB available for index>=5;
                // for other indices we integrate until the zero is found
  output_mode=0;


  for(int i = 1; i < argc; i+=2)
    {
      if(strcmp(argv[i],"-k") == 0 || strcmp(argv[i],"--step") == 0)
	{
	  h = atof(argv[i+1]);
	}
      else if(strcmp(argv[i],"-i") == 0 || strcmp(argv[i],"--index") == 0)
	{
	  index = atof(argv[i+1]);
	}
      else if(strcmp(argv[i],"-s") == 0 || strcmp(argv[i],"--const") == 0)
	{
	  const_K = atof(argv[i+1]);
	}
      else if(strcmp(argv[i],"-m") == 0 || strcmp(argv[i],"--mass") == 0)
	{
	  mass = atof(argv[i+1]);
	}
      else if(strcmp(argv[i],"-f") == 0 || strcmp(argv[i],"--file") == 0)
	{
	  if((fp = fopen(argv[i+1], "w"))==NULL)
	    {
	      printf("error opening file %s\n", argv[i+1]);
	      exit(1);
	    }
	}
      else if(strcmp(argv[i],"-p") == 0 || strcmp(argv[i],"--memory") == 0)
	{
	  memory = atoi(argv[i+1])*1e6; // value given in megabytes
	}
      else if(strcmp(argv[i], "-z") == 0 || strcmp(argv[i],"--output") == 0)
	{
	  if(atoi(argv[i+1])>=0 && atoi(argv[i+1]) <=2)
	    output_mode = atoi(argv[i+1]);
	  else
	    {
	      option_error();
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
	      option_error();
	      exit(1);
	    }
	}
      else if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i],"--version") == 0)
	{
	  printf("version 0.6\n");
	  exit(0);
	}
      else
	{
	  option_error();
	  exit(1);
	}
    }
  // convert solar masses to CGS grams
  mass=mass*SOLAR_MASS;


  // solve the Lane-Emden equation
  struct solution result = solve(polytrope, x, h, N, index, memory);

  // compute physical parameters from the dimensionless solution
  struct parameters params = compute_physical_params(result, mass, const_K, mol_weight, index);

  // write output according to the selected mode
  if(output_mode == 0)
    print_all(fp, result, params);
  else if(output_mode == 1)
    print_equation(fp, result);
  else
    print_parameters(fp, params, result.size);


  return 0;
}
