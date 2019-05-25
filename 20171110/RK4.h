//RK4.h
#include <stdio.h>
#include <math.h>
#ifndef _RK4H_
#define _RK4H_

void RK4(double x[],double y[],double vx[],double vy[],double tau,double GM,int i,int msize){
    double r, ax, ay, xh, yh, vxh, vyh;
    /* define arrays */ 
    double f1[4],f2[4],f3[4],f4[4];

    /* time integration (Runge-Kutta 4th-order Method) */
    f1[0] = vx[i];
    f1[1] = vy[i];
    r = sqrt(x[i]*x[i]+y[i]*y[i]);
    ax = -(GM/(r*r*r))*x[i];
    ay = -(GM/(r*r*r))*y[i];
    f1[2]  = ax;
    f1[3]  = ay;

    f2[0] = vx[i]+f1[2]*tau/2;
    f2[1] = vy[i]+f1[3]*tau/2;
    xh = x[i]+f1[0]*tau/2;
    yh = y[i]+f1[1]*tau/2;
    r = sqrt(xh*xh+yh*yh);
    ax = -(GM/(r*r*r))*xh;
    ay = -(GM/(r*r*r))*yh;
    f2[2]  = ax;
    f2[3]  = ay;

    f3[0] = vx[i]+f2[2]*tau/2;
    f3[1] = vy[i]+f2[3]*tau/2;
    xh = x[i]+f2[0]*tau/2;
    yh = y[i]+f2[1]*tau/2;
    r = sqrt(xh*xh+yh*yh);
    ax = -(GM/(r*r*r))*xh;
    ay = -(GM/(r*r*r))*yh;
    f3[2]  = ax;
    f3[3]  = ay;

    f4[0] = vx[i]+f3[2]*tau;
    f4[1] = vy[i]+f3[3]*tau;
    xh = x[i]+f3[0]*tau;
    yh = y[i]+f3[1]*tau;
    r = sqrt(xh*xh+yh*yh);
    ax = -(GM/(r*r*r))*xh;
    ay = -(GM/(r*r*r))*yh;
    f4[2]  = ax;
    f4[3]  = ay;

    x[i+1]  = x[i]+tau*(f1[0]+2*f2[0]+2*f3[0]+f4[0])/6;
    y[i+1]  = y[i]+tau*(f1[1]+2*f2[1]+2*f3[1]+f4[1])/6;
    vx[i+1] = vx[i]+tau*(f1[2]+2*f2[2]+2*f3[2]+f4[2])/6;
    vy[i+1] = vy[i]+tau*(f1[3]+2*f2[3]+2*f3[3]+f4[3])/6;

}

#endif
