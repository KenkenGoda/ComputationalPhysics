//step_motion.c
#include<stdio.h>
#include<math.h>

double random();

int main(void){

    int i,k,N,M,seed;
    double r,t,dx,dt,t_end,L,total;
    FILE *fp1,*fp2,*fp3;

    N = 10000;
    L = atan(1.0)*4.0;
    dx = 0.1;
    dt = 0.005;
    t_end = 5.0;
    M = L/dx+1;

    seed = 1;
    
    fp1 = fopen("step_motion_pi_total.dat","w");
    fp2 = fopen("step_motion_pi_0.dat","w");
    fp3 = fopen("step_motion_pi_5.dat","w");
    
    double x[N],wgm[N],n[M];

    t = 0.0;
    total = 0.0;
    
    for(i=0;i<M;i++) n[i]=0.0;

    for(i=0;i<N;i++){
        x[i] = 0.0;
        wgm[i] = 1.0/N;
        total = total+wgm[i];
        k = (x[i]+L*0.5)/dx;
        n[k] = n[k]+wgm[i];
    }
    
    fprintf(fp1,"%16.8e %16.8e\n",t,total);
    for(i=0;i<M;i++) fprintf(fp2,"%16.8e %16.8e\n",i*dx-L*0.5,n[i]);

    for(i=0;i<M;i++) n[i]=0.0;
    
    while(t<t_end){
        
        t = t+dt;
        total = 0;
        
        for(i=0;i<N;i++){
            
            if(wgm[i]!=0.0){

                r = random(&seed);

                if(r<0.5) x[i]=x[i]+dx;
                else x[i]=x[i]-dx;

                if(fabs(x[i])<=L*0.5)
                    wgm[i]=wgm[i]*(1+dt);
                else
                    wgm[i]=0.0;

                if(t>=t_end){
                    k = (x[i]+L*0.5)/dx;
                    n[k]=n[k]+wgm[i];
                }

            }

            total = total+wgm[i];

        }
            
        fprintf(fp1,"%16.8e %16.8e\n",t,total);

    }
    
    for(i=0;i<M;i++) fprintf(fp3,"%16.8e %16.8e\n",i*dx-L*0.5,n[i]);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

}
