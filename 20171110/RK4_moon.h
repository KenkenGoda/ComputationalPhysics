//RK4_moon.h
#include <stdio.h>
#include <math.h>
#ifndef _RK4_MOONH_
#define _RK4_MOONH_

void RK4_moon(double x[],double y[],double vx[],double vy[],double tau,double Xm,double GMe,double GMm,int i,int msize){
    double re, rm, ax, ay, xh, yh, vxh, vyh;
    /* define arrays */ 
    double f1[4],f2[4],f3[4],f4[4];

    /* time integration (Runge-Kutta 4th-order Method) */
    f1[0] = vx[i];
    f1[1] = vy[i];
    re = sqrt(x[i]*x[i]+y[i]*y[i]);
    rm = sqrt((x[i]-Xm)*(x[i]-Xm)+y[i]*y[i]);
    ax = -(GMe/(re*re*re))*x[i]-(GMm/(rm*rm*rm))*(x[i]-Xm);
    ay = -(GMe/(re*re*re))*y[i]-(GMm/(rm*rm*rm))*y[i];
    f1[2]  = ax;
    f1[3]  = ay;

    f2[0] = vx[i]+f1[2]*tau/2;
    f2[1] = vy[i]+f1[3]*tau/2;
    xh = x[i]+f1[0]*tau/2;
    yh = y[i]+f1[1]*tau/2;
    re = sqrt(xh*xh+yh*yh);
    rm = sqrt((xh-Xm)*(xh-Xm)+yh*yh);
    ax = -(GMe/(re*re*re))*xh-(GMm/(rm*rm*rm))*(xh-Xm);
    ay = -(GMe/(re*re*re))*yh-(GMm/(rm*rm*rm))*yh;
    f2[2]  = ax;
    f2[3]  = ay;

    f3[0] = vx[i]+f2[2]*tau/2;
    f3[1] = vy[i]+f2[3]*tau/2;
    xh = x[i]+f2[0]*tau/2;
    yh = y[i]+f2[1]*tau/2;
    re = sqrt(xh*xh+yh*yh);
    rm = sqrt((xh-Xm)*(xh-Xm)+yh*yh);
    ax = -(GMe/(re*re*re))*xh-(GMm/(rm*rm*rm))*(xh-Xm);
    ay = -(GMe/(re*re*re))*yh-(GMm/(rm*rm*rm))*yh;
    f3[2]  = ax;
    f3[3]  = ay;

    f4[0] = vx[i]+f3[2]*tau;
    f4[1] = vy[i]+f3[3]*tau;
    xh = x[i]+f3[0]*tau;
    yh = y[i]+f3[1]*tau;
    re = sqrt(xh*xh+yh*yh);
    rm = sqrt((xh-Xm)*(xh-Xm)+yh*yh);
    ax = -(GMe/(re*re*re))*xh-(GMm/(rm*rm*rm))*(xh-Xm);
    ay = -(GMe/(re*re*re))*yh-(GMm/(rm*rm*rm))*yh;
    f4[2]  = ax;
    f4[3]  = ay;

    x[i+1]  = x[i]+tau*(f1[0]+2*f2[0]+2*f3[0]+f4[0])/6;
    y[i+1]  = y[i]+tau*(f1[1]+2*f2[1]+2*f3[1]+f4[1])/6;
    vx[i+1] = vx[i]+tau*(f1[2]+2*f2[2]+2*f3[2]+f4[2])/6;
    vy[i+1] = vy[i]+tau*(f1[3]+2*f2[3]+2*f3[3]+f4[3])/6;

}

#endif
