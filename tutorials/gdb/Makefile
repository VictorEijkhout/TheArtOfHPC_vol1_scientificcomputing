################################################################
####
#### Makefile for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-7
####
#### Makefile for gdb examples
####
################################################################

info ::
	@echo "make clean"

clean :
	@/bin/rm -rf ${PROGS} ${FIXES} *~ *.o *.dSYM
	@for l in c cxx f ; do \
	  echo ".. cleaning in $$l" ; \
	  ( cd $$l ; make clean ) ; \
	done
