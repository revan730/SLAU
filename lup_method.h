//LUP-метод для решения СЛАУ.
#ifndef LUP_METHOD_H
#define LUP_METHOD_H

#endif // LUP_METHOD_H
#include <stdlib.h>

int lup_decompose(int,float**);
void lup_solve(int, int*, float**, float*, float*);

int lup_decompose(int n,float  **A,int *P)
{
    //LUP - разложение матрицы А.Возвращает 0 при успешном разложении,-1 если матрица вырожденная.
            int temp, kd = 0;//temp - для временного хранения при перестановке в матрице P
            //kd - k`
            float temp_f = 0;//Для временного хранения при перестановке в матрице А
            for (int i = 0; i < n; i++)
            {
                    P[i] = i;
            }
            for (int k = 0; k < n;k++)
            {
                    float p = 0;
                    for (int i = k; i < n;i++)
                    {
                            temp_f = A[i][k];
                            if (temp_f < 0)
                                    temp_f = -1 * temp_f;
                            if (temp_f > p)
                            {
                                    p = temp_f;
                                    kd = i;
                            }
                    }
                    if (p == 0)
                            return -1;
                    temp = P[kd];
                    P[kd] = P[k];
                    P[k] = temp;
                    for (int i = 0; i < n; i++)
                    {
                            temp_f = A[kd][i];
                            A[kd][i] = A[k][i];
                            A[k][i] = temp_f;
                    }
                    for (int i = k + 1; i < n; i++)
                    {
                            A[i][k] = A[i][k] / A[k][k];
                            for (int j = k + 1; j < n;j++)
                                    A[i][j] = A[i][j] - A[i][k] * A[k][j];
                    }
            }
            return 0;
}

void lup_solve(int n,int *P,float **A,float *B,float *X)
{
	//Нахождение корней системы.
	float t;//Временная переменная для хранения суммы
    float *Y = (float*) malloc(n * sizeof(float));//Матрица - вектор Y
    for (int i = 0; i < n; i++)
            {
					//Нахождение матрицы - вектора Y
                    t = 0;
                    for ( int j = 0; j < i; j++)
                    {
						//Нахождение суммы
                            t += A[i][j] * Y[j];
                    }
                    Y[i] = B[P[i]] - t;
            }
            for (int i = n - 1; i >= 0; i--)
            {
				//Нахождение матрицы - вектора X
                    t = 0;
                    for (int j = i + 1; j < n; j++)
                    {
						//Нахождение суммы
                            t += A[i][j] * X[j];
                    }
                    X[i] = (Y[i] - t) / A[i][i];
            }
}
