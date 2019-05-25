! ******************************************************************
!     Program : Partial Differential Equation II
!     Subject: Diffusion Equation (Schrodinger eq.)  FTCS scheme
!     ******************************************************************
program schrodinger_FTCS
  implicit none

  integer MAXN, MAXnplots
  parameter( MAXN = 200, MAXnplots = 50 )
  integer N, i, j, k, nStep, nout, iStep
  real*8 L, h, h_bar, mass, tau, tau_a, x(0:MAXN), V(0:MAXN)
  real*8 pi, x0, velocity, k0, sigma0, psi2_total
  real*8 Norm_psi, expFactor
  complex*16 iImag, Psi0(0:MAXN), Psi1(0:MAXN)

  pi = atan(1.0d0)*4.0d0
  iImag = ( 0.0, 1.0 )    ! = sqrt(-1)

  !* Initialize parameters (grid spacing, time step, etc.)
  N = 100        ! Number of grid points
  L = 200        ! System extends from -L/2 to L/2
  h = L/N        ! Grid size
  h_bar = 1      ! Planck's constant (natural units)
  mass = 1       ! Particle mass (natural units)
  tau = 0.001    ! time-step
  do i=0,N
     x(i) = h*i - L/2   ! Coordinates  of grid points
  enddo

  Psi0=(0.0d0,0.0d0)
  Psi1=(0.0d0,0.0d0)
  V=0.d0

  ! critical time step for FTCS
  tau_a=h**2/(h_bar/2/mass)/2.0

  open(10,file='t_x_phi_ftcs.dat')
  open(11,file='t_total_psi_ftcs.dat')

  !* Initialize the wavefunction
  psi2_total=0.0d0   ! sum |Psi**2|

  x0 = -50           ! Location of the center of the wavepacket
  velocity = 0.5   ! Average velocity of the packet
  k0 = mass*velocity/h_bar        ! Average wavenumber
  sigma0 = L/20    ! Standard deviation of the wavefunction
  Norm_psi = 1/(sqrt(sigma0*sqrt(pi)))   ! Normalization
  do i=1,N-1
     expFactor = exp(-(x(i)-x0)**2/(2*sigma0**2))
     Psi0(i) = Norm_psi * cos(k0*x(i)) * expFactor &
          + iImag* Norm_psi * sin(k0*x(i)) * expFactor
     psi2_total = psi2_total + abs(Psi0(i))**2*h
  enddo

  !* Initialize loop and plot variables
  nStep = int(1.7*L/(velocity*tau))  ! Particle should circle system
  nout = nStep/Maxnplots             ! Number of plots to record
  write(*,*) 'number of time steps: ',nStep, nout
  write(*,*) 'time step (tau): ',tau,'tau_a: ',tau_a

  open(12,file='x_phi_start_ftcs.dat')
  iStep=0
  do i=0,N   ! Record initial condition
     write(10,'(5e16.8)') iStep*tau,x(i),abs(Psi0(i))**2,real(Psi0(i)),imag(Psi0(i))
     write(12,'(5e16.8)') x(i),abs(Psi0(i))**2,real(Psi0(i)),imag(Psi0(i))
  enddo
  write(10,*) ' '
  close(12)

  write(11,'(5e16.8)') iStep*tau,psi2_total

  !* Loop over desired number of steps (wave circles system once)
  do iStep=1,nStep

     !* Compute new wave function using the FTCS
     do i=1,N-1
        Psi1(i) = Psi0(i) - (iImag*tau/h_bar)*(-(h_bar**2/(2*mass*h**2))*(Psi0(i+1)+Psi0(i-1)-2*Psi0(i))) &
                + (iImag*tau/h_bar)*V(i)*Psi0(i)
     enddo

     ! set boundary
     Psi1(0) = Psi0(0)
     Psi1(N) = Psi0(N)

     Psi0 = Psi1  ! Copy new values into Psi

     ! check sum |Psi**2|
     psi2_total = 0.d00
     do i=0,N
        psi2_total = psi2_total + abs(Psi0(i))**2*h
     enddo
     write(11,'(5e16.8)') iStep*tau,psi2_total

     if(mod(iStep,nout).eq.0) then
        do i=0,N
           write(10,'(5e16.8)') iStep*tau,x(i),abs(Psi0(i))**2,real(Psi0(i)),imag(Psi0(i))
        enddo
        write(10,*) ' '
     endif
  enddo

  open(12,file='x_phi_end_ftcs.dat')
  do i=0,N
     write(12,'(5e16.8)') x(i),abs(Psi0(i))**2,real(Psi0(i)),imag(Psi0(i))
  enddo

  close(10)
  close(11)
  close(12)

  stop
end program schrodinger_FTCS
