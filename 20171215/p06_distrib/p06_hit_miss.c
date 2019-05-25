//**************************************************************************
//    Program : Monte Carlo method (hit-or-miss) for definite integral
//**************************************************************************

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <complex.h>

double random( int *seed );

/* Main Program */
int main()
{
  double x,y,yr,yc,pi,sum,capi,delta,answer,ratio,area;
  int i,N,iseed,nout;
  FILE *fp1;

  // initial seed for random number
  iseed = 1;

  // number of trial
  N = 10000;

  // output in every 'nout' steps
  nout = 100;

  pi = atan(1.0) * 4.0;

  // taget box hight
  yc = 1.0;

  // area of integration (x:0-pi) & (y:0-1.0)
  area = pi*1.0;

  // correct answer
  answer = 2.0;

  fp1 = fopen("hit-miss.dat", "w");

  sum = 0.0;
  for (i=1;i<=N;i++){
    x = random(&iseed)*pi;
    yr = random(&iseed)*yc;
    y = sin(x);
    if(yr < y) {
      sum = sum + 1.0;
    }
    if ( (i % nout) == 0 ) {
      ratio = sum/i;
      capi = area*ratio;
      delta = answer - capi;
      fprintf( fp1, "%8d  %16.8e  %16.8e\n", i, capi, fabs(delta));
    }
  }
  ratio = sum/N;
  capi = area*ratio;

  printf("%8d  %16.8e  %16.8e\n", i, capi, fabs(delta)); 

  fclose(fp1);
    
  return 0;
}
