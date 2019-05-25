//2D.c
#include<stdio.h>
#include<math.h>
#include"runge_kutta.h"

int main(void){

    int i,j,k,n,N_e=1000,N_p=10000;
    double pi,t_e,t_p,t_end_e,t_end_p,dt_e,dt_p,m_e,m_p,q_e,q_p,E_x,E_y,E_z,B_x,B_y,B_z;
    double x_e[N_e],y_e[N_e],z_e[N_e],v_x_e[N_e],v_y_e[N_e],v_z_e[N_e],p_x_e[N_e],p_y_e[N_e],p_z_e[N_e],gamma_e[N_e];
    double x_p[N_p],y_p[N_p],z_p[N_p],v_x_p[N_p],v_y_p[N_p],v_z_p[N_p],p_x_p[N_p],p_y_p[N_p],p_z_p[N_p],gamma_p[N_p];
    FILE *fp_e,*fp_p;

    fp_e = fopen("2D_e.dat","w");
    fp_p = fopen("2D_p.dat","w");

    pi = atan(1.0)*4.0;

    t_e = 0.0;
    t_p = 0.0;
    t_end_e = 5*2*pi;
    t_end_p = 2000*2*pi;
    dt_e = t_end_e/N_e;
    dt_p = t_end_p/N_p;
    m_e = 1.0;
    m_p = 1840*m_e;
    q_e = -1.0;
    q_p = 1.0;

    E_x = 0.0;
    E_y = 0.0;
    E_z = 0.0;
    B_x = 0.0;
    B_y = 0.0;
    B_z = 1.0;

    x_e[0] = 0.1;
    y_e[0] = 0.0;
    z_e[0] = 0.0;
    p_x_e[0] = 0.0;
    p_y_e[0] = 0.1;
    p_z_e[0] = 0.0;
    gamma_e[0] = sqrt(1+p_x_e[0]*p_x_e[0]+p_y_e[0]*p_y_e[0]+p_z_e[0]*p_z_e[0]);
    v_x_e[0] = p_x_e[0]/gamma_e[0]/m_e;
    v_y_e[0] = p_y_e[0]/gamma_e[0]/m_e;
    v_z_e[0] = p_z_e[0]/gamma_e[0]/m_e;

    x_p[0] = 0.1;
    y_p[0] = 0.0;
    z_p[0] = 0.0;
    p_x_p[0] = 0.0;
    p_y_p[0] = 0.1;
    p_z_p[0] = 0.0;
    gamma_p[0] = sqrt(1+p_x_p[0]*p_x_p[0]+p_y_p[0]*p_y_p[0]+p_z_p[0]*p_z_p[0]);
    v_x_p[0] = p_x_p[0]/gamma_p[0]/m_p;
    v_y_p[0] = p_y_p[0]/gamma_p[0]/m_p;
    v_z_p[0] = p_z_p[0]/gamma_p[0]/m_p;

    fprintf(fp_e,"%16.8e %16.8e %16.8e %16.8e\n",t_e/2/pi,x_e[0],y_e[0],z_e[0]);
    fprintf(fp_p,"%16.8e %16.8e %16.8e %16.8e\n",t_p/2/pi,x_p[0],y_p[0],z_p[0]);

    for(n=1;n<N_e-1;n++){

        t_e = t_e+dt_e;

        cyclotron(n,pi,dt_e,m_e,q_e,E_x,E_y,E_z,B_x,B_y,B_z,x_e,y_e,z_e,v_x_e,v_y_e,v_z_e,p_x_e,p_y_e,p_z_e,gamma_e);

        fprintf(fp_e,"%16.8e %16.8e %16.8e %16.8e\n",t_e/2/pi,x_e[n],y_e[n],z_e[n]);

    }

    for(n=1;n<N_p-1;n++){

        t_p = t_p+dt_p;

        cyclotron(n,pi,dt_p,m_p,q_p,E_x,E_y,E_z,B_x,B_y,B_z,x_p,y_p,z_p,v_x_p,v_y_p,v_z_p,p_x_p,p_y_p,p_z_p,gamma_p);

        fprintf(fp_p,"%16.8e %16.8e %16.8e %16.8e\n",t_p/2/pi,x_p[n],y_p[n],z_p[n]);

    }

    fclose(fp_e);
    fclose(fp_p);

}



