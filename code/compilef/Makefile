# -*- makefile -*-
################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2023
####
#### makefile for code/compile in Fortran
####
################################################################
################################################################

info ::

PROGRAMS =  hello rotate
PROGRAM = rotate
LANGUAGE = F
MODE = seq
include ../../makefiles/Make.compile

include ../../makefiles/Make.run

include ../Make.rotate

PUBLICEXTS = F90
include ../../makefiles/Make.public

##
## clean rules
##
include ../../makefiles/Make.clean
clean ::
	@rm -f *.optrpt *.annot

.PHONY: example_clean
info ::
	@echo "make example_clean : remove local binaries"
example_clean ::
	@rm -f ${PROGRAMS} ${LIBS}
clean :: example_clean
	@rm -rf libs
