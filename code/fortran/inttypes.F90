Program inttypes
  use iso_fortran_env
  implicit none

  Integer(kind=Int8) :: i8
  Integer(kind=Int16) :: i16
  Integer(kind=Int32) :: i32
  Integer(kind=Int64) :: i64
  Integer(kind=16) :: i128

  print *,"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
  print *,"Checking on supported types:"
  print *,"number of defined int types:",size(INTEGER_KINDS)
  print *,"these are the supported types:",INTEGER_KINDS
  print *,"Pre-defined types INT8,INT16,INT32,INT64:",&
       INT8,INT16,INT32,INT64
  print *,"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
  print *,"kind Int8 max is",huge(i8)
  print *,"kind Int16 max is",huge(i16)
  print *,"kind Int32 max is",huge(i32)
  print *,"kind Int64 max is",huge(i64)
  print *,"kind KINDS[5]=16 max is",huge(i128)

end Program inttypes
