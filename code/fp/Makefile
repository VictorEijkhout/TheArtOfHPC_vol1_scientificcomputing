################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2023
####
#### makefile for Catelan computation
####
################################################################
################################################################

info ::

info ::
	@echo "make PROGRAM (where PROGRAM=${PROGRAMS})"
PROGRAM = catelan
CPROGRAMS = 
XPROGRAMS = catelan
PROGRAMS = ${CPROGRAMS} ${XPROGRAMS}

LANGUAGE = CXX
include ../../makefiles/Make.compile

include ../../makefiles/Make.run

PUBLICEXTS = py cxx
include ../../makefiles/Make.public

include ../../makefiles/Make.clean
clean ::
	@/bin/rm -f ${PROGRAMS}
