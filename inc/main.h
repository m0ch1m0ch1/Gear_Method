/*
 main.h : Header file for main.c
*/

/* -------------------------- Function declaration ------------------------- */

void File_open();
void Read_data();
void Output_condition();
void Output_result();
void Gear_initialize();
void Gear();
void Numerical_integration();
void Matrix_inversion(double *, double);
void Change();
void Differential_equation();

int *Malloc_int(int);
double *Malloc_double(int);
double **Malloc_double2(int,int);
char **Malloc_char(int);
void Free();

void Time_start();
void Time_stop();

/* -------------------------- Variable declaration ------------------------- */

/* For file.c */
FILE *infile;
FILE *outfile;

/* For read.c */
int number_x;
int number_k;
int number_change;
int *change_element;
int output_count=0;

double *value_x;
double *value_k;
double *change_time;
double *change_value;
double initial_step;
double min_step;
double max_step;
double convergence;
double output_step;
double end_time;

char **name_x;
char **name_k;
char change[10];

/* For output.c */
double *ytemp;

/* For gear.c */
int mxflag;

double **y;
double *ymax;
double **save;
double **jacobimat;
double *k;
double next_time;

/* For integration.c */
int imat;

double step;
double *error;
double *bnd;
double *edwn;
double *e;
double *eup;

char ieflag[10];

/* For matrix.c */
double **scale;
double **pw;

/* For change.c */
int change_count;

/* For diff.c */
double *df;
double *x;
double *z;
