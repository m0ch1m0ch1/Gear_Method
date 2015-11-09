/*
 output.c : Function for output initial condition and result data
*/

#include "common.h"

/* ------------------------ Output initial condition ----------------------- */

void Output_condition(){

  int i;

  printf("\n===========================================\n");
  printf("   Initial value of x (reaction species)\n");
  printf("===========================================\n");

  // number_x : 微分方程式の数
  for( i = 0 ; i < number_x ; i++){
    printf("   %-15s ..... %15.7E\n",name_x[i],value_x[i]);
  }

  printf("===========================================\n");
  printf("  Initial value of k (reaction constants)\n");
  printf("===========================================\n");

  // number_k : 速度定数の数
  for( i = 0 ; i < number_k ; i++){
    printf("   %-15s ..... %15.7E\n",name_k[i],value_k[i]);
  }

  printf("===========================================\n");
  printf("     Initial conditions of calculation\n");
  printf("===========================================\n");
  printf("   Initial stepsize :    %15.7E\n",initial_step);
  printf("   Minimum stepsize :    %15.7E\n",min_step);
  printf("   Maximum stepsize :    %15.7E\n",max_step);
  printf("   Convergence      :    %15.7E\n",convergence);
  printf("   Output step      :    %15.2f\n",output_step);
  printf("   Final time       :    %15.2f\n",end_time);
  printf("===========================================\n");
  printf("   Calculation started.\n");
  printf("===========================================\n");
}

/* --------------------------- Output result data -------------------------- */

void Output_result(){

  int i;

  for( i = 0 ; i < number_x ; i++){

    ytemp[i] = y[0][i];

    // 一定値以下の値を0とする
    if ( (i != 0) && (ytemp[i] < 1.0E-50)){
      ytemp[i] = 0.0;
	  }

    fprintf(outfile,"%E\t",ytemp[i]);
  }

  fprintf(outfile,"\n");
  output_count++;

  next_time += output_step;
}
