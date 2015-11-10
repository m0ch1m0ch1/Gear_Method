/*
 malloc.c : Function for allocation and release of memory
*/

#include "common.h"
#define NAME 50

/* --------- Allocation of memory for single dimention int variable -------- */

int *Malloc_int(int number){

  int *tmp;

  if ((tmp = (int *)malloc(sizeof(int)*number)) == NULL){
    printf("\n Can't allocate memory!!\n");
    return(0);
  }else{
    return(tmp);

  }
}

/* ------- Allocation of memory for single dimention double variable ------- */

double *Malloc_double(int number){

  double *tmp;

  if ((tmp = (double *)malloc(sizeof(double)*number)) == NULL){
    printf("\n Can't allocate memory!!\n");
    return(0);
  }else{
    return(tmp);
  }
}

/* -------- Allocation of memory for two dimentions double variable -------- */

double **Malloc_double2(int number1, int number2){

  int i;
  double **tmp;

  if ((tmp = (double **)malloc(sizeof(double *)*number1)) == NULL){
    printf("\n Can't allocate memory!!\n");
    return(0);
  }else{
    for(i=0;i<number1;i++){
	     if ((*(tmp+i) = (double *)malloc(sizeof(double)*number2)) == NULL){
         printf("\n Can't allocate memory!!\n");
         return(0);
       }
    }

    return(tmp);
  }
}

/* --------- Allocation of memory for two dimentions char variable --------- */

char **Malloc_char(int number){

  int i;
  char **tmp;

  if ((tmp = (char **)malloc(sizeof(char *)*number)) == NULL){
    printf("\n Can't allocate memory!!\n");
    return(0);
  }else{
    for(i=0;i<number;i++){
      if ((*(tmp+i) = (char *)malloc(sizeof(char)*NAME)) == NULL){
        printf("\n Can't allocate memory!!\n");
	      return(0);
	    }
    }

    return(tmp);
  }
}

/* ------------------- Release of memory for all variable ------------------ */

void Free(){

  extern FILE *outfile;
  extern FILE *logfile;

  fclose(outfile);

  free(name_x);
  free(value_x);
  free(name_k);
  free(value_k);

  if (strcmp(change,"CHANGE") == 0){
    free(change_time);
    free(change_element);
    free(change_value);
  }

  free(y);
  free(ymax);
  free(k);
  free(save);
  free(jacobimat);
  free(pw);
  free(scale);
  free(error);
  free(bnd);
  free(edwn);
  free(e);
  free(eup);
  free(ytemp);
  free(df);
  free(x);
  free(z);
}
