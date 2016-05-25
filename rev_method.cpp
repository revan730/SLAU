#include "rev_method.h"

int rev_solve(double** A, double* X, int n,int &ic,int &oc)//Решение СЛАУ методом вращения.
{
    ic = 0;//Счетчик количества итераций
    oc = 0;//Счетчик количества операций
    double C, s, A1;//Временные переменые для математических операций
    int start = clock();//Начальное значение времени
	for (int i = 0; i < n; i++)
	{
		for (int k = i + 1; k < n; k++)
		{
			C = A[i][i] / (sqrt((A[i][i] * A[i][i]) + (A[k][i] * A[k][i])));
            oc++;
			s = A[k][i] / (sqrt((A[i][i] * A[i][i]) + (A[k][i] * A[k][i])));
            oc++;
			for (int j = 0; j< n + 1; j++)
			{
                //Вычисление M,K
				A1 = A[i][j];
                oc++;
				A[i][j] = C*A1 + s*A[k][j];
                oc++;
				A[k][j] = -s*A1 + C*A[k][j];
                oc++;
                ic++;
			}
		}
	}
	X[n - 1] = A[n - 1][n] / A[n - 1][n - 1];
    oc++;
	for (int i = n - 2; i >= 0; i--)
	{
        //Обратный ход
		X[i] = A[i][n];
        oc++;
		for (int j = i + 1; j < n; j++)
		{
			X[i] -= A[i][j] * X[j];
            oc++;
            ic++;
		}
		X[i] /= A[i][i];
        oc++;
	}
    return clock() - start;//Время выполнения метода
}
