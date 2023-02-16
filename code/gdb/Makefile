################################################################
################################################################
####
#### This Makefile is part of the textbook
#### Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2023
####
#### Makefile for debugging examples
####
################################################################
################################################################

info ::
	@echo "make <progname> in: ${APPS}"

APPS = hello root square

MODE = seq
LANGUAGE = C

MAKEFILESDIR = ../..
include ${MAKEFILESDIR}/makefiles/Make.compile
OPTLEVEL = 0

PUBLICEXTS = c
include ../../makefiles/Make.public

include ${MAKEFILESDIR}/makefiles/Make.clean
clean ::
	@rm -f ${APPS}
