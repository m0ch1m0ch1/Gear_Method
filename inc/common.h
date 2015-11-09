/*
 common.h : Header file for except main.c
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/* -------------------------- Function declaration ------------------------- */

extern void File_open();
extern void Read_data();
extern void Output_condition();
extern void Output_result();
extern void Gear_initialize();
extern void Gear();
extern void Numerical_integration();
extern void Matrix_inversion(double *, double);
extern void Change();
extern void Differential_equation();

extern int *Malloc_int(int);
extern double *Malloc_double(int);
extern double **Malloc_double2(int,int);
extern char **Malloc_char(int);
extern void Graph();
extern void Free();

extern void Time_start();
extern void Time_stop();

/* -------------------------- Variable declaration ------------------------- */

/* For file.c */
extern FILE *infile;
extern FILE *outfile;
extern char filename[2][50];

/* For read.c */
extern int number_x;
extern int number_k;
extern int number_change;
extern int *change_element;
extern int output_count;

extern double *value_x;
extern double *value_k;
extern double *change_time;
extern double *change_value;
extern double initial_step;
extern double min_step;
extern double max_step;
extern double convergence;
extern double output_step;
extern double end_time;

extern char **name_x;
extern char **name_k;
extern char change[10];

/* For output.c */
extern double *ytemp;

/* For gear.c */
extern int mxflag;

extern double **y;
extern double *ymax;
extern double **save;
extern double **jacobimat;
extern double *k;
extern double next_time;

/* For integration.c */
extern int imat;

extern double step;
extern double *error;
extern double *bnd;
extern double *edwn;
extern double *e;
extern double *eup;

extern char ieflag[10];

/* For matrix.c */
extern double **scale;
extern double **pw;

/* For change.c */
extern int change_count;

/* For diff.c */
extern double *df;
extern double *x;
extern double *z;
