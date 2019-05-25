//midpoint.h
#include<math.h>

void cyclotron(int n, double pi, double t, double dt, double m, double q, double E_x, double E_y, double E_z, double B_x, double B_y, double B_z, double x[], double y[], double z[], double v_x[], double v_y[], double v_z[], double p_x[], double p_y[], double p_z[], double gamma[]){

    t = t+dt;

    p_x[n] = p_x[n-1]+q*(E_x+v_y[n-1]*B_z-v_z[n-1]*B_y)*dt;
    p_y[n] = p_y[n-1]+q*(E_y+v_z[n-1]*B_x-v_x[n-1]*B_z)*dt;
    p_z[n] = p_z[n-1]+q*(E_z+v_x[n-1]*B_y-v_y[n-1]*B_x)*dt;
    gamma[n] = sqrt(1+p_x[n]*p_x[n]+p_y[n]*p_y[n]+p_z[n]*p_z[n]);
    v_x[n] = p_x[n]/gamma[n]/m;
    v_y[n] = p_y[n]/gamma[n]/m;
    v_z[n] = p_z[n]/gamma[n]/m;

    x[n] = x[n-1]+dt*(v_x[n]+v_x[n-1])/2;
    y[n] = y[n-1]+dt*(v_y[n]+v_y[n-1])/2;
    z[n] = z[n-1]+dt*(v_z[n]+v_z[n-1])/2;

}
