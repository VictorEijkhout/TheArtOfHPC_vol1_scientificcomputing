################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2022
####
#### makefile for load balancing stuff
####
################################################################
################################################################

info ::

info ::
	@echo "make PROGRAM (where PROGRAM=${PROGRAMS})"
PROGRAM = fpn
CPROGRAMS = 
XPROGRAMS = fpn
PROGRAMS = ${CPROGRAMS} ${XPROGRAMS}

LANGUAGE = CXX
include ../../makefiles/Make.compile

include ../../makefiles/Make.run

include ../../makefiles/Make.public

include ../../makefiles/Make.clean
clean ::
	@/bin/rm -f ${PROGRAMS}
