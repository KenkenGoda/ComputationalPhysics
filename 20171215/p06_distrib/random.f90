!--------------------------------------------------------------------------
!     Random number generator by the linear congruential method
!--------------------------------------------------------------------------
real(kind=8) function random( ix )
  real(kind=8) a /16807.d0/, c/0.0d0/,x
  real(kind=8)  M /2147483647d0/
  x      = ix
  x      = dmod( a*x+c,M )
  ix     = x
  random   = x/M

  return
end function random
