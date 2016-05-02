//Реализация матричного метода для решения СЛАУ.
#ifndef MATRIX_METHOD_H
#define MATRIX_METHOD_H

#endif // MATRIX_METHOD_H
#include <math.h>
#include <stdlib.h>
#include "lup_method.h"

float det(float**,int);
float** multiply(float**,float**,int,int,int,int);
float** inverse(float**,int);
void solve(float**,float**,float*,int);
int lup_decompose(int,float,int);
void matrix_solve(float**,float**,float*,int);
