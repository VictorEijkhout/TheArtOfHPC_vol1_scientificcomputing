################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
####
#### copyright 2010-2023 Victor Eijkhout
####
#### makefile for C++ linking
####
################################################################
################################################################

info ::
	@echo

PROGRAMS =
WRONGS = undefined

include ../../makefiles/Make.run
RUNS =
RUNS += run_undefined
run_undefined :
	@make --no-print-directory localclean
	@out=$@.runout \
	 && make --no-print-directory undefined ECHO=1 \
	    || echo >/dev/null 

PHONY: ${RUNS}

LANGUAGE = CXX
include ../../makefiles/Make.compile

include ../../makefiles/Make.public
include ../../makefiles/Make.clean
