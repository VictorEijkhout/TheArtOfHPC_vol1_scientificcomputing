      !!codesnippet gdb-squaref
      Program square
      real squares(1)
      integer i

      do i=1,100
         squares(i) = sqrt(1.*i)
         sum = sum + squares(i)
      end do
      print *,"Sum:",sum

      End
      !!codesnippet 
