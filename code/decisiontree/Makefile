################################################################
################################################################
####
#### This makefile is part of the code
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2023
####
#### decision tree codes
####
################################################################
################################################################

.PHONY: info
info ::
	@echo

PROGRAMS = tree

.SECONDEXPANSION:
${PROGRAMS} : $$@.cxx
	${CXX} -o $@ $<

PUBLICEXTS = cxx
include ../../makefiles/Make.public

.PHONY: clean
clean ::
	@/bin/rm -f *~ *.o a.out ${PROGRAMS}
