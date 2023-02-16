################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-8
####
#### makefile for prefetch exploration
####
################################################################
################################################################

info ::
	@echo

PROGRAMS = stream
stream : 
	${CC} -O2 -o $@ $^

include ../../makefiles/Make.public

include ../../makefiles/Make.clean
clean ::
	@rm -f ${PROGRAMS}
