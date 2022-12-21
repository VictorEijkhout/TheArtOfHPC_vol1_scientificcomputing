program VectorScale

  use assert
  implicit none

  integer :: n=20,i
  real(kind=dp),dimension(:),allocatable :: xarray,yarray
  real(kind=dp) :: scale=2.d0

  allocate(xarray(n)); allocate(yarray(n))
  
  !snippet scale
  do i=1,n
     xarray(i) = 1.d0
  end do
  call dscal(n,scale,xarray,1)
  do i=1,n
     if (.not.assert_equal( xarray(i),scale )) print *,"Error in index",i
  end do
  !snippet end

end program VectorScale
