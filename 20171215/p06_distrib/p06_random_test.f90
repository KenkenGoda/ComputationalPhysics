!--------------------------------------------------------------------------
!-- Program: test of random number 
!--------------------------------------------------------------------------
  implicit none
  real(kind=8)	:: r,random,count(0:9)
  integer i,j,seed,irand

! initial random seed (non zero)
  seed =1

! clear count array
count=0.0

! open an output file with IO=10, name: err.dat
  open(10,file='rand.dat')
  open(11,file='count.dat')

  do i=0,10000
     r = random(seed)
     write(10,'(i6,e16.8)') i,r
     irand = r*10
     count(irand) = count(irand) + 1
  enddo

  do j=0,9
     write(11,'(2e16.8)') j*0.1,count(j)
  enddo

! close the output file
  close(10)
  close(11)

  stop
end program
