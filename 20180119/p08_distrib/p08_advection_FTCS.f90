!--------------------------------------------------------------------------
!-- Program : Advection (wave) equation by FTCS scheme
!--------------------------------------------------------------------------
program main
  implicit none
  integer i,n,m,mx,nmax,nout,nn
  parameter (m=201)
  real(kind=8) f0(0:m-1),f1(0:m-1),cdt,dx,t,x,pi,dts,c,dt
  character*5 label

!  constant (pi)
  pi = atan(1.0d0)*4.0d0

  c   = 1.0d0
  dx  = 0.05d0
  dt  = 0.005d0
  cdt = c*dt

! calcuate number of timestep required
  nmax=(m-1)*dx/(cdt)
  nout=nmax/20
  write(*,*) 'number of timestep   =',nmax
  write(*,*) 'interval of snapshot = ',nout*dt
  write(*,*) ' '
  mx=1

! intialization
  f0=0.0d0;    f1=0.0d0
  t = 0.0d0

  do i=5,55
     f0(i)=sin(2.0d0*pi*(i-5)/50.0d0)
  enddo

  write(*,*) 'h=',dx,'c*tau=',cdt

  nn=0  ! output counter
  call label_gen5(nn,label)
  open(10,file='advec_'//label//'.dat')

  x = 0.0d0
! output of the initial values
  do i=0,m-1,mx
     write(10,*) t,x,f0(i)
     x = x + dx
  enddo
  close(10)

  do n=1,nmax

     t = t + cdt/c
     
     do i=1,m-2
!   FTCS scheme
           f1(i)=f0(i)-cdt/(2.0d0*dx)*(f0(i+1)-f0(i-1))
     enddo

     if(mod(n,nout).eq.0) then
        nn=nn+1
        call label_gen5(nn,label)
        open(10,file='advec_'//label//'.dat')
        x = 0.0d0
        do i=0,m-1,mx
           write(10,*) t,x,f1(i)
           x = x + dx
        enddo
        close(10)
     endif

!  update array f0 by new values
     f0=f1
  enddo

  stop
end program main
!=======================================================================
subroutine label_gen5(nstart,label)
  implicit none
      
  integer nstart
  integer ind(5)
  integer ind1,ind2,count
  character*1 cha(5)
  character*5 label

  do count=1,5
     ind(count)=0
     cha(count)='0'
  enddo

  count=1
  ind1=nstart
1111 ind(count)=mod(ind1,10)
  cha(count)=char(48+ind(count))
  ind2=int(ind1/10)
  ind1=ind2
  count=count+1
  if (ind1.gt.0) goto 1111 
  
  label=cha(5)//cha(4)//cha(3)//cha(2)//cha(1)
  
  return
end subroutine label_gen5
