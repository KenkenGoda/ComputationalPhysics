PROGRAM xtridag
  !     driver for routine tridag
  implicit none
  INTEGER NP
  PARAMETER (NP=20)
  INTEGER k,n,nl,INFO
  REAL(kind=8) diag(NP),superd(NP-1),subd(NP-1),rhs(NP),u(NP)

  n = 3    ! number of matrix
  nl = 1   ! number of line of RHS

  diag(1) = 1.0;    diag(2) = 2.0;  diag(3) = 3.0
  superd(1) = 2.0;  superd(2) = 3.0
  subd(1)   = 2.0;  subd(2)   = 3.0

  rhs(1) = 1.0;     rhs(2) = 2.0;   rhs(3) = 3.0

!     a vector 'u' will be overwritten by subroutine 'dgtsv'
  u=rhs

!     carry out solution: arrays, subd,diag,superd are overwritten
  call dgtsv(n,nl,subd,diag,superd,u,n,INFO)

!     set arrays (diag, superd, subd) again to check the result
  diag(1) = 1.0;   diag(2) = 2.0;  diag(3) = 3.0
  superd(1) = 2.0; superd(2) = 3.0
  subd(1)   = 2.0; subd(2)   = 3.0

  !  output of solution
  write(*,*) 'The solution vector is:'
  write(*,'(1x,6f12.6)') (u(k), k=1,n)

  !  check solution
  write(*,*) '(matrix)*(sol''n vector) should be:'
  write(*,'(1x,6f12.6)') (rhs(k), k=1,n)
  write(*,*) 'Actual result is:'
  do k=1,n
     if (k.eq.1) then
        rhs(k)=diag(1)*u(1) + superd(1)*u(2)
     else if (k.eq.n) then
        rhs(k)=subd(n-1)*u(n-1) + diag(n)*u(n)
     else
        rhs(k)=subd(k-1)*u(k-1) + diag(k)*u(k) + superd(k)*u(k+1)
     endif
  enddo
  write(*,'(1x,6f12.6)') (rhs(k), k=1,n)
END PROGRAM xtridag
