/*
 integration.c : Function for numerical integration
*/

#include "common.h"

/* ------------- Numerical integration of differential equation ------------ */

void Numerical_integration(){

  static int i,j,nloop,idobl,j1,j2,nt,imin,kq,nq,Flag;
  static double old_step,ysave,dlt,enq1,enq2,enq3,pepsh,fmin,ep,fd;
  static double r,new_step,dtemp,r1,r2,gsum,pr,pr1,pr2,pr3,d;
  static double a[6];
  static double pertst[6][3]={
            {1.0, 2.0, 3.0},
			      {1.0, 4.5, 6.0},
			      {0.5, 7.333, 9.167},
			      {0.1667, 10.42, 12.5},
			      {0.04133, 13.7, 15.98},
			      {0.008267, 17.15, 1.0}
  };

  a[1] = -1.0;

  strncpy(ieflag,"STILLCLR",8);
  old_step = step;
  nloop = 1;

  if (mxflag == 1){

    imat = 1;
    step = initial_step;
    old_step = step;

    Differential_equation();

    for(i=0;i<number_x;i++){
      y[1][i] = df[i] * step;
    }

    for(i=0;i<number_x;i++){
      Differential_equation();

      for (j=0;j<number_x;j++){
        error[j] = df[j];
      }

      ysave = y[0][i];
      dlt = convergence;

      if (dlt < ysave){
        dlt = ysave;
      }

      dlt *= convergence;
      y[0][i] += dlt;

      Differential_equation();

      y[0][i] = ysave;

      for(j=0;j<number_x;j++){
        jacobimat[j][i] = (df[j] - error[j]) / dlt;
      }
    }

    nq = 2;
    if (nq != 1){

      imat = 2;
      nq = 1;
      kq = 2;
      a[0] = -1.0;
      idobl = 2;

      enq1 = 0.5;
      enq2 = 0.25;
      enq3 = 1.0/6.0;

      for(i=0;i<number_x;i++){

        bnd[i] = enq3 * convergence;
        pepsh = pow(convergence,2.0);
        edwn[i] = pepsh;
        e[i] = 4.0 * pepsh;
        eup[i] = 9.0 * pepsh;
      }

      fmin = 0.1E+20;

      for(i=0;i<number_x;i++){

        ep = convergence * ymax[i];
        fd = 0.0;

        for(j=0;j<number_x;j++){
          fd += y[1][j] * jacobimat[i][j];
        }

        fd = fabs(fd);

        if (fd >= 0.1E-20){
          fd = ep / fd;

          if (fd < fmin){
            fmin = fd;
          }
        }
      }

      fmin = 1.9 * fmin / old_step;
      r = sqrt(fmin);
      new_step = r * old_step;

      if (new_step < min_step){
        strncpy(ieflag,"UNCONVEG",8);
        return;
      }

      if (new_step > max_step){
        r = max_step / old_step;
      }

      step = old_step * r;

      for(i=0;i<number_x;i++){
        y[1][i] *= r;
      }

      if (mxflag == 1){
        Differential_equation();
        for(i=0;i<number_x;i++){
          y[1][i] = df[i] * step;
        }

        for(j=0;j<kq;j++){
          for(i=0;i<number_x;i++){
            save[j][i] = y[j][i];
          }
        }
      }
    }
  }else{
  // mxflag != 1 の場合
    for(j=0;j<kq;j++){
      for(i=0;i<number_x;i++){
        save[j][i] = y[j][i];
      }
    }
  }

  while(1){

    for(j=1;j<kq;j++){
      for(j1=j;j1<kq;j1++){
        j2 = kq - j1 + j - 1;

        for (i=0;i<number_x;i++){
          y[j2-1][i] += y[j2][i];
	      }
	    }
    }

    for(i=0;i<number_x;i++){
      save[6][i] = 0.0;
    }

    for(j=0;j<3;j++){
      Differential_equation();

      for(i=0;i<number_x;i++){
        error[i] = y[1][i] - df[i] * step;
      }

      Matrix_inversion(error,a[0]);

      nt = number_x;

      for(i=0;i<number_x;i++){
        y[0][i] += a[0] * error[i];
        y[1][i] -= error[i];
        save[6][i] += error[i];
        dtemp = error[i];

        if (fabs(dtemp) <= (bnd[i]*ymax[i])){
          if (y[0][i] >= 0.0){
            nt--;
          }
        }
      }

      if (nt <= 0){

        Flag = 0;
        if (nloop >= 3){
          idobl = kq + 1;
        }

        idobl--;
        imat = 0;

        if (idobl >= 0){
          if (kq >= 3){
            for(j=2;j<kq;j++){
              for(i=0;i<number_x;i++){
                y[j][i] += a[j] * save[6][i];
              }
            }
          }

          for(i=0;i<number_x;i++){
            save[8][i] = save[6][i];
          }

          for(i=0;i<number_x;i++){
            if (ymax[i] < y[0][i]){
              ymax[i] = y[0][i];
            }
          }

          for(i=0;i<number_x;i++){
            save[7][i] += error[i];
          }

          mxflag = 0;
          return;
        }

        gsum = 0.0;

        for(i=0;i<number_x;i++){
          dtemp = save[1][i];
          gsum += fabs(dtemp);
        }

        gsum /= step;

        if (gsum <= 0.1E-11){
          strncpy(ieflag,"UNCHANGE",8);
          return;
        }

        r2 = pow((step / old_step),(double)kq);
        pr2 = 0.0;

        for(i=0;i<number_x;i++){
          d = pow((save[6][i] / ymax[i]),2.0);
          pr = 1.2 * pow((d / e[i]),enq2);

          if (pr > pr2){
            pr2 = pr;
          }
        }

        if (nq == 1){
          pr1 = 1.0E+20;
          pr3 = 0.0;

          for(i=0;i<number_x;i++){
            d = pow(((save[6][i] - save[8][i] * r2) / ymax[i]),2.0);
            pr = 1.4 * pow((d / eup[i]),enq3);

            if (pr > pr3){
              pr3 = pr;
            }
          }

        }else{

          pr1 = 0.0;

          for(i=0;i<number_x;i++){
            d = pow((y[kq-1][i] / ymax[i]),2.0);
            pr = 1.3 * pow((d / edwn[i]),enq1);

            if (pr > pr1){
              pr1 = pr;
            }
          }

          if (nq < 5){
            pr3 = 0.0;

            for(i=0;i<number_x;i++){
              d = pow(((save[6][i] - save[8][i] * r2) / ymax[i]),2.0);
              pr = 1.4 * pow((d / eup[i]),enq3);

              if (pr > pr3){
                pr3 = pr;
              }
            }
          }else{
            pr3 = 1.0E+20;
          }
        }

        pr = pr1;
        imin = 1;

        if (pr >= pr2){
          pr = pr2;
          imin = 2;
        }

        if (pr >= pr3){
          pr = pr3;
          imin = 3;
        }

        if (pr < 0.1E-06){
          pr = 1.0;
        }

        r = 1.0 / pr;

        if (r <= 1.1){

          idobl = 10;
          if (kq >= 3){
            for(j=2;j<kq;j++){
              for(i=0;i<number_x;i++){
                y[j][i] += a[j] * save[6][i];
              }
            }
          }

          for(i=0;i<number_x;i++){
            save[8][i] = save[6][i];
          }

          for(i=0;i<number_x;i++){
            if (ymax[i] < y[0][i]){
              ymax[i] = y[0][i];
            }
          }

          for(i=0;i<number_x;i++){
            save[7][i] += error[i];
          }

          mxflag = 0;
          return;
        }

        new_step = step * r;

        if (new_step > max_step){
          r = max_step / step;
        }

        step *= r;
        r1 = 1.0;
        imat = 2;

        for (i=0;i<kq;i++){
          for(j=0;j<number_x;j++){
            y[i][j] = save[i][j];
          }
        }

        if (imin == 2){

          idobl = kq;

        }else if (imin == 3){

          nq = kq;
          kq++;

          for(i=0;i<number_x;i++){
            save[kq-1][i] = save[6][i] * a[nq-1] / (double)nq;
            y[kq-1][i] = save[kq-1][i];
          }

        }else {
          kq = nq;
          nq--;
        }

        if (imin != 2){
          switch(nq){
            case 1:
              a[0] = -1.0000;
              break;

            case 2:
              a[0] = -2.0 / 3.0;
              a[2] = -1.0 / 3.0;
              break;

            case 3:
              a[0] = -6.0 / 11.0;
              a[2] = a[0];
              a[3] = -1.0 / 11.0;
              break;

            case 4:
              a[0] = -12.0 / 25.0;
              a[2] = -7.0 / 10.0;
              a[3] = -1.0 / 5.0;
              a[4] = -1.0 / 50.0;
              break;

            case 5:
              a[0] = -120.0 / 274.0;
              a[2] = -225.0 / 274.0;
              a[3] = -85.0 / 274.0;
              a[4] = -15.0 / 274.0;
              a[5] = -1.0 / 274.0;
          }

          kq = nq + 1;
          idobl = kq;
          enq1 = 0.5 / (double)nq;
          enq2 = 0.5 / (double)(nq + 1);
          enq3 = 0.5 / (double)(nq + 2);

          for(i=0;i<number_x;i++){

            pepsh = convergence;
            edwn[i] = pow((pertst[nq-1][0] * pepsh),2.0);
            e[i] = pow((pertst[nq-1][1] * pepsh),2.0);
            eup[i] = pow((pertst[nq-1][2] * pepsh),2.0);
          }
        }

        r = step / old_step;

        for(j=1;j<kq;j++){

          r1 *= r;

          for(i=0;i<number_x;i++){
            y[j][i] *= r1;
          }
        }

        Flag = 1;
      }
      if(Flag == 1){
        break;
      }
    }

    if(Flag == 1){
      Flag = 0;
      continue;
    }

    nloop++;

    for(i=0;i<kq;i++){
      for(j=0;j<number_x;j++){
        y[i][j] = save[i][j];
	    }
    }

    if (nloop != 2){
      imat = 2;
      new_step = step * 0.25;

      if (new_step > min_step){
        step = new_step;
        r = new_step / old_step;
        r1 = 1.0;

        for(i=1;i<kq;i++){

          r1 *= r;

          for(j=0;j<number_x;j++){
            y[i][j] *= r1;
      	  }
        }

        if ((nloop > 3) && (nq != 1)){
          for(i=0;i<number_x;i++){
            Differential_equation();

            for (j=0;j<number_x;j++){
              error[j] = df[j];
            }

            ysave = y[0][i];
            dlt = convergence;

            if (dlt < ysave){
              dlt = ysave;
            }

            dlt *= convergence;
            y[0][i] += dlt;

            Differential_equation();

            y[0][i] = ysave;

            for(j=0;j<number_x;j++){
              jacobimat[j][i] = (df[j] - error[j]) / dlt;
            }
          }

          nq = 2;

          if (nq == 1){
            continue;
          }

          imat = 2;
          nq = 1;
          kq = 2;
          a[0] = -1.0;
          idobl = 2;

          enq1 = 0.5;
          enq2 = 0.25;
          enq3 = 1.0/6.0;

          for(i=0;i<number_x;i++){
            bnd[i] = enq3 * convergence;
            pepsh = pow(convergence,2.0);
            edwn[i] = pepsh;
            e[i] = 4.0 * pepsh;
            eup[i] = 9.0 * pepsh;
          }

          fmin = 0.1E+20;

          for(i=0;i<number_x;i++){
            ep = convergence * ymax[i];
            fd = 0.0;

            for(j=0;j<number_x;j++){
              fd += y[1][j] * jacobimat[i][j];
            }

            fd = fabs(fd);

            if (fd >= 0.1E-20){
              fd = ep / fd;

              if (fd < fmin){
                fmin = fd;
              }
            }
          }

          fmin = 1.9 * fmin / old_step;
          r = sqrt(fmin);
          new_step = r * old_step;

          if (new_step < min_step){
            strncpy(ieflag,"UNCONVEG",8);
            return;
          }

          if (new_step > max_step){
            r = max_step / old_step;
          }

          step = old_step * r;

          for(i=0;i<number_x;i++){
            y[1][i] *= r;
          }

          if (mxflag != 1){
            continue;
          }

          Differential_equation();

          for(i=0;i<number_x;i++){
            y[1][i] = df[i] * step;
          }

          for(j=0;j<kq;j++){
            for(i=0;i<number_x;i++){
              save[j][i] = y[j][i];
            }
          }
          continue;
        }
        continue;
      }

      if (nq == 1){
        strncpy(ieflag,"UNCONVEG",8);
        return;
      }

      if (nq == 1){
        continue;
      }

      imat = 2;
      nq = 1;
      kq = 2;
      a[0] = -1.0;
      idobl = 2;

      enq1 = 0.5;
      enq2 = 0.25;
      enq3 = 1.0/6.0;

      for(i=0;i<number_x;i++){

        bnd[i] = enq3 * convergence;
        pepsh = pow(convergence,2.0);
        edwn[i] = pepsh;
        e[i] = 4.0 * pepsh;
        eup[i] = 9.0 * pepsh;
      }

      fmin = 0.1E+20;

      for(i=0;i<number_x;i++){

        ep = convergence * ymax[i];
        fd = 0.0;

        for(j=0;j<number_x;j++){
          fd += y[1][j] * jacobimat[i][j];
        }

        fd = fabs(fd);

        if (fd >= 0.1E-20){
          fd = ep / fd;

          if (fd < fmin){
            fmin = fd;
          }
        }
      }

      fmin = 1.9 * fmin / old_step;
      r = sqrt(fmin);
      new_step = r * old_step;

      if (new_step < min_step){
        strncpy(ieflag,"UNCONVEG",8);
        return;
      }

      if (new_step > max_step){
        r = max_step / old_step;
      }

      step = old_step * r;

      for(i=0;i<number_x;i++){
        y[1][i] *= r;
      }

      if (mxflag != 1){
        continue;
      }

      Differential_equation();

      for(i=0;i<number_x;i++){
        y[1][i] = df[i] * step;
      }

      for(j=0;j<kq;j++){
        for(i=0;i<number_x;i++){
          save[j][i] = y[j][i];
        }
      }
      continue;
    }

    imat = 1;
    if (mxflag == 0){
      continue;
    }

    imat = 0;
    mxflag = 0;

    continue;

  }
}
