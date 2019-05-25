//v1.c
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "RK4.h"
#include "RK4a.h"

int main(void){
    double r,ax,ay,ek,ep,et,pi,GMe,Re,safe1,safe2,err;
    double dt,dtold;
    int i,n,maxstep;

    /*  maximun time-step, time-step (dt [s]) */
    maxstep = 500;  dt = 1.5;

    /* define arrays */ 
    double t[maxstep+1],x[maxstep+1],y[maxstep+1],vx[maxstep+1],vy[maxstep+1],xbig[4],xsmall[4];

    FILE *fp;

    /* open an output file */
    fp=fopen("v1.dat","w");

    /* Earth radius Re=6.378e3 [km] */
    Re = 6378;

    /* gravitational constant g=9.8 [kg/s^2] */
    GMe = 3.98*pow(10,5)/pow(Re,3);

    /* initial position (-1Re,0.0) & velocity */
    x[0] = -1.0; y[0] = 0.0;
    r  = sqrt(x[0]*x[0]+y[0]*y[0]);
    vx[0] = 0.0; vy[0] = -7.91/Re;

    ek = (vx[0]*vx[0]+vy[0]*vy[0])*Re*Re/2.0;
    ep = -GMe/r*Re*Re;
    et = ek + ep;

    /* output the initial values */
    i =0;  t[0]=0.0;
    fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e  %16.8e  %16.8e  %16.8e\n",t[0],x[0],y[0],vx[0],vy[0],ek,ep,et);

    err = pow(10,-6);
    safe1 = 0.9;
    safe2 = 4.0;

    for(i=0;i<=maxstep;i++){
        printf("%d\n",i+1);
        RK4a(x,y,vx,vy,&dt,GMe,err,safe1,safe2,i,maxstep);
        printf("dt,x: %f %f\n",dt,x[i+1]);
        t[i+1] = t[i]+dt;
        if(i>10 && x[i+1]<-0.99)
            break;
    }

    n = i;

    for(i=0;i<=n;i++){
        
        /* kinetic energy */
        ek = (vx[i+1]*vx[i+1]+vy[i+1]*vy[i+1])*Re*Re/2.0;
        /* gravitational potential */
        r  = sqrt(x[i+1]*x[i+1]+y[i+1]*y[i+1]);
        ep = -GMe/r*Re*Re;
        /* total energy */
        et = ek + ep;

        /* ouput the updated values */
        fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e  %16.8e  %16.8e  %16.8e\n",t[i+1],x[i+1],y[i+1],vx[i+1],vy[i+1],ek,ep,et);

    }

    fclose(fp);
  
    return 0;
}
