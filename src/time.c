/*
  time.c : Fuction for measure time
*/

#include <stdio.h>
#include <time.h>

clock_t start, end;

/* ----------------------- Start of time measurement ----------------------- */

void Time_start(){

  //- 計算開始時間の保存
  start = clock();

}

/* ------------------------ Stop of time measurement ----------------------- */

void Time_stop(){

  int hour, min;
  double sec;

  //- 計算終了時間の保存
  end = clock();

  //- sec を3600で割った値 = hour
  hour = (int)(((end - start)/(double) CLOCKS_PER_SEC)/3600.0);

  //- sec を60で割って、上記のhourに対応する時間を引いた値 = min　
  min  = (int)(((end - start)/(double) CLOCKS_PER_SEC)/60.0) - hour*60;

  //- min及びhourに対応する時間を引いた値 = sec
  sec  = ((end - start)/(double) CLOCKS_PER_SEC) - hour*3600 - min*60;

  printf("   Calculation finished.\n");
  printf("===========================================\n");
  printf("   CPU time = %d:%d:%.2f (hour:min:sec)\n",hour,min,sec);
  printf("===========================================\n");
}
