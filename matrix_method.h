//Реализация матричного метода для решения СЛАУ.
#ifndef MATRIX_METHOD_H
#define MATRIX_METHOD_H

#endif // MATRIX_METHOD_H
#include <math.h>
#include <stdlib.h>
#include "lup_method.h"

double det(double**,int);
double** multiply(double**,double**,int,int,int,int,int&,int&);
double** inverse(double**,int,int&,int&);
void solve(double**,double**,double*,int,int&,int&);
int lup_decompose(int,double,int);
void matrix_solve(double**,double**,double*,int,int&,int&);
