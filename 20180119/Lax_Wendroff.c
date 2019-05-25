/*--------------------------------------------------------------------------
!-- Program : Advection (wave) equation by LAX_Wendroff scheme
!--------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void) {
    int i,n,mx,nmax,nout,nn,m=201;
    double f0[m],f1[m];
    double cdt,dx,t,x,pi,dts,c,dt;
    FILE *fp;
    char label[30];

    pi = atan(1.0)*4.0;

    /* timestep*/
    c  = 1.0;
    dx = 0.05;
    dt = 0.075;
    cdt = c*dt;

    /* calculate number of timestep required */
    nmax = (m-1)*dx/cdt;
    nout = nmax/20;

    printf("number of timestep   = %d\n",nmax);
    printf("interval of snapshot = %e\n\n",nout*dt);

    mx = 1;

    /* initialization */
    for(i=0;i<m;i++){
        f0[i] = 0.0;
        f1[i] = 0.0;
    }

    t = 0.0;

    for(i=5;i<=55;i++){
        f0[i] = sin(2*pi*(i-5)/50.0);
    }
    printf("h=%16.8e  c*tau=%16.8e\n",dx,cdt);

    nn = 0;  /* output counter*/

    sprintf(label,"lax_wendroff_larger_%05d.dat",nn);
    fp = fopen(label,"w");
    x = 0.0;
    for(i=0;i<m;i+=mx){
    /* output the initial values */
        fprintf(fp,"%16.8e  %16.8e  %16.8e\n",t,x,f0[i]);
        x = x + dx;
    }
    fclose(fp);

    for(n=1;n<=nmax;n++){  /* loop for timestep */
        t = t + cdt/c;

        for(i=1;i<m-1;i++){
            f1[i] = f0[i]-cdt/(2.0*dx)*(f0[i+1]-f0[i-1])+cdt*cdt/(2.0*dx*dx)*(f0[i+1]-2*f0[i]+f0[i-1]);
        }

        if(n%nout == 0){  /* loop for grids */
            nn = nn+1;
            sprintf(label,"lax_wendroff_larger_%05d.dat",nn);
            fp = fopen(label,"w");
            x = 0.0;
            for(i=0;i<m;i+=mx){
	        /* output the initial values */
	        fprintf(fp,"%16.8e  %16.8e  %16.8e\n",t,x,f1[i]);
	        x = x + dx;
            }
            fclose(fp);
        }

        /* update array f0 by new values */
        for(i=0;i<m;i++) f0[i]=f1[i];
    }
  
    return 0;
}
