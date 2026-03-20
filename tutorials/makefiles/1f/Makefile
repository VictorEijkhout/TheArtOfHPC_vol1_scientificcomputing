# -*- makefile -*-
################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2024
####
#### makefile for Make tutorial in Fortran
####
################################################################
################################################################

fooprog : foomain.o foomod.o
	gfortran -o fooprog foo.o foomod.o
foomain.o : foomain.F
	gfortran -c foomain.F
foomod.o : foomod.F
	gfortran -c foomod.F
clean :
	rm -f *.o fooprog

include ../Make.snippets
