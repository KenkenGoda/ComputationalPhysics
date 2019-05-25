//v2.c
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "RK4.h"
#include "RK4a.h"

int main(void){
    double GMe,Re,safe1,safe2,err;
    double dt,dtold;
    int i,k,maxstep;

    /*  maximun time-step, time-step (dt [s]) */
    maxstep = 20000;  dt = 1.5;

    /* define arrays */
    double n[4];
    double x[5][maxstep+1],y[5][maxstep+1],vx[5][maxstep+1],vy[5][maxstep+1];
    double xbig[4],xsmall[4];

    FILE *fp1,*fp2,*fp3,*fp4,*fp5;

    /* open an output file */
    fp1 = fopen("v2_1.dat","w");
    fp2 = fopen("v2_2.dat","w");
    fp3 = fopen("v2_3.dat","w");
    fp4 = fopen("v2_4.dat","w");
    fp5 = fopen("v2_5.dat","w");

    /* Earth radius Re=6.378e3 [km] */
    Re = 6378;

    /* gravitational constant g=9.8 [kg/s^2] */
    GMe = 3.98*pow(10,5)/pow(Re,3);

    /* initial position (-1Re,0.0) & velocity */
    for(k=0;k<=4;k++){
        x[k][0] = -1.0;
        y[k][0] = 0.0;
        vx[k][0] = 0.0;
    }
    vy[0][0] = -7.91/Re;
    vy[1][0] = vy[0][0]*1.3;
    vy[2][0] = vy[0][0]*1.35;
    vy[3][0] = vy[0][0]*1.4;
    vy[4][0] = vy[0][0]*pow(2,0.5);

    /* output the initial values */
    i =0;
    fprintf(fp1,"%16.8e %16.8e\n",x[0][0],y[0][0]);
    fprintf(fp2,"%16.8e %16.8e\n",x[1][0],y[1][0]);
    fprintf(fp3,"%16.8e %16.8e\n",x[2][0],y[2][0]);
    fprintf(fp4,"%16.8e %16.8e\n",x[3][0],y[3][0]);
    fprintf(fp5,"%16.8e %16.8e\n",x[4][0],y[4][0]);

    err = pow(10,-6);
    safe1 = 0.9;
    safe2 = 4.0;

    for(k=0;k<=3;k++){
        for(i=0;i<=maxstep;i++){
            printf("%d\n",i+1);
            RK4a(x[k],y[k],vx[k],vy[k],&dt,GMe,err,safe1,safe2,i,maxstep); 
            printf("dt,x: %f %f\n",dt,x[k][i+1]);
            if(i>10 && x[k][i+1]<-0.99)
                break;
        }
        n[k] = i;
    }
        
    for(i=0;i<=n[0];i++){
        /* ouput the updated values */
        fprintf(fp1,"%16.8e %16.8e\n",x[0][i+1],y[0][i+1]);
    }
    
    for(i=0;i<=n[1];i++){
        /* ouput the updated values */
        fprintf(fp2,"%16.8e %16.8e\n",x[1][i+1],y[1][i+1]);
    }

    for(i=0;i<=n[2];i++){
        /* ouput the updated values */
        fprintf(fp3,"%16.8e %16.8e\n",x[2][i+1],y[2][i+1]);
    }

    for(i=0;i<=n[3];i++){
        /* ouput the updated values */
        fprintf(fp4,"%16.8e %16.8e\n",x[3][i+1],y[3][i+1]);
    }

    dt = 15;
    for(i=0;i<=maxstep;i++){
        RK4(x[4],y[4],vx[4],vy[4],dt,GMe,i,maxstep);
        /* ouput the updated values */
        fprintf(fp5,"%16.8e %16.8e\n",x[4][i+1],y[4][i+1]);
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
  
    return 0;
}
