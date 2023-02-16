################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
####
#### copyright 2010-2020 Victor Eijkhout
####
#### makefile for linking cross-language
####
################################################################
################################################################

info ::
	@echo

FC = gfortran
CXX = g++

all : subprogram.o mainprogram.o
	${CXX} -o program $^

%.o : %.cxx
	${CXX} -c -o $@ $^

include ../../makefiles/Make.public

include ../../makefiles/Make.clean
clean :: 
	@rm -f ${PROGRAMS}
