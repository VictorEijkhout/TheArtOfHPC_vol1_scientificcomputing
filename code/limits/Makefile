################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
####
#### copyright 2010-2023 Victor Eijkhout
####
#### makefile for numeric limit exploration
####
################################################################
################################################################

info ::
	@echo

PROGRAMS = hexfloat denorm underflow
include ../../makefiles/Make.compile
LANGUAGE = CXX
MODE = seq

# .SECONDEXPANSION:
# ${PROGRAMS} : $$@.o
# 	${LINKER} -o $@ $^

PUBLICEXTS = cxx
include ../../makefiles/Make.public

include ../../makefiles/Make.clean
clean :: 
	@rm -f ${PROGRAMS}
