################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
####
#### copyright 2010-2023 Victor Eijkhout
####
#### makefile for fortran issues
####
################################################################
################################################################

info ::
	@echo

FC = gfortran
CXX = g++

PROGRAM = inttypes
PROGRAMS = inttypes

.SECONDEXPANSION:
${PROGRAMS} : $$@.o
	${FC} -o $@ $^

%.o : %.F90
	${FC} -c -g -O2 -std=f2008 \
	    -o $@ $^

PUBLICEXTS = F90
include ../../makefiles/Make.public

include ../../makefiles/Make.clean
clean :: 
	@rm -f ${PROGRAMS}


