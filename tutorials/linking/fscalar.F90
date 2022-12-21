Program Fscalar
  implicit none
  integer :: i=5
  real*4 :: xfunc,xsubr

  external rootfunc
  real*4 :: rootfunc

  xfunc = rootfunc(i)
  print *,xfunc

  call rootsubr(i,xsubr)
  print *,xsubr
  
end Program Fscalar
