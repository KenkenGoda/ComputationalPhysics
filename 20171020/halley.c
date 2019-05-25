//halley.c
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "halley.h"

int main(void) {
    double r,ax,ay,ek,ep,et,pi,GM,T,a;
    double dt ,t;
    int i,maxstep;

    /*  maximun time-step, time-step (dt [s]) */
    maxstep = 200000;  dt = 0.001;

    /* define arrays */ 
    double x[maxstep+1],y[maxstep+1],vx[maxstep+1],vy[maxstep+1];

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
    printf("%f\n",a);
    /* initial position (0.0,35AU) & velocity */
    x[0]=35; y[0]=0.0;
    r  = sqrt(x[0]*x[0]+y[0]*y[0]);
    vx[0]= 0.0; vy[0]=pow(GM*(2/r-1/a),0.5);

    ek = (vx[0]*vx[0]+vy[0]*vy[0])/2.0;
    ep = -GM/r;
    et = ek + ep;

    /* output the initial values */
    i=0;  t=0.0;
    fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e  %16.8e  %16.8e  %16.8e\n",t,x[0],y[0],vx[0],vy[0],ek,ep,et);

    for(i=0;i<=maxstep;i++){

        halley(x,y,vx,vy,dt,GM,i,maxstep);

        /* kinetic energy */
        ek = (vx[i+1]*vx[i+1]+vy[i+1]*vy[i+1])/2.0;
        /* gravitational potential */
        r  = sqrt(x[i+1]*x[i+1]+y[i+1]*y[i+1]);
        ep = -GM/r;
        /* total energy */
        et = ek + ep;

        t = t + dt;

        /* ouput the updated values */
        fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e  %16.8e  %16.8e  %16.8e\n",t,x[i+1],y[i+1],vx[i+1],vy[i+1],ek,ep,et);
    }

    fclose(fp);
  
    return 0;
}
