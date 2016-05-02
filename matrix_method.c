#include "matrix_method.h"

float det(float **a,int n) {
	//Нахождение определителя матрицы
  float determinant = 0;
  float **temp = new float *[n];
  for (int i = 0;i < n;i++)
	  temp[i] = new float[n];
  int p,h,k,i,j;
  if(n == 1) {
    return a[0][0];
  } else if(n == 2) {
    determinant = (a[0][0] * a[1][1] - a[0][1] * a[1][0]);
    return determinant;
  } else {
    for(p = 0;p < n;p++) {
      h = 0;
      k = 0;
      for(i = 1;i < n;i++) {
        for(j = 0;j < n;j++) {
          if(j == p) {
            continue;
          }
          temp[h][k] = a[i][j];
          k++;
          if(k == n-1) {
            h++;
            k = 0;
          }
        }
      }
      determinant = determinant + a[0][p] * pow(-1,p) * det(temp,n-1);
    }
	delete[] temp;
    return determinant;
  }
}

float** multiply(float **A,float **B,int r1,int r2,int c1,int c2)
{
	//Умножение матриц
	float **C = new float *[r1];
   	for (int i = 0;i < r1;i++)
	{
		C[i] = new float[c2];
		for (int k = 0;k < c2;k++)
			C[i][k] = 0;
	}
	if (c1 == r2)
	{
	for (int i = 0;i < r1;i++)
		for (int j = 0;j < c2;j++)
			for (int k = 0;k < c1;k++)
				C[i][j] +=A[i][k] * B[k][j];
  	return C;
	}
	else return NULL;
}

float** inverse(float **A,int n)
{
	//Нахождение обратной матрицы с помощью LUP-декомпозиции
    float **I = new float *[n];
    for (int i = 0;i < n;i++)
        I[i] = new float[n];
    int P[3] = {0,0,0};
    lup_decompose(n,A,P);
     for(int k = n-1; k >= 0; k--) {
    I[ k ][ k ] = 1;
    for( int j = n-1; j > k; j--)
        I[ k ][ k ] -= A[ k ][ j ] * I[ j ][ k ];
    I[ k ][ k ] /= A[ k ][ k ];
    for( int i = k-1; i >= 0; i-- )
    {
        for( int j = n-1; j > i; j-- )
        {
            I[ i ][ k ] -= A[ i ][ j ] * I[ j ][ k ];
            I[ k ][ i ] -= A[ j ][ i ] * I[ k ][ j ];
        }
        I[ i ][ k ] /= A[ i ][ i ];
    }
 }
 //X = X*P;
 float **Pm = p_matrix(P,n);

 return multiply(I,Pm,n,n,n,n);
}

void matrix_solve(float **Ar,float **B,float *X,int n)
{
	//Решение СЛАУ матричным методом
    float **S = multiply(Ar,B,n,n,n,1);
    for (int i = 0;i < n;i++)
        X[i] = S[i][0];
	delete[] S;
}
