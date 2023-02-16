Module cfunctions
  interface
     subroutine setelement(x,i,v) bind(c,name="setelement")
       use iso_c_binding,only: c_int,c_double
       real(kind=c_double),dimension(4),intent(inout) :: x
       integer(kind=c_int),intent(in) :: i
       real(kind=c_double),intent(in) :: v
     end subroutine setelement
  end interface
end Module cfunctions

Program CArrayCall
  implicit none

  ! interface
  !    subroutine setelement(x,i,v)
  !      real(8),dimension(4),intent(inout) :: x
  !      integer(4),intent(in) :: i
  !      real(8),intent(in) :: v
  !    end subroutine setelement
  ! end interface


  real*8,dimension(4) :: x
  integer*4 :: i=2
  real*8 :: v=3.14
  call setelement( x, i,v ) 
  print *,"x[i]=",x(i)

end Program CArrayCall
