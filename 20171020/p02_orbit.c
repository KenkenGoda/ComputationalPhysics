//p02_orbit.c
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void) {
    double r,ax,ay,ek,ep,et,pi,GM,xa,ya;
    double dt ,t;
    int i,maxstep;

    /*  maximun time-step, time-step (dt [s]) */
    maxstep = 2000;  dt = 0.002;

    /* define arrays */ 
    double x[maxstep+1],y[maxstep+1],vx[maxstep+1],vy[maxstep+1];

    FILE *fp;

    /* open an output file */
    fp=fopen("orbit_leap.dat","w");

    /* pi = 3.141592...*/
    pi = atan(1.0)*4.0;

    /* gravitational constant g=9.8 [kg/s^2] */
    GM = 4*pi*pi;

    /* initial position (0.0,1.0m) & velocity */
    x[0]=1.0; y[0]=0.0; vx[0]= 0.0; vy[0]=2*pi;
    r = sqrt(x[0]*x[0] + y[0]*y[0]);
    ek = (vx[0]*vx[0]+vy[0]*vy[0])/2.0;
    ep = -GM/r;
    et = ek + ep;

    x[0] = x[0] + vx[0]*dt/2.0;
    y[0] = y[0] + vy[0]*dt/2.0;

    /* output the initial values */
    i=0;  t=0.0;
    fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e  %16.8e  %16.8e  %16.8e\n",t,x[0],y[0],vx[0],vy[0],ek,ep,et);

 // x[0] = x[0] + vx[0]*0.5*dt;
 // y[0] = y[0] + vy[0]*0.5*dt;

    for(i=0;i<=maxstep;i++){

        /*find accleration*/
        r = sqrt(x[i]*x[i] + y[i]*y[i]);
        ax = -GM*x[i]/pow(r,3);
        ay = -GM*y[i]/pow(r,3);
 
        /* update the velocity */
        vx[i+1] = vx[i] + dt*ax;
        vy[i+1] = vy[i] + dt*ay;

        /* update the position */
        x[i+1] = x[i] + dt*vx[i+1];
        y[i+1] = y[i] + dt*vy[i+1];

        /* kinetic energy */
        ek = 0.5*(vx[i+1]*vx[i+1] + vy[i+1]*vy[i+1]);
        /* gravitational potential */
        xa= 0.5*(x[i]+x[i+1]);
        ya= 0.5*(y[i]+y[i+1]);
        r=sqrt(xa*xa +ya*ya);

        ep =-GM/r ;
        /* total energy */
        et = ek + ep;

        t = t + dt;

        /* ouput the updated values */
        fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e  %16.8e  %16.8e  %16.8e\n",t,x[i+1],y[i+1],vx[i+1],vy[i+1],ek,ep,et);
    }

    fclose(fp);
  
    return 0;
}
