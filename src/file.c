/*
  file.c : Function for file open
*/

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
/* --------------------------- File open function -------------------------- */

void File_open(){

  int count = 0;
  extern FILE *infile;
  extern FILE *outfile;

  while(1){
    printf("\n Input data filename ---> ");
    scanf("%s",filename[0]);

    if ((infile = fopen(filename[0],"r")) == NULL){
      printf("\n Can't open %s !!\n",filename[0]);
      count++;

      if (count == 5){
        printf("\n Exit program!!\n");
        exit(1);
      }
    }else{
      break;
    }
  }

  strcpy(filename[1], "output.csv");
  outfile = fopen(filename[1],"w");
}
