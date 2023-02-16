################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
####
#### copyright 2010-2020
####
#### makefile for computer arithmetic examples
####
################################################################
################################################################

.PHONY: info
info ::
	@echo "Available targets:"

info ::
	@echo "make PROGRAM (in ${APPS})"
CPROGRAMS = bits   intc   oddeven   power
EXERCISES = bits.c intc.c oddeven.c power.c bitp.py
APPS = ${CPROGRAMS} ${FPROGRAMS}

LANGUAGE = C
MODE = seq
include ../../makefiles/Make.compile

info ::
	@echo "make run_PROGRAM (in ${RUNS})"
RUNS =
RUNS += run_bits
.PHONY: run_bits
run_bits : bits
	@( \
	   for i in 1 2 3 0 ; do \
	     echo $${i} \
	     ; \
	   done \
	 ) | ./bits 

RUNS += run_power
.PHONY: run_power
run_power : power
	./power

RUNS += run_intc
.PHONY: run_intc
run_intc : intc
	@for i in 0 1 2 3 4 5 -1 -2 ; do \
	  echo $${i} | ./intc \
	  ; \
	done

include ../../makefiles/Make.run

####
#### turn codes into exercises
#### and publish to students
####

.PHONY: exercises
EXERCISEDIR = ../arithmetic_exercises
include ../../Makefile.student
exercises :
	@/bin/rm -rf ${EXERCISEDIR} \
	&& echo "making exercise directory" \
	&& mkdir ${EXERCISEDIR} \
	&& for x in ${EXERCISES} ; do \
	       cat $${x} \
	       | awk '/solution/ { print "YOUR CODE HERE" } \
	              !/solution/ { print } ' \
	       > ${EXERCISEDIR}/$${x} \
	       ; \
	   done \
	&& make student_upload \
	     RECURSFLAG=-r FILE=${EXERCISEDIR} TARGETDIR=assignments_and_solutions

PUBLICEXTS = py c runout
include ../../makefiles/Make.public

####
#### cleaning
####

include ../../makefiles/Make.clean
clean ::
	@/bin/rm -f ${APPS}
