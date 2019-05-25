!--------------------------------------------------------------------------
!-- Program: Monte Calro method (hit-or-miss) for definite integral
!--------------------------------------------------------------------------
  implicit none
  real(kind=8) x,y,yr,yc,pi,random,sum,capi,delta,answer,ratio,area
  integer i,N,iseed,nout

! initial seed for random number
  iseed=1

! number of trial
  N=10000
! output in every 'nout' steps
  nout = 100

  pi=atan(1.0d0)*4.0d0

! target box hight
  yc=1.0d0

! area of integration (x: 0 - pi) & (y: 0 - 1.0)
  area = pi*1.0d0

! correct answer
  answer=2.0d0

  open(10,file='hit-miss.dat')

  sum=0.0d0
  do i=1,N
     x=random(iseed)*pi
     yr=random(iseed)*yc
     y=sin(x)
     if(yr.le.y) then    ! nice hit!!
        sum=sum+1
     endif

! mod(a,p) modulo operation:  computes the remainder of the division of a by p.
     if(mod(i,nout).eq.0) then 
        ratio=sum/i
        capi=area*ratio
        delta=answer-capi
        write(10,'(i8,3e16.8)') i,capi,delta
     endif
  enddo

  ratio=sum/N
  capi=area*ratio

  write(*,*) 'Integral sin(x) dx = ',capi

  stop
end program
