//theory.c
#include<stdio.h>
#include<string.h>
#include<math.h>

int main(void){
    double t,dt,angle,theta,g,v0,pi;
    int i,maxstep;
    FILE *fp;

    maxstep = 2000;
    dt = 0.1;

    g = 9.8;

    angle = 45.0;
    v0 = 50.0;

    double x[maxstep+1],y[maxstep+1],vx[maxstep+1],vy[maxstep+1];

    fp = fopen("theory.dat","w");

    pi = atan(1.0)*4.0;

    theta = angle/180.0*pi;

    x[0] = 0.0;
    y[0] = 1.0;
    vx[0] = v0*cos(theta);
    vy[0] = v0*sin(theta);

    i = 0;
    t = 0.0;
    fprintf(fp,"#   time    x   y   vx  vy\n");
    fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e\n",t,x[0],y[0],vx[0],vy[0]);

    while(y[i]>0.0 && i<=maxstep){
        t = t+dt;

        x[i+1] = x[0]+v0*cos(theta)*t;
        y[i+1] = y[0]+v0*sin(theta)*t-g*t*t/2;
        vx[i+1] = v0*cos(theta);
        vy[i+1] = v0*cos(theta)-g*t;

        fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e\n",t,x[i+1],y[i+1],vx[i+1],vy[i+1]);
        
        i++;

    }

    printf("number of time-step : %d\n",i);
    printf("maximum distance [m]: %f16\n",x[i]);

    fclose(fp);

    return 0;

}


