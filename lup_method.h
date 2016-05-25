//LUP-метод для решения СЛАУ.
#ifndef LUP_METHOD_H
#define LUP_METHOD_H

#endif // LUP_METHOD_H
#include <stdlib.h>

int lup_decompose(int,double**,int*,int&,int&);
void lup_solve(int, int*, double**, double*, double*,int&,int&);
double** p_matrix(int*,int);
