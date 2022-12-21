Program BinaryWrite
  implicit none

  integer :: i
  !!codesnippet fbinwrite
  Open(Unit=13,File="binarydata.out",Form="unformatted")
  do i=0,9
     write(13) i
  end do
  Close(Unit=13)
  !!codesnippet end

end Program BinaryWrite
