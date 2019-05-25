/* ******************************************************************
!     Computational Physics
!     Program : Partial Differential Equation I
!     Subject: Diffusion Equation
!  ******************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void) {
  int i,n,m,nmax,nout;
  /*(m): grid size, (nmax): number of timestep, (nout): output interval*/
  m = 60;  nmax = 100;  nout = 2; 
  double an0[m+1], an1[m+1], x[m+1];
  double t,tau,tau_a,h,ak,L,pi,sigma,theory;
  FILE *fp;

  /* pi = 3.141592...*/
  pi = atan(1.0)*4.0;

  /* constant parameters */
  L = 1.0;
  h = L/m;
  ak = 1.0;
  tau_a = h*h/ak/2.0;
  tau = tau_a*0.5;    /* tau < tau_a (stablity condition) */

  /* intialization of array */
  for(i=0;i<=m;i++){
    an0[i]=0.0;  an1[i]=0.0;
  }
  an0[m/2]=1/h;   /* 1/h at center */

  printf("tau_a=%16.8e, tau=%16.8e\n",tau_a,tau);

  /* open an output file */
  fp=fopen("t_x_n.dat","w");

  t = 0.0;
  /* output of the initial values */
  for(i=0;i<=m;i++){
    x[i] = h*i;
    fprintf(fp,"%16.8e %16.8e %16.8e\n",t,x[i],an0[i]);
  }
  fprintf(fp,"\n");

  for(n=1;n<=nmax;n++){
    for(i=1;i<m;i++){  /*we don't calculate i=0&m, an0(0)&an0(1)are boundary conditions*/
      /* FTCS (Forward Time Centered Space) scheme */
      an1[i] = an0[i]+tau/(tau_a*2)*(an0[i+1]+an0[i-1]-2*an0[i]);
    }

    t = t + tau;
    
    if(n%nout == 0){
      for(i=0;i<=m;i++){
	fprintf(fp,"%16.8e %16.8e %16.8e\n",t,x[i],an1[i]);
      }
      fprintf(fp,"\n");
    }
    /* update array an0 by new values */
    for(i=0;i<=m;i++){
      an0[i]=an1[i];
    }

  }

  fclose(fp);

  /* open an output file */
  fp=fopen("xn_theory.dat","w");

  /* output of the initial values */
  t = 0.0;
  for(i=0;i<=m;i++){
    theory = h*i;
    fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e\n",t,x[i],an0[i],theory,fabs(an0[i]-theory));
  }
  fprintf(fp,"\n");

  for(n=1;n<=nmax;n++){
    t = t+tau;
    if(n%nout == 0){
      for(i=0;i<=m;i++){
        sigma = sqrt(2.0*t);
        theory = 1.0/(sigma*sqrt(2*pi))*exp(-(x[i]-L/2)*(x[i]-L/2)/(2*sigma*sigma));
        fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e\n",t,x[i],an0[i],theory,fabs(an0[i]-theory));
      }
      fprintf(fp,"\n");
    }
  }

  fclose(fp);
  
  return 0;
}
