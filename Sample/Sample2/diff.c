/*
 diff.c : Function for definition of differential equation
*/

#include "common.h"

#define PI M_PI

/* ------------------ Definition of differential equation ------------------ */

void Differential_equation(){

  int i;

  for( i = 0 ; i < number_x ; i++){
    x[i] = y[0][i];
  }

  df[0] = 1.000000000000000E-00;
  df[1] = k[1]*x[3] + k[4]*x[4] - k[0]*x[1]*x[2];
  df[2] = k[1]*x[3] - k[0]*x[1]*x[2];
  df[3] = k[0]*x[1]*x[2] + k[3]*x[4] - k[1]*x[3] - k[2]*x[3];
  df[4] = k[2]*x[3] - k[3]*x[4] - k[4]*x[4];
  df[5] = k[4]*x[4];
}
