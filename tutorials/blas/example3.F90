program MatrixVector

  use assert
  implicit none

  integer :: m=20,n,i,j
  real(kind=dp) :: alpha,beta
  real(kind=dp),dimension(:),allocatable :: xarray,yarray
  real(kind=dp),dimension(:,:),allocatable :: matrix

  n = 2*m
  allocate(matrix(m,n),xarray(n)); allocate(yarray(m))
  
  !snippet mvp
  do j=1,n
     xarray(j) = 1.d0
     do i=1,m
        matrix(i,j) = 1.d0
     end do
  end do

  alpha = 1.d0; beta = 0.d0
  call dgemv( 'N',M,N, alpha,matrix,M, xarray,1, beta,yarray,1)
  do i=1,m
     if (.not.assert_equal( yarray(i),dble(n) )) &
          print *,"Error in index",i,":",yarray(i)
  end do
  !snippet end
  
end program MatrixVector
