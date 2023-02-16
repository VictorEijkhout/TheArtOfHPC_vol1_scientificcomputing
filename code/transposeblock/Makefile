################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
####
#### copyright 2010-2020 Victor Eijkhout
####
#### makefile for transposeblock
####
################################################################
################################################################

info ::
	@echo "make PROGRAMNAME [OPTLEVEL=0/1/2/3 (default=${OPTLEVEL})]"

PROGRAMS = transregular transblocked
OPTLEVEL = 1
transregular : trans.c regular.c
	${CC} -g -O${OPTLEVEL} -std=gnu99 -o $@ $<
transblocked : trans.c blocked.c
	${CC} -g -O${OPTLEVEL} -std=gnu99 -DBLOCKED -o $@ $<

include ../../makefiles/Make.public
info ::
	@echo "make clean"
.PHONY: clean
include ../../makefiles/Make.clean
clean ::
	@/bin/rm -f ${PROGRAMS}
