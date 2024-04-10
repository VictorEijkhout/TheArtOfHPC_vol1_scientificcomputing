################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2022
####
#### makefile for IEEE 754 stuff
####
################################################################
################################################################

info ::

info ::
	@echo "make PROGRAM (where PROGRAM=${PROGRAMS})"
PROGRAM = sqrt
CPROGRAMS = sqrt sineseries elimit
XPROGRAMS = bitprint fake
PROGRAMS = ${CPROGRAMS} ${XPROGRAMS}

LANGUAGE = CXX
EXTRA_INCLUDES = -I${TACC_FMTLIB_INC}
EXTRALIBS = -L${TACC_FMTLIB_LIB} -lfmt
include ../../makefiles/Make.compile

N = 32
EXTRA_OPTIONS =
##-DN=${N}

RUNS += run_elimit
.PHONY: run_elimit
run_elimit : elimit
	@./elimit

RUNS += run_bitprint
.PHONY: run_bitprint
run_bitprint : bitprint
	@echo 3.14 \
	| ./bitprint

include ../../makefiles/Make.run

include ../../makefiles/Make.public

include ../../makefiles/Make.clean
clean ::
	@/bin/rm -f ${PROGRAMS}
