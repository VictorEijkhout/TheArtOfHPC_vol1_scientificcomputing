program VectorScale

  use assert
  implicit none

  integer :: n=20,i
  !snippet scaleinc
  integer :: inc=2
  !snippet end
  real(kind=dp),dimension(:),allocatable :: xarray,yarray
  real(kind=dp) :: scale=2.d0

  allocate(xarray(n)); allocate(yarray(n))
  
  do i=1,n
     xarray(i) = 1.d0
  end do
  !snippet scaleinc
  call dscal(n/inc,scale,xarray,inc)
  do i=1,n
     if (mod(i,inc)==1) then
        if (.not.assert_equal( xarray(i),scale )) print *,"Error in index",i
     else
        if (.not.assert_equal( xarray(i),1.d0 )) print *,"Error in index",i
     end if
  end do
  !snippet end
  
end program VectorScale
