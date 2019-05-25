//random_step.c
#include<stdio.h>
#include<math.h>

double random();

int main(void){

    int i,N,seed;
    double r,t,dx,dt,t_end,L,total;
    FILE *fp;

    N = 10000;
    L = 1.5;
    dx = 0.1;
    dt = 0.005;
    t_end = 5.0;

    seed = 1;
    
    fp = fopen("random_step_15_total.dat","w");
    
    double x[N],wgm[N];

    t = 0.0;
    total = 0.0;
    
    for(i=0;i<N;i++){
        x[i] = 0.0;
        wgm[i] = 1.0/N;
        total = total+wgm[i];
    }
    
    fprintf(fp,"%16.8e %16.8e\n",t,total);

    while(t<t_end){
        
        t = t+dt;
        total = 0;
        
        for(i=0;i<N;i++){
            
            if(wgm[i]!=0.0){

                r = random(&seed);

                x[i]=x[i]+(r*0.2-dx);

                if(fabs(x[i])<=L*0.5) wgm[i]=wgm[i]*(1+dt);
                else wgm[i]=0.0;

            }

            total = total+wgm[i];

        }
            
        fprintf(fp,"%16.8e %16.8e\n",t,total);

    }
    
    fclose(fp);

}
