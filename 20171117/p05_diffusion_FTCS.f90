! ******************************************************************
!     PHYS404/604
!     Program : Partial Differential Equation
!     Subject: Diffusion Equation
!     ******************************************************************
  implicit none

  integer i,n,m,nmax,nout
! (m): grid size, (nmax): number of timestep, (nout): output interval
  parameter (m=60, nmax=100, nout=2)  
  real*8 an0(0:m),an1(0:m),x(0:m),t,tau,tau_a,h,ak,L,pi,sigma,theory

!  constant (pi)
  pi = atan(1.0d0)*4.0d0

!..   constant parameters
  L=1.0d0
  h = L/m
  ak = 1.0d0
  tau_a=h**2/ak/2.0
  tau = tau_a*0.5    ! tau < tau_a (stablity condition)

!..  intialization of array
  an0=0.0d0
  an1=0.0d0
  an0(m/2)=1/h   ! 1/h at center

  write(*,*) 'tau_a=',tau_a,'tau=',tau
  open(10,file='t_x_n.dat')

  t = 0.0d0
!..   output of the initial values
  do i=0,m
     x(i) = h*i
     write(10,*) t,x(i),an0(i)
  enddo
  write(10,*) ' '

  do n=1,nmax
     do i=1,m-1 ! we don't calculate i=0&m, an0(0)&an0(1)are boundary conditions
!..   FTCS (Forward Time Centered Space) scheme
        an1(i)=an0(i)+tau/(tau_a*2)*(an0(i+1)+an0(i-1)-2*an0(i))
     enddo
     t = t + tau

     if(mod(n,nout).eq.0) then
        do i=0,m
           write(10,'(4e16.8)') t,x(i),an1(i)
        enddo
        write(10,*) ' '
     endif 

!..   update array (an0) by new values (an1)
     an0=an1
  enddo

  open(11,file='xn_theory.dat')
  do i=0,m
     sigma=sqrt(2.0d0*t)
     theory = 1.0d0/(sigma*sqrt(2*pi))*exp(-(x(i)-L/2)**2/(2*sigma**2))
     write(11,'(5e16.8)') t,x(i),an0(i),theory,abs(an0(i)-theory)
  enddo

  close(10)
  close(11)

  stop
end program
