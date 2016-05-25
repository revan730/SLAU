#include "matrix_method.h"

double det(double **a,int n)//Нахождение определителя матрицы с помощью LUP-метода
{
    double **T = new double *[n];
    int *P = new int [n];
    int s,q;
    double Det = 1;
    for (int i = 0;i < n;i++)
        T[i] = new double [n];

    for (int i = 0;i < n;i++)
        for (int j = 0; j < n;j++)
            T[i][j] = a[i][j];

    if (lup_decompose(n,T,P,s,q) != -1)
    {
        for (int i = 0;i < n;i++)
           Det *= T[i][i];
        delete[] T;
        delete[] P;
        return Det;
    }
    else
    {
        delete[] T;
        delete[] P;
        return 0;
    }

}

double** multiply(double **A,double **B,int r1,int r2,int c1,int c2,int &ic,int &oc)
{
	//Умножение матриц
    double **C = new double *[r1];
   	for (int i = 0;i < r1;i++)
	{
        C[i] = new double[c2];
		for (int k = 0;k < c2;k++)
			C[i][k] = 0;
	}
	if (c1 == r2)
	{
	for (int i = 0;i < r1;i++)
		for (int j = 0;j < c2;j++)
			for (int k = 0;k < c1;k++)
            {
				C[i][j] +=A[i][k] * B[k][j];
                oc++;
                ic++;
            }
  	return C;
	}
	else return NULL;
}

double** inverse(double **A,int n,int &ic,int &oc)
{
	//Нахождение обратной матрицы с помощью LUP-декомпозиции
    double **I = new double *[n];
    for (int i = 0;i < n;i++)
        I[i] = new double[n];
    for (int i = 0 ;i < n;i++)
        for (int j = 0; j < n;j++)
            I[i][j] = 0;

    int *P = new int[n];
    lup_decompose(n,A,P,ic,oc);

     for(int k = n-1; k >= 0; k--)
     {
        I[k][k] = 1;
        oc++;
        for( int j = n-1; j > k; j--)
        {
            I[k][k] -= A[k][j] * I[j][k];
            oc++;
            ic++;
        }
        I[k][k] /= A[k][k];
        oc++;
        for( int i = k-1; i >= 0; i-- )
        {
            for( int j = n-1; j > i; j-- )
            {
                I[i][k] -= A[i][j] * I[j][k];
                oc++;
                I[k][i] -= A[j][i] * I[k][j];
                oc++;
                ic++;
            }
            I[i][k] /= A[i][i];
            oc++;
        }
 }
 double **Pm = p_matrix(P,n);

 return multiply(I,Pm,n,n,n,n,ic,oc);//Умножаем на матрицу перестановок для получение правильного порядка строк
}

void matrix_solve(double **Ar,double **B,double *X,int n,int &ic,int &oc)
{
	//Решение СЛАУ матричным методом
    double **S = multiply(Ar,B,n,n,n,1,ic,oc);
    for (int i = 0;i < n;i++)
    {
        X[i] = S[i][0];
        oc++;
        ic++;
    }
	delete[] S;
}
