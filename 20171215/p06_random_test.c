//-------------------------------------------------------------------------
//-- PHYS404/604 (2013)
//- Program: test of random number 
//--------------------------------------------------------------------------

#include <stdio.h>
#include <math.h>

double random();

int main(void)
{
  int nc = 10;
  double r,count[nc];
  int i,irand,nrand,seed=1;
  FILE *fp1,*fp2;

  // number of random number
  nrand = 10000;

  // clear count array
  for(i=0;i<nc;i++) count[i]=0.0;

  fp1=fopen("rand.dat","w");
  fp2=fopen("count.dat","w");


  for(i=0;i<=nrand;i++){
    // uniform random number generator [0.0,1.0)
    r = random(&seed);
    fprintf(fp1,"%d  %16.8e\n",i,r);

    // counter (spectrum)
    irand = (int)(r*nc);

    count[irand] = count[irand] + 1;
  }

  for(i=0;i<nc;i++){
    fprintf(fp2,"%16.8e  %16.8e\n",(double)i/nc,count[i]);
  }

  fclose(fp1);
  fclose(fp2);
}
