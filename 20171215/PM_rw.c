//PM_rw.c
#include<stdio.h>
#include<math.h>

double random();

int main(void){

    int i,j,n,N,seed,x;
    double mu,sigma2,r,pi;
    FILE *fp;

    n = 100;
    N = 10000;
    seed = 1;

    mu = 0.0;
    sigma2 = 1.0;
    pi = atan(1.0)*4.0;

    fp = fopen("PM_rw.dat","w");

    double count[n*2+1],theory[n*2+1];

    for(j=0;j<=n*2;j++) count[j]=0.0;

    for(i=0;i<N;i++){

        x = 100;

        for(j=0;j<n;j++){

            r = random(&seed);

            if(r<0.5) x=x-1;
            else x=x+1;

        }

        count[x] = count[x]+1.0;

    }

    for(j=0;j<=n*2;j++){
        
        count[j] = count[j]/N*0.5;
        theory[j] = 1/(pow(2*pi*sigma2*n,0.5)*exp(((j-n-mu)*(j-n-mu))/(2*sigma2*n)));
        
        fprintf(fp,"%d %16.8e %16.8e\n",j-n,count[j],theory[j]);

    }

    fclose(fp);

}
