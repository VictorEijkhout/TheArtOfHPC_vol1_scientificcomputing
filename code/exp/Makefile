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

PROGRAMS = exp1 expfact expinv
include ../../makefiles/Make.compile
LANGUAGE = C
MODE = seq

# .SECONDEXPANSION:
# ${PROGRAMS} : $$@.o
# 	${LINKER} -o $@ $^

RUNS =

RUNS += run_expfact
run_expfact : expfact
	@for n in 3  5 10 12 15 ; do \
	    echo "%%%%%%%%%%%%%" \
	    && echo $$n | ./expfact \
	 ; done

RUNS += run_expinv
run_expinv : expinv
	@for n in 1 3 10 50 ; do \
	    echo "%%%%%%%%%%%%%" \
	    && echo $$n | ./expinv \
	 ; done

include ../../makefiles/Make.run

PUBLICEXTS = c runout
include ../../makefiles/Make.public

include ../../makefiles/Make.clean
clean :: 
	@rm -f ${PROGRAMS}
