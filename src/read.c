/*
 read.c : Function for read initial data
*/

#include "common.h"

/* --------------------------- Read initial data --------------------------- */

void Read_data(){

  int i;

  // 1行目の読み込み(微分方程式の数の読み込み)
  fscanf(infile,"%d",&number_x);

  // 微分方程式の数の分のメモリ確保
  name_x  = Malloc_char(number_x);
  value_x = Malloc_double(number_x);

  // 反応種の名前/値の確保
  for( i = 0 ; i < number_x ; i++){
    fscanf(infile,"%s%lf",name_x[i],&value_x[i]);
  }

  // 速度定数の数の確保
  fscanf(infile,"%d",&number_k);

  // 速度定数の数の分のメモリ確保
  name_k  = Malloc_char(number_k);
  value_k = Malloc_double(number_k);

  // 速度定数の名前/値の確保
  for( i = 0 ; i < number_k ; i++){
    fscanf(infile,"%s%lf",name_k[i],&value_k[i]);
  }

  // change及びnochangeの文字列を取得
  fscanf(infile,"%s",change);

  // Changeの場合の処理
  if (strcmp(change,"CHANGE") == 0){

    // 変化させる回数の取得
    fscanf(infile,"%d",&number_change);

    // 変化させる時刻の取得
    change_time = Malloc_double(number_change);

    // 変化させる反応種の番号の取得
    change_element = Malloc_int(number_change);

    // 変化させる値の取得
    change_value = Malloc_double(number_change);

    //変化させる回数分の値を確保
    for( i = 0 ; i < number_change ; i++){
	     fscanf(infile,"%lf%d%lf",&change_time[i],&change_element[i],
        &change_value[i]);
	  }
  }

  // 計算条件の取得
  // (刻み幅の初期値/最小値/最大値/収束条件/出力ファイルへの出力刻み幅/終了時刻)
  fscanf(infile,"%lf%lf%lf%lf%lf%lf",&initial_step,&min_step,&max_step,
    &convergence,&output_step,&end_time);
  fclose(infile);

  // Outputファイルの作成
  // テーブルの見出しの作成

  for( i = 0 ; i < number_x ; i++){
    fprintf(outfile,"%12s",name_x[i]);
    if (i != ( number_x - 1 )){
      fprintf(outfile,", ");
    }
  }
  fprintf(outfile,"\n");

  //初期値の出力
  for( i = 0 ; i < number_x ; i++){
    fprintf(outfile,"%E",value_x[i]);
    if (i != ( number_x - 1 )){
      fprintf(outfile,", ");
    }
  }

  fprintf(outfile,"\n");

  output_count++;

  y = Malloc_double2(7,number_x);
  ymax = Malloc_double(number_x);
  k = Malloc_double(number_k);
  save = Malloc_double2(9,number_x);
  jacobimat = Malloc_double2(number_x,number_x);

  pw = Malloc_double2(number_x,number_x);
  scale = Malloc_double2(2,number_x);

  error = Malloc_double(number_x);
  bnd = Malloc_double(number_x);
  edwn = Malloc_double(number_x);
  e = Malloc_double(number_x);
  eup = Malloc_double(number_x);

  ytemp = Malloc_double(number_x);
  df = Malloc_double(number_x);

  x = Malloc_double(number_x);
  z = Malloc_double(number_x);
}
