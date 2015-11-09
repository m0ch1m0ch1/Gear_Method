/*
 gear.c : Function for Gear's method
*/

#include "common.h"

/* ---------- Initialization of various variable in Gear's method ---------- */

void Gear_initialize(){

  int i, j;

  for(i=0;i<number_x;i++){
    y[0][i] = value_x[i];
    ymax[i] = 0.001;
    save[7][i] = 0.0;

    for(j=0;j<number_x;j++){
      jacobimat[i][j] = 0.0;
    }
  }

  for(i=0;i<number_k;i++){
    k[i] = value_k[i];
  }

  if (initial_step <= 1.0E-21){
    initial_step = 2.0E-05;
    max_step = 4.0E-04;
    min_step = 1.0E-41;
  }

  mxflag = 1;

  next_time = value_x[0] + output_step;
}


/* ------ Numerical solution of differential equation by Gear's method ----- */

void Gear(){

  Gear_initialize();

  while(next_time < (end_time+output_step)){

    Numerical_integration();

    if (strcmp(ieflag,"STILLCLR") == 0){
      if ((strcmp(change,"CHANGE") == 0) &&
        (y[0][0] > change_time[change_count])){
          Change();
      }else if (y[0][0] >= next_time){
        Output_result();
	    }
    }else{
      printf("   You are unlucky !!\n");
      printf("   Calculation stoped.\n");
      printf("===========================================\n");
      exit(1);
    }
  }

  printf("   The number of output data are %d.\n",output_count);
  printf("===========================================\n");
}
