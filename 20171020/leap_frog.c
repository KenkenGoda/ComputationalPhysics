//leap_frog.c
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void) {
    double r,ek,ep,et,pi,GM;
    double dt ,t;
    int i,maxstep;

    /*  maximun time-step, time-step (dt [s]) */
    maxstep = 2000;  dt = 0.002;

    /* define arrays */ 
    double x[maxstep+1],y[maxstep+1],vx[maxstep+1],vy[maxstep+1],ax[maxstep+1],ay[maxstep+1];

    FILE *fp;

    /* open an output file */
    fp=fopen("leap_frog.dat","w");

    /* pi = 3.141592...*/
    pi = atan(1.0)*4.0;

    /* gravitational constant g=9.8 [kg/s^2] */
    GM = 4*pi*pi;

    /* initial position (0.0,1.0m) & velocity */
    x[0]=1.0; y[0]=0.0; vx[0]= 0.0; vy[0]=2*pi;
    r = sqrt(x[0]*x[0]+y[0]*y[0]);
    ax[0] = -GM*x[0]/pow(r,3);
    ay[0] = -GM*y[0]/pow(r,3);
    ek = (vx[0]*vx[0]+vy[0]*vy[0])/2.0;
    ep = -GM/r;
    et = ek + ep;

    /* output the initial values */
    t = 0.0;
    fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e %16.8e %16.8e %16.8e %16.8e %16.8e\n",t,x[0],y[0],vx[0],vy[0],ax[0],ay[0],ek,ep,et);

    x[1] = x[0]+dt*vx[0];
    y[1] = y[0]+dt*vy[0];
    r = sqrt(x[1]*x[1] + y[1]*y[1]);
    ax[1] = -GM*x[1]/pow(r,3);
    ay[1] = -GM*y[1]/pow(r,3);
    vx[1] = vx[0]+dt*(ax[1]+ax[0])/2;
    vy[1] = vy[0]+dt*(ay[1]+ay[0])/2;
    ek = (vx[1]*vx[1]+vy[1]*vy[1])/2.0;
    ep = -GM/r;
    et = ek + ep;

    t = t+dt;
    fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e %16.8e %16.8e %16.8e %16.8e %16.8e\n",t,x[1],y[1],vx[1],vy[1],ax[1],ay[1],ek,ep,et);

    for(i=1;i<=maxstep;i++){

        /* update the position */
        x[i+1] = 2*x[i]-x[i-1]+dt*dt*ax[i];
        y[i+1] = 2*y[i]-y[i-1]+dt*dt*ay[i];

        /*find accleration*/
        r = sqrt(x[i+1]*x[i+1]+y[i+1]*y[i+1]);
        ax[i+1] = -GM*x[i+1]/pow(r,3);
        ay[i+1] = -GM*y[i+1]/pow(r,3);
 
        /* update the velocity */
        vx[i+1] = vx[i]+dt*(ax[i+1]+ax[i])/2;
        vy[i+1] = vy[i]+dt*(ay[i+1]+ay[i])/2;

        /* kinetic energy */
        ek = 0.5*(vx[i+1]*vx[i+1]+vy[i+1]*vy[i+1]);

        /* gravitational potential */
        ep = -GM/r ;

        /* total energy */
        et = ek+ep;

        /* ouput the updated values */
        t = t+dt;
        fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e %16.8e %16.8e %16.8e %16.8e %16.8e\n",t,x[i+1],y[i+1],vx[i+1],vy[i+1],ax[i+1],ay[i+1],ek,ep,et);
    }

    fclose(fp);
  
    return 0;
}
