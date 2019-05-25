//linear.c
#include<stdio.h>
#include<math.h>
#include"runge_kutta.h"

int main(void){

    int i,j,k,n,N=1000;
    double pi,t,t_end,dt,m,q,E_x,E_y,E_z,B_x,B_y,B_z;
    double x[N],y[N],z[N],v_x[N],v_y[N],v_z[N],v[N],p_x[N],p_y[N],p_z[N],p[N],gamma[N];
    FILE *fp;

    fp = fopen("linear.dat","w");

    pi = atan(1.0)*4.0;

    t = 0.0;
    t_end = 5*2*pi;
    dt = t_end/N;
    m = 1.0;
    q = -1.0;

    E_x = 1.0;
    E_y = 0.0;
    E_z = 0.0;
    B_x = 0.0;
    B_y = 0.0;
    B_z = 0.0;

    x[0] = 0.0;
    y[0] = 0.0;
    z[0] = 0.0;
    p_x[0] = 0.0;
    p_y[0] = 0.0;
    p_z[0] = 0.0;
    gamma[0] = sqrt(1+p_x[0]*p_x[0]+p_y[0]*p_y[0]+p_z[0]*p_z[0]);
    v_x[0] = p_x[0]/gamma[0]/m;
    v_y[0] = p_y[0]/gamma[0]/m;
    v_z[0] = p_z[0]/gamma[0]/m;

    v[0] = sqrt(v_x[0]*v_x[0]+v_y[0]*v_y[0]+v_z[0]*v_z[0]);
    p[0] = sqrt(p_x[0]*p_x[0]+p_y[0]*p_y[0]+p_z[0]*p_z[0]);

    fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e %16.8e %16.8e\n",t/2/pi,x[0],y[0],z[0],v[0],p[0],gamma[0]);

    for(n=1;n<N-1;n++){
        
        t = t+dt;

        cyclotron(n,pi,dt,m,q,E_x,E_y,E_z,B_x,B_y,B_z,x,y,z,v_x,v_y,v_z,p_x,p_y,p_z,gamma);

        v[n] = sqrt(v_x[n]*v_x[n]+v_y[n]*v_y[n]+v_z[n]*v_z[n]);
        p[n] = sqrt(p_x[n]*p_x[n]+p_y[n]*p_y[n]+p_z[n]*p_z[n]);
        
        fprintf(fp,"%16.8e %16.8e %16.8e %16.8e %16.8e %16.8e %16.8e\n",t/2/pi,x[n],y[n],z[n],v[n],p[n],gamma[n]);

    }

    fclose(fp);

}



