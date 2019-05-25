//RK4a.h
#include <math.h>
#include "RK4.h"

void RK4a(double x[],double y[],double vx[],double vy[],double* dt,double GM,double err,double safe1,double safe2,int i,int maxstep){

    double eps,errratio,scale,xdiff,ratio,dtold;
    double xbig[4],xsmall[4];
    int k;

    eps = pow(10,-16);

    for(;;){

        RK4(x,y,vx,vy,*dt,GM,i,maxstep);
        xbig[0] = x[i+1];
        xbig[1] = y[i+1];
        xbig[2] = vx[i+1];
        xbig[3] = vy[i+1];

        RK4(x,y,vx,vy,*dt/2,GM,i,maxstep);
        RK4(x,y,vx,vy,*dt/2,GM,i+1,maxstep);
        xsmall[0] = x[i+2];
        xsmall[1] = y[i+2];
        xsmall[2] = vx[i+2];
        xsmall[3] = vy[i+2];

        errratio = 0.0;

        for(k=0;k<=3;k++){
            scale = err*(fabs(xbig[k])+fabs(xsmall[k]))/2;
            xdiff = xsmall[k]-xbig[k];
            ratio = fabs(xdiff)/(scale+eps);
            if (ratio>errratio)
                errratio = ratio;
        }

        dtold = *dt;
        *dt = safe1*dtold*pow(errratio,-0.20);

        if(*dt<dtold/safe2)
            *dt = dtold/safe2;
        else if(*dt>safe2*dtold)
            *dt = safe2*dtold;
        
        if(errratio<1.0){
            x[i+1] = xsmall[0];
            y[i+1] = xsmall[1];
            vx[i+1] = xsmall[2];
            vy[i+1] = xsmall[3];
            break;
        }
    }
}
