/*
 change.c : Function for changed value by force
*/

#include "common.h"

/* ------------------------- Changed value by force ------------------------ */

void Change(){

  int i, tmp;

  for( i = 0 ; i < number_x ; i++){
    value_x[i] = y[0][i];
  }

  tmp = change_count;

  do{
    value_x[change_element[tmp]] = change_value[tmp];
    printf("   Change No.%d, time  : %15.7f\n",change_element[tmp],value_x[0]);
    printf("                 value : %15.7E\n",change_value[tmp]);
    tmp++;
  }while((int) (change_time[tmp] * 1.0E+10) == (int) ( change_time[change_count] * 1.0E+10));

  for(i=0;i<number_x;i++){
    fprintf(outfile,"%E\t",value_x[i]);
  }

  fprintf(outfile,"\n");

  change_count = tmp;
  output_count++;
  next_time += output_step;

  if (change_count == number_change){
    strncpy(change,"NOCHAN",6);
  }

  printf("   Calculation restarted.\n");
  printf("===========================================\n");
  Gear_initialize();
}
