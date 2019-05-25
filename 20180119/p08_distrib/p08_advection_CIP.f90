!--------------------------------------------------------------------------
!-- Program : Advection (wave) equation by CIP (Cubic interpolation)
!--------------------------------------------------------------------------
program main
  implicit none
  integer i,n,m,mx,nmax,isg,iup,nout,nn
  parameter (m=200)
  real(kind=8) f0(0:m),f1(0:m),C,dt,dx,t,x,pi,dts,zz,xx
  real(kind=8) g0(0:m),g1(0:m),fdif,a,b
  character*15 fname

!  constant (pi)
  pi = atan(1.0d0)*4.0d0

!  constant (propagation speed)
  c = 1.0d0

  dx = 0.05d0
  dt = 0.005d0

  nmax=m*dx/(c*dt)
  mx = 1
  nout = nmax/20

!  intialization
  f0=0.0d0;       f1=0.0d0
  g0=0.0d0;       g1=0.0d0
  t = 0.0d0

  do i=5,55
!     f0(i)=sin(2.0d0*pi*(i-5)/50.0d0)
     f0(i)=1.0d0
  enddo

! calculation of g=df/dt for the intiial profile
  do i=1,m-2
     g0(i)=(f0(i+1)-f0(i-1))/(2.0d0*dx)
  enddo

  write(*,*) 'tau_s=',dx/c,'tau=',dt,'nmax=',nmax

  nn=0  ! output counter
  write(fname,'(a,i5.5,a)') 'advec_',nn,'.dat'
  open(10,file=fname)

  x = 0.0d0
! output of the initial values
  do i=0,m,mx
     write(10,*) t,x,f0(i)
     x = x + dx
  enddo
  write(10,*) ' '
  close(10)

  do n=1,nmax
     t = t + dt
     call cip(f0,f1,g0,g1,m,c,dx,dt)

     if(mod(n,nout).eq.0) then
        nn=nn+1
        write(fname,'(a,i5.5,a)') 'advec_',nn,'.dat'
        open(10,file=fname)
        x = 0.0d0
        do i=0,m,mx
           write(10,*) t,x,f1(i)
           x = x + dx
        enddo
        write(10,*) ' '
        close(10)
     endif

  enddo

  stop
end program main
!--------------------------------------------------------------------------
!-- subroutine: Cubic Interpolation scheme for advection equation
! f0: wave amplitude f^n
! f1: wave ampiitude f^(n+1)
! g0: gradient g^n
! g1: gradient g^(n+1)
! m : array size
! c : vecloty
! dx: grid size
! dt: time step
!--------------------------------------------------------------------------
subroutine cip(f0,f1,g0,g1,m,c,dx,dt)
  implicit none
  integer m, isg, iup, i, istart, iend
  real(kind=8) f0(0:m),f1(0:m),g0(0:m),g1(0:m)
  real(kind=8) c, dt, dx, xx, fdif, a, b

  if(c.ge.0.0)then
     istart= 1
     iend  = m
  else
     istart = 0
     iend   = m-1
  endif
  do i=istart,iend
     if(c.ge.0.0)then
        isg   = -1
        iup   = i-1
     else
        isg    = 1
        iup    = i+1
     endif
     xx   = -c*dt
     fdif = (f0(iup)-f0(i))/dx*isg
     a    = (g0(i)+g0(iup)-2.0d0*fdif)/(dx*dx)
     b    = (3.0d0*fdif-2.0d0*g0(i)-g0(iup))/dx*isg
     f1(i)= ((a*xx+b)*xx+g0(i))*xx+f0(i)
     g1(i)= (3.0d0*a*xx+2.0d0*b)*xx+g0(i)
  enddo
!  update array an0 by new values
  f0=f1
  g0=g1

  return
end subroutine cip
