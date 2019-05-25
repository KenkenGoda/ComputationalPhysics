//runge_kutta.h
#include<math.h>

void cyclotron(int n, double pi, double dt, double m, double q, double E_x, double E_y, double E_z, double B_x, double B_y, double B_z, double x[], double y[], double z[], double v_x[], double v_y[], double v_z[], double p_x[], double p_y[], double p_z[], double gamma[]){

    double vx,vy,vz,ax,ay,az;
    double f1[6],f2[6],f3[6],f4[6];

    f1[0] = v_x[n-1];
    f1[1] = v_y[n-1];
    f1[2] = v_z[n-1];
    f1[3] = q*(E_x+f1[1]*B_z-f1[2]*B_y)/m;
    f1[4] = q*(E_y+f1[2]*B_x-f1[0]*B_z)/m;
    f1[5] = q*(E_z+f1[0]*B_y-f1[1]*B_x)/m;

    f2[0] = v_x[n-1]+f1[3]*dt/2;
    f2[1] = v_y[n-1]+f1[4]*dt/2;
    f2[2] = v_z[n-1]+f1[5]*dt/2;
    f2[3] = q*(E_x+f2[1]*B_z-f2[2]*B_y)/m;
    f2[4] = q*(E_y+f2[2]*B_x-f2[0]*B_z)/m;
    f2[5] = q*(E_z+f2[0]*B_y-f2[1]*B_x)/m;

    f3[0] = v_x[n-1]+f2[3]*dt/2;
    f3[1] = v_y[n-1]+f2[4]*dt/2;
    f3[2] = v_z[n-1]+f2[5]*dt/2;
    f3[3] = q*(E_x+f3[1]*B_z-f3[2]*B_y)/m;
    f3[4] = q*(E_y+f3[2]*B_x-f3[0]*B_z)/m;
    f3[5] = q*(E_z+f3[0]*B_y-f3[1]*B_x)/m;

    f4[0] = v_x[n-1]+f3[3]*dt;
    f4[1] = v_y[n-1]+f3[4]*dt;
    f4[2] = v_z[n-1]+f3[5]*dt;
    f4[3] = q*(E_x+f4[1]*B_z-f4[2]*B_y)/m;
    f4[4] = q*(E_y+f4[2]*B_x-f4[0]*B_z)/m;
    f4[5] = q*(E_z+f4[0]*B_y-f4[1]*B_x)/m;

    vx = (f1[0]+2*f2[0]+2*f3[0]+f4[0])/6;
    vy = (f1[1]+2*f2[1]+2*f3[1]+f4[1])/6;
    vz = (f1[2]+2*f2[2]+2*f3[2]+f4[2])/6;
    ax = (f1[3]+2*f2[3]+2*f3[3]+f4[3])/6;
    ay = (f1[4]+2*f2[4]+2*f3[4]+f4[4])/6;
    az = (f1[5]+2*f2[5]+2*f3[5]+f4[5])/6;

    x[n] = x[n-1]+vx*dt;
    y[n] = y[n-1]+vy*dt;
    z[n] = z[n-1]+vz*dt;
    v_x[n] = v_x[n-1]+ax*dt;
    v_y[n] = v_y[n-1]+ay*dt;
    v_z[n] = v_z[n-1]+az*dt;
    
    p_x[n] = p_x[n-1]+q*(E_x+vy*B_z-vz*B_y)*dt;
    p_y[n] = p_y[n-1]+q*(E_y+vz*B_x-vx*B_z)*dt;
    p_z[n] = p_z[n-1]+q*(E_z+vx*B_y-vy*B_x)*dt;
    gamma[n] = sqrt(1+p_x[n]*p_x[n]+p_y[n]*p_y[n]+p_z[n]*p_z[n]);

}
