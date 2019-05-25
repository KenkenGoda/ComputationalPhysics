!--------------------------------------------------------------------------
!-- PHYS404/604 (2013)
!-- Program : Orbit of Comet
!--------------------------------------------------------------------------
  implicit none

! set time step & maximum timestep (use parameter statement)
  real(kind=8) dt ,t
  integer maxstep
  parameter (maxstep = 2000, dt = 0.002)

! define other valuables
  real(kind=8)	:: x(0:maxstep),y(0:maxstep)
  real(kind=8)  :: vx(0:maxstep),vy(0:maxstep)
  real(kind=8)  :: r,ax,ay,ek,ep,et,pi,GM
  integer i

! open an output file with IO=10, name: orbit.dat
  open(10,file='orbit_euler.dat')

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
  do i=0,maxstep-1

! update the velocity
    r = sqrt(x(i)**2+y(i)**2)
    ax = -(GM/(r*r*r))*x(i)
    ay = -(GM/(r*r*r))*y(i)
    vx(i+1) = vx(i) + ax*dt
    vy(i+1) = vy(i) + ay*dt

! update the position (Euler)
    x(i+1)  = x(i)  + vx(i)*dt
    y(i+1)  = y(i)  + vy(i)*dt

    r = sqrt(x(i+1)**2+y(i+1)**2)
! kinetic energy
    ek = (vx(i+1)**2+vy(i+1)**2)/2.0
! gravitational potential
    ep = -GM/r
! total energy
    et = ek+ep

    t = t + dt

! output the updated values
    write(10,'(8e16.8)') t,x(i+1),y(i+1),vx(i+1),vy(i+1),ek,ep,et
  enddo
! ****************** main loop ( end ) ********************

! close the output file
  close(10)

  stop ; end
