################################################################
####
#### Makefile for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-7
####
#### Makefile for gdb examples, C++ style
####
################################################################

info ::
	@echo "make <progname>"
	@echo "    where progname=${PROGS}"

PROGS = hello root bounds boundcatch
% : %.cxx
	g++ -g -O0 -o $@ $^

info ::
	@echo "make clean"
clean :
	@/bin/rm -rf ${PROGS} *~ *.o *.dSYM
