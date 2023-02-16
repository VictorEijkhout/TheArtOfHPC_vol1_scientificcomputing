################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2023
####
#### makefile for fixed-point exercise
####
################################################################
################################################################

info ::
	@echo "The following targets are avaible:"

PROGRAMS = real31
info ::
	@echo "make PROGRAM (from: ${PROGRAMS})"

% : %.c
	${CC} -O1 -o $@ $^

PUBLICEXTS = py c sh
include ../../makefiles/Make.public

info ::
	@echo "make clean"
clean :
	@rm -f *~ *.o ${PROGRAMS}
