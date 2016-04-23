#include "rev_method.h"

int rev_solve(float** A, float* X, int i)//Решение СЛАУ методом вращения.Возвращает количество операций.
{
    int counter = 0;//Счетчик количества операций
	float C, s, A1;//Временные переменые для математических операций
	for (int k = 0; k<i; k++)
	{
		for (unsigned int n = k + 1; n<i; n++)
		{
			C = A[k][k] / (sqrt((A[k][k] * A[k][k]) + (A[n][k] * A[n][k])));
			s = A[n][k] / (sqrt((A[k][k] * A[k][k]) + (A[n][k] * A[n][k])));
			for (unsigned int m = 0; m<i + 1; m++)
			{
				A1 = A[k][m];
				A[k][m] = C*A1 + s*A[n][m];
				A[n][m] = -s*A1 + C*A[n][m];
                counter++;
			}
		}
	}
	X[i - 1] = A[i - 1][i] / A[i - 1][i - 1];
	for (int n = i - 2; n >= 0; n--)
	{
		X[n] = A[n][i];
		for (unsigned int m = n + 1; m<i; m++)
		{
			X[n] -= A[n][m] * X[m];
            counter++;
		}
		X[n] /= A[n][n];
	}
	return counter;
}
