# gear-method

## 1. はじめに

    このプログラムは，Gear法(*)と呼ばれる手法を用いて
    高速に微分方程式の数値計算を実施するプログラムである．

    事前に導入が必要なソフト
      ・gcc version 4.9.0 ~
      ・Gnuplot Version 5.0 patchlevel 1 ~

    各ファイルの内容は以下の通りである。

    ./
      README.md           このファイル

    ./src/
      Makefile            Makefile
      change.c            計算中のある時刻に値を強制的に変える部分
      diff.c              計算に用いる微分方程式の記述部分
      file.c              入出力ファイルの open 部分
      gear.c              Gear 法の導入部分
      integration.c       数値積分の計算部分
      main.c              メイン部分
      malloc.c            変数の動的確保および解放部分
      matrix.c            ヤコビアンの逆行列の計算部分
      output.c            画面およびファイル出力部分
      read.c              入力ファイルの読み込み部分
      time.c              時間計測部分
      graph.c             グラフ描写部分

    ./inc/
      main.h              main.c のヘッダファイル
      common.h            main.c 以外のファイルの共通ヘッダファイル

    ./bin/
      sample.in           サンプルの入力ファイル
      gear                実行ファイル

    ./sample/
      case1/
        diff.c            サンプルの計算に用いる微分方程式の記述部分
        sample.in         サンプルの入力ファイル
      case2/
        diff.c            サンプルの計算に用いる微分方程式の記述部分
        sample.in         サンプルの入力ファイル

      (*) Gear, C. W. (1971).
        Numerical Initial Value Problems in Ordinary Differential Equations
        (Prentice-Hall, Inc. Englewood Cliffs, New Jersey)

## 2. 微分方程式の記述法

    次のような酵素反応を解く場合，微分方程式(diff.c)は次のように記述する・

                        k1        k2        k3
                 E + S <===> ES1 <===> ES2 ===> E + P
                        k-1       k-2

      (diff.c の微分方程式部分のみ抜粋)
        df[0] = 1.0;
        df[1] = k[1]*x[3] + k[4]*x[4] - k[0]*x[1]*x[2];
        df[2] = k[1]*x[3] - k[0]*x[1]*x[2];
        df[3] = k[0]*x[1]*x[2] + k[3]*x[4] - k[1]*x[3] - k[2]*x[3];
        df[4] = k[2]*x[3] - k[3]*x[4] - k[4]*x[4];
        df[5] = k[4]*x[4];

    ここで，df[0] は時間変化を表し，df[0] = 1.0 で固定である．
    df[1], df[2], df[3], df[4], df[5] はそれぞれ E, S, ES1, ES2, P
    の濃度変化 (dx/dt) を，x[1], x[2], x[3], x[4], x[5] はそれぞれ
    E, S, ES1, ES2, P の濃度を k[0], k[1], k[2], k[3], [4] は
    それぞれ k1, k-1, k2, k-2, k3 の値を表す．

    次に，フィードバックなどが存在する系を解く際は
    フィードバックの式を C 言語形式で記述すればよい．
    その際、以下の (1), (2) どちらの記述でも構わない．
    (説明に必要な部分のみ記述)

        (1) ベタに記述する場合

            df[2] = k[0]*(1.0-1.0/PI*(atan((x[3]-1.0)/0.1)+PI/2.0))*x[1]

        (2) z を介して記述する場合

            z[0] = k[0]*(1.0-1.0/PI*(atan((x[3]-1.0)/0.1)+PI/2.0))
            df[2] = z[0]*x[1]

    微分方程式を解く系を変えた場合も同様に記述できる．
    C言語形式で記述しているので，各行末に ; (セミコロン) を忘れないこと．

## 3. 入力ファイルの記述法

    2 で示した酵素反応を解く場合，
    入力ファイルは以下のように記述する (sample.in)．

        6                                微分方程式の数 (df[0] も含む)
        TIME             0.0000000E+00   反応種の名前を 15 文字以内で書き，
        E                1.0000000E-06   その後に初期濃度を書く．
        S                1.0000000E-04
        ES1              0.0000000E+00
        ES2              0.0000000E+00
        P                0.0000000E+00
        5                                速度定数の数
        k1               3.0000000E+07   速度定数の名前を 15 文字以内で書き，
        k-1              3.0000000E+02   その後に速度定数値を書く．
        k2               3.0000000E+05
        k-2              3.0000000E+04
        k3               7.2000000E+00
        NOCHAN                           CHANGE か NOCHAN → 注 1
         1.000000000000000E-05           計算刻みの初期値
         1.000000000000000E-12           計算刻みの最小値
         1.000000000000000E-02           計算刻みの最大値
         1.000000000000000E-01           収束条件 → 注 2
         1.000000000000000E+00           出力ファイルへの出力刻み
         20.000000                       最終 (終了) 時刻

    注 1: 計算中のある時刻にある値を強制的に変化させたい場合
          (一定入力 (df[?] = 0.0) の値をある時刻で変える場合等)，
          CHANGE にしてその後に変更事項を記述する．それ以外はNOCHAN．

          CHANGE にした時の変更事項の記述法は以下の通りである．
          (例) 時刻が 5.0 の時、5 番目の反応種の濃度を 5.0 に変更する場合

               CHANGE
               1              変化させる回数
               5.0            変化させる時刻
               5              変化させる反応種の番号 (x[5] なら 5)
               5.0000000E+00  変化させる値

    注 2: この値を大きくすると収束しやすくなる (計算時間が短くて済む) が，
          計算精度は悪くなる．逆に小さくすると収束はしにくい (計算時間は
          長くなる) が計算精度は良くなる．

## 4. 使用法

    解きたい系の微分方程式を記述しそれに対応した入力ファイルを作成する．
    微分方程式のファイルを編集した場合はsrcフォルダでmakeを実行する．

    binフォルダ内のgearを実行すると、

        Input data filename --->

    と出力されるので作成した入力ファイルのファイル名を入力する．
    すると，反応種の名前と初期濃度，速度定数の名前と値，
    計算刻みなどの計算条件を順次出力して計算が開始される．
    CHANGE にした場合，変化させる時刻になったとき，
    変化させた反応種の番号と時刻と値が出力される．
    計算が終了すると計算時間 (CPU time) を出力し終了する．

    もしYou are unluckly !! が出力された場合は，
    Convergence の値を大きくして再度計算し直す．

## 5. 出力ファイルのフォーマット

    [時刻  0 ]  [反応種 1] [反応種 2] ... [反応種 n-1] [反応種 n]
    [時刻  1 ]  [反応種 1] [反応種 2] ... [反応種 n-1] [反応種 n]
        :          :         :              :          :
    [時刻 t-1]  [反応種 1] [反応種 2] ... [反応種 n-1] [反応種 n]
    [時刻  t ]  [反応種 1] [反応種 2] ... [反応種 n-1] [反応種 n]

## 6. おわりに

    バグや改良点などありましたらお知らせ下さい．