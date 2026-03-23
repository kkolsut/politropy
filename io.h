//io.h

#include <stdio.h>
#include "calculations.h"
void print_matrix(double **tab, int rows, int cols);

void print_parameters(FILE *fp, struct parameters params, int size);

void print_equation(FILE *fp, struct solution sol);

void print_all(FILE *fp, struct solution sol, struct parameters params);
