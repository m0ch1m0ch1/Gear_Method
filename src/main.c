/*
 main.c : Function for main
*/

#include <stdio.h>
#include "main.h"

/* ---------------------------------- Main --------------------------------- */

int main(void){

  printf("\n/*\n");
  printf(" * Copyright (C) 2001 - 2015 Kouji Tanaka and Yohei Motomura All rights reserved.\n");
  printf(" *\n");
  printf(" * Numerical solution of differential equation by Gear's method\n");
  printf(" *\n");
  printf(" * Ver. 2.2.0, 2015/11/05\n");
  printf(" */\n");

  File_open();        // file.c
  Read_data();
  Output_condition();
  Time_start();       // time.c
  Gear();             // gear.c
  Time_stop();        // time.c
  Free();             // malloc.c

  return 0;
}
