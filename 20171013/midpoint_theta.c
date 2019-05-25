//midpoint_theta.c
#include<stdio.h>
#include<string.h>
#include<math.h>

int main(void){
    double t,dt,r,m,C,v,A,angle,theta,g,v0,pi;
    int i,a,maxstep;
    FILE *fp;

    maxstep = 2000;
    dt = 0.01;

    r = 3.7*0.01;
    m = 0.145;
    pi = atan(1.0)*4.0;
    g = 9.8;
    C = 0.35;
    v = 1.2;
    A = pi*r*r;

    v0 = 50.0;

    double x[maxstep+1],y[maxstep+1],vx[maxstep+1],vy[maxstep+1],ax[maxstep+1],ay[maxstep+1];

    fp = fopen("midpoint_theta.dat","w");

    for(a=0;a<=200;a++){

        angle = 30+a*0.1;
        theta = angle/180.0*pi;

        x[0] = 0.0;
        y[0] = 1.0;
        vx[0] = v0*cos(theta);
        vy[0] = v0*sin(theta);
        ax[0] = -C*v*A*v0*vx[0]/2/m;
        ay[0] = -C*v*A*v0*vy[0]/2/m-g;

        i = 0;
        t = 0.0;
//        fprintf(fp,"#   time    x   y   vx  vy\n");
//        fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e\n",t,x[0],y[0],vx[0],vy[0]);

        while(y[i]>0.0 && i<=maxstep){
            t = t+dt;
            vx[i+1] = vx[i]+dt*ax[i];
            vy[i+1] = vy[i]+dt*ay[i];
            ax[i+1] = -C*v*A*pow(vx[i+1]*vx[i+1]+vy[i+1]*vy[i+1],0.5)*vx[i+1]/2/m;
            ay[i+1] = -C*v*A*pow(vx[i+1]*vx[i+1]+vy[i+1]*vy[i+1],0.5)*vy[i+1]/2/m-g;
            x[i+1] = x[i]+dt*(vx[i]+vx[i+1])/2.0;
            y[i+1] = y[i]+dt*(vy[i]+vy[i+1])/2.0;
//            fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e\n",t,x[i+1],y[i+1],vx[i+1],vy[i+1]);
            i++;
        }

        fprintf(fp,"#   theta   maximum distance\n");
        fprintf(fp,"%16.8e %16.8e\n",angle,x[i]);

    }

//    fprintf(fp,"%16.8e\n",angle)
//    printf("number of time-step : %d\n",i);
//    printf("maximum distance [m]: %f16\n",x[i]);

    fclose(fp);

    return 0;

}


