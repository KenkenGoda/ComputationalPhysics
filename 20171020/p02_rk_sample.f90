!--------------------------------------------------------------------------
!-- PHYS404/604 (2013)
!-- Program : Sample program of Runge-Kutta scheme
!--------------------------------------------------------------------------
  implicit none
  real(kind=8)	:: tau,f
  integer n,i
  parameter (n = 12)
  real(kind=8)	:: x(0:n),fh
  real(kind=8)	:: x1,x2,x3,x4,f1,f2,f3,f4

!--------------------------------------------------------------------------
! Euler scheme
  open(10,file='euler.dat')
  tau = 0.2
  i=0;  x=0.0  ! clear array x(n)
  x(0)=1.0
  write(10,'(i3,3e16.8)') i,tau*i,x(i)

  do i=1,n
     x(i)=x(i-1) + tau*f(x(i-1))
     write(10,'(i3,3e16.8)') i,tau*i,x(i)
  enddo
  close(10)
!--------------------------------------------------------------------------
! 2nd order Runge-Kutta scheme (Join method)
  open(10,file='rk2.dat')
  tau = 2*0.2
  i=0;  x=0.0  ! clear array x(n)
  x(0)=1.0
  write(10,'(i3,3e16.8)') i,tau*i,x(i)

  do i=1,n/2
     f1 = f(x(i-1))
     x2 = x(i-1)+tau*f1
     f2 = f(x2)
     x(i)=x(i-1) + (tau/2)*(f1+f2)
     write(10,'(i3,3e16.8)') i,tau*i,x(i)
  enddo
  close(10)

!--------------------------------------------------------------------------
! 4th order Runge-Kutta scheme
  
  open(10,file='rk4.dat')
  tau = 4*0.2
  i=0;  x=0.0  ! clear array x(n)
  x(0)=1.0
  write(10,'(i3,3e16.8)') i,tau*i,x(i)

  do i=1,n/4
     f1 = f(x(i-1))
     x2 = x(i-1) + (tau/2)*f1
     f2 = f(x2)
     x3 = x(i-1) + (tau/2)*f2
     f3 = f(x3)
     x4 = x(i-1) + tau*f3
     f4 = f(x4)

     x(i)=x(i-1) + (tau/6)*(f1+2*f2+2*f3+f4)
     write(10,'(i3,3e16.8)') i,tau*i,x(i)
  enddo
  close(10)

  stop ; end

!--------------------------------------------------------------------------
! function f(x) = -x
!--------------------------------------------------------------------------
function f(x)
  implicit none
  real(kind=8)	:: f,x
  f=-x
  return
end function f
