!--------------------------------------------------------------------------
!-- PHYS404/604 (2009)
!-- Program 07: Orbit of Comet (2nd - order Runge-Kutta)
!--------------------------------------------------------------------------
  implicit none

! set time step & maximum timestep (use parameter statement)
  real(kind=8) dt, t , xh, yh, vxh, vyh
  integer maxstep
  parameter (maxstep = 2000, dt = 0.002)

! define other valuables
  real(kind=8)	:: x(0:maxstep),y(0:maxstep)
  real(kind=8)  :: vx(0:maxstep),vy(0:maxstep)
  real(kind=8)  :: r,ax,ay,ek,ep,et,pi,GM
  integer i

! open an output file with IO=10, name: orbit.dat
  open(10,file='orbit_rk2.dat')

! pi = 3.141592....
  pi = atan(1.0)*4.0

! normalized gravitational constant 4*pi**2
  GM = 4*pi**2

! initial position & velocity
  x(0)=1.0; y(0)=0.0; vx(0)=0.0 ; vy(0)=2*pi

  r  = sqrt(x(0)**2+y(0)**2)
  ek = (vx(0)**2+vy(0)**2)/2.0
  ep = -GM/r
  et = ek + ep

! output the initial values
  i=0; t=0
  write(10,'(8e16.8)') t,x(i),y(i),vx(i),vy(i),ek,ep,et

! ****************** main loop (start) ********************
  do i=1,maxstep

! time integration (Runge-Kutta 2nd-order Method)
    call rk2(x,y,vx,vy,dt,GM,i,maxstep)

    ek = (vx(i)**2+vy(i)**2)/2.0
    r = sqrt(x(i)**2+y(i)**2)
    ep = -GM/r
    et = ek + ep

    t = t + dt

! output the updated values
    write(10,'(8e16.8)') t,x(i),y(i),vx(i),vy(i),ek,ep,et
  enddo
! ****************** main loop ( end ) ********************

! close the output file
  close(10)

  stop ; end
