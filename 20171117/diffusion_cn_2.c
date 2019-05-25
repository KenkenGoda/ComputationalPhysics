/* cranc_2.c */

#include<stdio.h>
#include<math.h>

int main(){
  long NP,k,n=60,nout,nl,INFO,i,j;
  double diag[n],superd[n-1],subd[n-1],rhs[n],u[n];
  double t,ak,h,tau,tau_a,alpha;
  char filename[100];

  t = 0.0;
  NP = 10000;
  nout = 500;
  nl = 1;
  ak = 1.0;
  h = 1.0/NP;
  tau_a = h*h/2/ak;
  tau = tau_a*1.0;
  alpha = tau/2/tau_a;

  FILE *fp;
  fp = fopen("Crank_Nicolson_2.dat","w");

  for(i=0;i<n;i++) rhs[i] = 0.0;

  rhs[0] = 1.0;

  for(i=0;i<n;i++) fprintf(fp,"%16.8e %ld %16.8e\n",t,i,rhs[i]);

  fprintf(fp,"\n");

  for(j=0;j<NP;j++){

    t = t+tau;

    for(i=0;i<n;i++) diag[i]=2*(alpha+1);
  
    for(i=0;i<n-1;i++){
      superd[i] = -alpha;
      subd[i] = -alpha;
    }

    for(i=0;i<n;i++) u[i]=rhs[i];

    dgtsv_(&n,&nl,subd,diag,superd,u,&n,&INFO);

    u[0] = 1.0;
    u[n-1] = u[n-2];

    for(i=1;i<n-1;i++) rhs[i]=alpha*u[i+1]+2*(1-alpha)*u[i]+alpha*u[i-1];

    if(j%nout==0){
      for(i=0;i<n;i++){
        fprintf(fp,"%16.8e %ld %16.8e\n",t,i,rhs[i]);
      }
      fprintf(fp,"\n");
    }

  }

  /*set arrays (diag, superd, subd) again to check the result */
  for(i=0;i<n;i++) diag[i]=2*(alpha+1);

  for(i=0;i<n-1;i++){
      superd[i] = -alpha;
      subd[i] = -alpha;
  }

  /*output solution*/
/*  printf("The solution vector is\n");
  for(i=0;i<n;i++){
    printf("%lf ",u[i]);
    fprintf(fp,"%ld %16.8e\n",i,u[i]);
  }

  printf("\n");
*/
  /*check solution*/
  printf("(matrix)*(sol'n vector) should be:\n");
  for(i=0;i<n;i++)  printf("%lf ",rhs[i]);
  printf("\n");

  for(k=0;k<n;k++){
    if(k==0){
      rhs[k]=diag[0]*u[0] + superd[0]*u[1];
    }
    else if(k==n-1) {
      rhs[k]=subd[n-2]*u[n-2] + diag[n-1]*u[n-1];
    }
    else{
      rhs[k]=subd[k-1]*u[k-1] + diag[k]*u[k] + superd[k]*u[k+1];
    }
  }

  printf("Actual result is:\n");  
  for(i=0;i<n;i++)  printf("%lf ",rhs[i]);
  printf("\n");

  fclose(fp);

}
