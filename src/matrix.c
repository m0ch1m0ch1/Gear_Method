/*
  matrix.c : Function for inversion of Jacobian matrix
*/

#include "common.h"

/* ---------------------- Inversion of Jacobian matrix --------------------- */

void Matrix_inversion(double *f, double a0){

  static int i, j, k, i1, i2;
  static double sum1, sum2, sum3, sum4;
  static double dlt, ysave, xmax, xx, dtemp;

  switch(imat){

    // 0の場合
    case 0:
      for(i=0;i<number_x;i++){
        f[i] /= scale[0][i];
      }

      f[0] /= pw[0][0];

      for(i=1;i<number_x;i++){
        sum2 = 0.0;

        for(j=0;j<i;j++){
          sum2 += pw[i][j] * f[j];
        }

        f[i] = (f[i] - sum2) / pw[i][i];
      }

      break;
    //--------------------------------

    // 1の場合
    case 1:
      for(i=0;i<number_x;i++){
        Differential_equation();

        for(j=0;j<number_x;j++){
          scale[0][j] = df[j];
        }

        ysave = y[0][i];
        dlt = convergence;

        if (dlt < ysave){
          dlt = ysave;
        }

        dlt *= convergence;
        y[0][i] += dlt;

        Differential_equation();

        y[0][i] = ysave;

        for(j=0;j<number_x;j++){
          jacobimat[j][i] = (df[j] - scale[0][j]) / dlt;
        }
      }
    //--------------------------------

    // 2の場合
    case 2:
      imat = 0;

      for(i=0;i<number_x;i++){
        for(j=0;j<number_x;j++){
	         pw[i][j] = jacobimat[i][j] * (a0 * step);
        }
      }

      for(i=0;i<number_x;i++){
        pw[i][i] += 1.0;
      }

      for(i=0;i<number_x;i++){
        xmax = 0.0;

        for(j=0;j<number_x;j++){
          dtemp = pw[i][j];
          xx = fabs(dtemp);

          if (xx > xmax){
            xmax = xx;
          }
        }

        scale[0][i] = xmax;
        f[i] /= xmax;

        for(j=0;j<number_x;j++){
          pw[i][j] /= xmax;
        }
      }

      for(i=0;i<number_x;i++){
        xmax = 0.0;

        for(j=0;j<number_x;j++){
          dtemp = pw[j][i];
          xx = fabs(dtemp);

          if (xx > xmax){
            xmax = xx;
          }
        }

        scale[1][i] = xmax;

        for(j=0;j<number_x;j++){
          pw[j][i] /= xmax;
        }
      }

      f[0] /= pw[0][0];

      for(k=1;k<number_x;k++){
        pw[0][k] /= pw[0][0];
        sum3 = pw[0][k] * pw[k][0];
        sum4 = pw[k][0] * f[0];

        if (k != 1){
          for(i=1;i<k;i++){
            sum1 = 0.0;
            sum2 = 0.0;

            for(j=0;j<i;j++){
              sum1 += pw[i][j] * pw[j][k];
              sum2 += pw[k][j] * pw[j][i];
            }

            pw[i][k] = (pw[i][k] - sum1) / pw[i][i];
            pw[k][i] -= sum2;
            sum3 += pw[i][k] * pw[k][i];
            sum4 += pw[k][i] * f[i];
          }
        }

        pw[k][k] -= sum3;
        f[k] = (f[k] - sum4) / pw[k][k];
      }
    }

    //--------------------------------

    for (i=0;i<number_x-1;i++){
      i1 = number_x - i - 2;
      i2 = i1 + 1;
      sum1 = 0.0;

      for(j=i2;j<number_x;j++){
        sum1 += pw[i1][j] * f[j];
      }

      f[i1] -= sum1;
    }

    for(i=0;i<number_x;i++){
      f[i] /= scale[1][i];
    }
}
