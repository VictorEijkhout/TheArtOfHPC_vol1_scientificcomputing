! /****************************************************************
!  ****
!  **** This program source is part of
!  **** Introduction to High-performance Scientific Computing
!  **** by Victor Eijkhout
!  **** copyright Victor Eijkhout 2011-2022
!  ****
!  **** rotate.F90 : rotation program
!  ****
!  ****************************************************************/

Program RotatePerf
  implicit none

  integer,parameter :: nreps = 10000000
  real*8 :: x=.5, y=.5, alpha=1.57
  integer :: tstart,tend,rate
  real :: runtime
  integer :: iteration

  call system_clock(count_rate=rate)
  print *,"clock freq:",rate
  call system_clock(count=tstart)
  do iteration=1,nreps
     call rotate(x,y,alpha)
  end do
  call system_clock(count=tend)
  runtime = real(tend-tstart) / rate
  print *,"Done after",runtime

contains
  subroutine rotate(x,y,alpha)
    implicit none
    real*8,intent(inout) :: x,y
    real*8,intent(in) :: alpha
    ! temporary
    real*8 :: x0,y0

    x0 = x; y0 = y
    x = cos(alpha)*x0 - sin(alpha)*y0
    y = sin(alpha)*x0 + cos(alpha)*y0
    
  end subroutine rotate

End Program RotatePerf
