#include "matrix_method.h"
 
float det(float **a,int n) {
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
