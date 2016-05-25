#include "lup_method.h"

int lup_decompose(int n,double  **A,int *P,int &ic,int &oc)
{
    //LUP - разложение матрицы А.Возвращает 0 при успешном разложении,-1 если матрица вырожденная.
            int temp, kd = 0;//temp - для временного хранения при перестановке в матрице P
            //kd - k`
            double temp_f = 0;//Для временного хранения при перестановке в матрице А
            for (int i = 0; i < n; i++)
            {
                    P[i] = i;//Инициализация массива p
                    ic++;
                    oc++;
            }
            for (int k = 0; k < n;k++)
            {
                    double p = 0;
                    for (int i = k; i < n;i++)
                    {
                            temp_f = A[i][k];
                            oc++;
                            if (temp_f < 0)
                            {
                             temp_f = -1 * temp_f;
                             oc++;
                            }
                            if (temp_f > p)
                            {
                                    p = temp_f;
                                    oc++;
                                    kd = i;
                                    oc++;
                            }
                            ic++;
                    }
                    if (p == 0)
                            return -1;//Определитель равен 0, разложение невозможно
                    temp = P[kd];
                    oc++;
                    P[kd] = P[k];
                    oc++;
                    P[k] = temp;
                    oc++;
                    for (int i = 0; i < n; i++)
                    {
                            temp_f = A[kd][i];
                            oc++;
                            A[kd][i] = A[k][i];
                            oc++;
                            A[k][i] = temp_f;
                            oc++;
                            ic++;
                    }
                    for (int i = k + 1; i < n; i++)
                    {
                        //Разложение матрицы А на матрицу U и L
                            A[i][k] = A[i][k] / A[k][k];
                            oc++;
                            for (int j = k + 1; j < n;j++)
                            {
                                    A[i][j] = A[i][j] - A[i][k] * A[k][j];
                                    oc++;
                                    ic++;
                            }
                    }
            }
            return 0;//Успешное завершение разложения
}

void lup_solve(int n,int *P,double **A,double *B,double *X,int &ic,int &oc)
{
	//Нахождение корней системы.
    double t;//Временная переменная для хранения суммы
    double *Y = (double*) malloc(n * sizeof(double));//Матрица - вектор Y
    for (int i = 0; i < n; i++)
            {
					//Нахождение матрицы - вектора Y
                    t = 0;
                    for ( int j = 0; j < i; j++)
                    {
						//Нахождение суммы
                            t += A[i][j] * Y[j];
                            oc++;
                            ic++;
                    }
                    Y[i] = B[P[i]] - t;
                    oc++;
            }
            for (int i = n - 1; i >= 0; i--)
            {
				//Нахождение матрицы - вектора X
                    t = 0;
                    for (int j = i + 1; j < n; j++)
                    {
						//Нахождение суммы
                            t += A[i][j] * X[j];
                            oc++;
                            ic++;
                    }
                    X[i] = (Y[i] - t) / A[i][i];
                    oc++;
            }
}

double** p_matrix(int* P,int n)
{
	//Пресдтавление P в виде матрицы
    double **Pm = new double *[n];
    for (int i = 0;i < n;i++)
        Pm[i] = new double[n];
    for (int i = 0; i < n;i++)
        for (int k = 0;k < n;k++)
            if (P[i] == k)
                Pm[i][k] = 1;
    return Pm;
}
