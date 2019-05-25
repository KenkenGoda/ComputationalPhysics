/* program xtridag */

#include<stdio.h>

main(){
  long NP=20,k,n,nl,INFO,i;
  double diag[NP],superd[NP-1],subd[NP-1],rhs[NP],u[NP];

  n = 3, nl=1;

  diag[0]=1.0,   diag[1]=2.0,   diag[2]=3.0;
  superd[0]=2.0, superd[1]=3.0;
  subd[0]=2.0,   subd[1]=3.0;
  rhs[0]=1.0,    rhs[1]=2.0;    rhs[2]=3.0;

  for(i=0;i<NP;i++) u[i]=rhs[i];
	
  dgtsv_(&n,&nl,subd,diag,superd,u,&n,&INFO);
	
  /*set arrays (diag, superd, subd) again to check the result */
  diag[0]=1.0,   diag[1]=2.0,   diag[2]=3.0;
  superd[0]=2.0, superd[1]=3.0;
  subd[0]=2.0,   subd[1]=3.0;

  /*output solution*/
  printf("The solution vector is\n");
  for(i=0;i<n;i++)  printf("%lf ",u[i]);
  printf("\n");

  /*check solution*/
  printf("(matrix)*(sol'n vector) should be:\n",NP);
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

  printf("Actual result is:\n",NP);  
  for(i=0;i<n;i++)  printf("%lf ",rhs[i]);
  printf("\n");
	
}
