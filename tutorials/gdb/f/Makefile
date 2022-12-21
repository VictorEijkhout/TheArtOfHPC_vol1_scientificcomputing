################################################################
####
#### Makefile for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-7
####
#### Makefile for gdb examples, F90 style
####
################################################################

info ::
	@echo "make <progname>"
	@echo "make clean"

PROGS = say hello square square100

FC = gfortran
% : %.F
	${FC} -g -o $@ $@.F
clean :
	/bin/rm -rf ${PROGS} *~ *.o *.dSYM
