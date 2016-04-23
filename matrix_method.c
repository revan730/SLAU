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
