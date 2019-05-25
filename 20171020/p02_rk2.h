//p02_rk2.h
#include <math.h>

void rk2(double x[], double y[], double vx[], double vy[], double tau, double GM, int i, int msize){
    double r, ax, ay, xh, yh, vxh, vyh;
    /* define arrays */ 
    double f1[4],f2[4],f3[4],f4[4];

    /* time integration (Runge-Kutta 2nd-order Method) */
    f1[0] = vx[i];
    f1[1] = vy[i];
    r = sqrt(x[i]*x[i]+y[i]*y[i]);
    ax = -(GM/(r*r*r))*x[i];
    ay = -(GM/(r*r*r))*y[i];
    f1[2]  = ax;
    f1[3]  = ay;

    f2[0] = vx[i]+f1[2]*tau;
    f2[1] = vy[i]+f1[3]*tau;
    xh = x[i]+f1[0]*tau;
    yh = y[i]+f1[1]*tau;
    r = sqrt(xh*xh+yh*yh);
    ax = -(GM/(r*r*r))*xh;
    ay = -(GM/(r*r*r))*yh;
    f2[2]  = ax;
    f2[3]  = ay;

    x[i+1]  = x[i]+tau*(f1[0]+f2[0])/2;
    y[i+1]  = y[i]+tau*(f1[1]+f2[1])/2;
    vx[i+1] = vx[i]+tau*(f1[2]+f2[2])/2;
    vy[i+1] = vy[i]+tau*(f1[3]+f2[3])/2;

}
