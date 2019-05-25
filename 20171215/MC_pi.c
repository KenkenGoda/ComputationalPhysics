//MC_pi.c
#include<stdio.h>
#include<math.h>

double random();

int main(void){

    int i,N,seed;
    double x,y,r,count,pi,pi_th;
    FILE *fp;

    seed = 1;
    pi_th = atan(1.0)*4.0;

    fp = fopen("MC_pi.dat","w");

    for(N=10000;N<1000000;N=N+10000){

        count = 0.0;

        for(i=0;i<=N;i++){

            x = random(&seed);
            y = random(&seed);
            r = pow(x*x+y*y,0.5);

            if(r<=1) count = count+1.0;

        }

        pi = count/N*4;

        fprintf(fp,"%d %16.8e %16.8e\n",N,pi,pi_th);

    }
    
    fclose(fp);

    printf("%f\n",pi);

}
