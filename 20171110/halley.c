//halley.c
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "RK4.h"
#include "RK4a.h"

int main(void){
    double r,ax,ay,ek,ep,et,pi,GM,T,a,safe1,safe2,err,eps,errratio,scale,xdiff,ratio;
    double dt,dtold;
    int i,n,maxstep;

    /*  maximun time-step, time-step (dt [s]) */
    maxstep = 500;  dt = 1.5;

    /* define arrays */ 
    double t[maxstep+1],x[maxstep+1],y[maxstep+1],vx[maxstep+1],vy[maxstep+1],xbig[4],xsmall[4];

    FILE *fp;

    /* open an output file */
    fp=fopen("halley.dat","w");

    /* pi = 3.141592...*/
    pi = atan(1.0)*4.0;

    /* gravitational constant g=9.8 [kg/s^2] */
    GM = 4*pi*pi;

    /* period [yr] */
    T = 76.03;

    /* semimajor axes [AU] */
    a = pow(GM*T*T/4/pi/pi,1.0/3.0);

    /* initial position (35AU,0.0) & velocity */
    x[0]=35; y[0]=0.0;
    r  = sqrt(x[0]*x[0]+y[0]*y[0]);
    vx[0]= 0.0; vy[0]=pow(GM*(2/r-1/a),0.5);

    ek = (vx[0]*vx[0]+vy[0]*vy[0])/2.0;
    ep = -GM/r;
    et = ek + ep;

    /* output the initial values */
    i =0;  t[0]=0.0;
    fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e  %16.8e  %16.8e  %16.8e\n",t[0],x[0],y[0],vx[0],vy[0],ek,ep,et);

    err = pow(10,-6);
    safe1 = 0.9;
    safe2 = 4.0;

    for(i=0;i<=maxstep;i++){
        printf("%d\n",i+1);
        RK4a(x,y,vx,vy,&dt,GM,err,safe1,safe2,i,maxstep);
        printf("dt: %f\n",dt);
        t[i+1] = t[i]+dt;
        if(i>100 && x[i+1]>34.9)
            break;
    }

    n = i;

    for(i=0;i<=n;i++){

//        RK4(x,y,vx,vy,dt,GM,i,maxstep);
        
        /* kinetic energy */
        ek = (vx[i+1]*vx[i+1]+vy[i+1]*vy[i+1])/2.0;
        /* gravitational potential */
        r  = sqrt(x[i+1]*x[i+1]+y[i+1]*y[i+1]);
        ep = -GM/r;
        /* total energy */
        et = ek + ep;

        /* ouput the updated values */
        fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e  %16.8e  %16.8e  %16.8e\n",t[i+1],x[i+1],y[i+1],vx[i+1],vy[i+1],ek,ep,et);

    }

    fclose(fp);
  
    return 0;
}
