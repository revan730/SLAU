#include "rev_method.h"

int rev_solve(float** A, float* X, int n)//Решение СЛАУ методом вращения.Возвращает количество операций.
{
    int counter = 0;//Счетчик количества операций
	float C, s, A1;//Временные переменые для математических операций
	for (int i = 0; i < n; i++)
	{
		for (int k = i + 1; k < n; k++)
		{
			C = A[i][i] / (sqrt((A[i][i] * A[i][i]) + (A[k][i] * A[k][i])));
			s = A[k][i] / (sqrt((A[i][i] * A[i][i]) + (A[k][i] * A[k][i])));
			for (int j = 0; j< n + 1; j++)
			{
				A1 = A[i][j];
				A[i][j] = C*A1 + s*A[k][j];
				A[k][j] = -s*A1 + C*A[k][j];
                counter++;
			}
		}
	}
	X[n - 1] = A[n - 1][n] / A[n - 1][n - 1];
	for (int i = n - 2; i >= 0; i--)
	{
		X[i] = A[i][n];
		for (int j = i + 1; j < n; j++)
		{
			X[i] -= A[i][j] * X[j];
            counter++;
		}
		X[i] /= A[i][i];
	}
	return counter;
}
