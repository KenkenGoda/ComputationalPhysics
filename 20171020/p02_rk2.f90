!--------------------------------------------------------------------------
!-- PHYS404/604 (2013)
!-- Subroutine: Runge-Kutta 2nd-order scheme for Orbit problem
!--------------------------------------------------------------------------
  subroutine rk2(x, y, vx, vy, tau, GM, i, msize)
    integer i, msize
    real(kind=8) r,ax,ay,GM,tau,xh,yh,vxh,vyh
    real(kind=8) x(0:msize),y(0:msize)
    real(kind=8) vx(0:msize),vy(0:msize)
    real(kind=8) f1(4),f2(4),f3(4),f4(4)

! time integration (Runge-Kutta 2nd-order Method)
    f1(1) = vx(i)
    f1(2) = vy(i)
    r = sqrt(x(i)*x(i)+y(i)*y(i))
    ax = -(GM/(r*r*r))*x(i)
    ay = -(GM/(r*r*r))*y(i)
    f1(3)  = ax
    f1(4)  = ay

    f2(1) = vx(i)+f1(3)*tau
    f2(2) = vy(i)+f1(4)*tau
    xh = x(i)+f1(1)*tau
    yh = y(i)+f1(2)*tau
    r = sqrt(xh*xh+yh*yh)
    ax = -(GM/(r*r*r))*xh
    ay = -(GM/(r*r*r))*yh
    f2(3)  = ax
    f2(4)  = ay

    x(i+1)  = x(i)  + tau*(f1(1)+f2(1))/2;
    y(i+1)  = y(i)  + tau*(f1(2)+f2(2))/2;
    vx(i+1) = vx(i) + tau*(f1(3)+f2(3))/2;
    vy(i+1) = vy(i) + tau*(f1(4)+f2(4))/2;

    return
  end subroutine rk2
