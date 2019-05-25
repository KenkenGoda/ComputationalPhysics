//Crank.c

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <complex.h>

/* Main Program */
int main()
{
  int MAXN = 200, MAXnplots = 50;
  long nl = 1, INFO;
  int N, i, j, k, nStep, nout, iStep;
  /* Note:  'i', as defined above, is an index.
            'I', which is used below, is sqrt(-1)
  */
  double L, h, h_bar, mass, tau, tau_a;
  double x[MAXN], V[MAXN];
  double pi, x0, velocity, k0, sigma0, psi2_total;
  double Norm_psi, expFactor;
  double complex Psi0[MAXN], Psi1[MAXN], alpha, diag[MAXN], superd[MAXN], subd[MAXN];
  FILE *fp1, *fp2, *fp3;

  pi = atan(1.0) * 4.0;

  // Initialize parameters (grid spacing, time step, etc.)
  N = 100;        // Number of grid points
  L = 200;        // System extends from -L/2 to L/2
  h = L/N;        // Grid size
  h_bar = 1;      // Planck's constant (natural units)
  mass = 1;       // Particle mass (natural units)
  tau = 0.01;    // time-step
  // critical time step for FTCS
  tau_a = (h*h) / ((h_bar / (2*mass)) * 2.0);

  alpha = (I*tau*h_bar)/(2*mass*h*h);

  for (i=0; i<=N; i++) {
    x[i] = h*i - L/2;   // Coordinates  of grid points
    Psi0[i] = 0.0 + 0.0*I;
    Psi1[i] = 0.0 + 0.0*I;
    V[i] = 0.0;
  }

  fp1 = fopen("t_x_phi_Crank.dat", "w");
  fp2 = fopen("t_total_psi_Crank.dat", "w");

  // Initialize the wavefunction
  psi2_total = 0.0;   // sum |Psi^2|

  x0 = -50;           // Location of the center of the wavepacket
  velocity = 0.5;   // Average velocity of the packet
  k0 = (mass*velocity) / h_bar;        // Average wavenumber
  sigma0 = L/20;    // Standard deviation of the wavefunction
  Norm_psi = 1 / ( sqrt(sigma0*sqrt(pi)) );   // Normalization
  for (i=0; i<=N; i++) {
     expFactor = exp(-(x[i]-x0)*(x[i]-x0)/(2*sigma0*sigma0));
     Psi0[i] = Norm_psi * cos(k0*x[i]) * expFactor
               + I * Norm_psi * sin(k0*x[i]) * expFactor;
     psi2_total = psi2_total + pow( cabs(Psi0[i]), 2 ) * h;
  }

  // Initialize loop and plot variables
  nStep = (int) (1.7*L/(velocity*tau));  // Particle should circle system
  nout = nStep/MAXnplots;                // Number of plots to record
  printf("number of time steps: %d  nout: %d\n", nStep, nout);
  printf("time step (tau): %16.8e  tau_a: %16.8e\n", tau, tau_a);

  fp3 = fopen("x_phi_start_Crank.dat", "w");
  iStep = 0;
  // Record initial condition
  for (i=0; i<=N; i++) {
     fprintf( fp1, "%16.8e  %16.8e  %16.8e  %16.8e  %16.8e\n", iStep*tau, x[i], pow(cabs(Psi0[i]),2), creal(Psi0[i]), cimag(Psi0[i]) );
     fprintf( fp3, "%16.8e  %16.8e  %16.8e  %16.8e\n", x[i], pow(cabs(Psi0[i]),2), creal(Psi0[i]), cimag(Psi0[i]) );
  }
  fprintf(fp1, "\n");
  fclose(fp3);

  fprintf(fp2, "%16.8e  %16.8e\n", iStep*tau, psi2_total);

  // Loop over desired number of steps (wave circles system once)
  for (iStep=1; iStep<=nStep; iStep++) {

    for(i=0;i<=N;i++) diag[i]=2*(1+alpha)+I*(tau/h_bar)*V[i];
    for(i=0;i<=N-1;i++){
      superd[i] = -alpha;
      subd[i] = -alpha;
    }
    for(i=0;i<=N;i++) Psi1[i]=Psi0[i];
    
    zgtsv_(&N,&nl,subd,diag,superd,Psi1,&N,&INFO);
printf("%f\n",cabs(Psi1[10]));

    // set boundary
    Psi1[0] = Psi0[0];
    Psi1[N] = Psi0[N];

    //Copy new values into Psi
    for (i=1; i<N; i++) {
      Psi0[i] = alpha*Psi1[i+1]+2*(1-alpha)*Psi1[i]+alpha*Psi1[i-1]-I*(tau/h_bar)*V[i]*Psi1[i];
    }

    // check sum |Psi**2|
    psi2_total = 0.0;
    for (i=0; i<=N; i++) {
      psi2_total = psi2_total + pow( cabs(Psi0[i]), 2)*h;
    }
    fprintf(fp2, "%16.8e  %16.8e\n", iStep*tau, psi2_total);

    if ( (iStep % nout) == 0 ) {
      for (i=0; i<=N; i++) {
        fprintf( fp1, "%16.8e  %16.8e  %16.8e  %16.8e  %16.8e\n", iStep*tau, x[i], pow(cabs(Psi0[i]),2), creal(Psi0[i]), cimag(Psi0[i]) );
      }
      fprintf(fp1, "\n");
    }
  }

  fp3 = fopen("x_phi_end_Crank.dat", "w");
  for (i=0; i<=N; i++) {
    fprintf( fp3, "%16.8e  %16.8e  %16.8e  %16.8e\n", x[i], pow(cabs(Psi0[i]),2), creal(Psi0[i]), cimag(Psi0[i]) );
  }

  fclose(fp1);
  fclose(fp2);
  fclose(fp3);

  return 0;
}
