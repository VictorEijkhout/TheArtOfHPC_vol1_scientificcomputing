################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2023
####
#### makefile for C/F interoperability
####
################################################################
################################################################

.PHONY: info
info ::

PROGRAMS = 

PROGRAMS += carray
info ::
	@echo "make carray : standalone C program"

PROGRAMS += carraycall
info ::
	@echo "make carraycall : F program calling C"
carraycall : carraylib.o

include ../../makefiles/Make.compile

PUBLICEXTS = c F90
include ../../makefiles/Make.public

include ../../makefiles/Make.clean
