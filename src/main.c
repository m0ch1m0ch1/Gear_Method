/*
  main.c : Function for main
*/

#include <stdio.h>
#include "main.h"

/* ---------------------------------- Main --------------------------------- */

int main(void){

  printf("===========================================\n");

  File_open();        // file.c
  Read_data();
  Output_condition();
  Time_start();       // time.c
  Gear();             // gear.c
  Time_stop();        // time.c
  Graph();            // graph.c
  Free();             // malloc.c

  return 0;
}
