
#include "common.h"

void Graph(){

  FILE *gp;
  int i;

  fclose(outfile);

  gp = popen("gnuplot", "w");
  if ( gp == NULL ){
    return;
  }

  fprintf(gp, "set term png\n");
  fprintf(gp, "set datafile separator \",\"\n");

  fprintf(gp, "set output \"./DataAll.png\"\n");

  fprintf(gp, "plot");
  for( i = 1 ; i < number_x ; i++){

    fprintf(gp, "\"./output.csv\" using 1:%d title \"%s\" w lp", i+1, name_x[i]);
    if (i != ( number_x - 1 )){
      fprintf(gp,",\\");
    }
    fprintf(gp,"\n");
  }
  fflush(gp);

  for( i = 1 ; i < number_x ; i++){
    fprintf(gp, "set output \"./%s.png\"\n", name_x[i]);
    fprintf(gp, "plot \"./output.csv\" using 1:%d title \"%s\" w l lw 3\n", i+1, name_x[i]);
    fflush(gp);
  }

  pclose(gp);

}
