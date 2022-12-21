# -*- makefile -*-
################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2022
####
#### makefile for Make tutorial in C++
####     two-parameter version of the code
####
################################################################
################################################################

fooprog : foo.o bar.o
	${CXX} -o fooprog foo.o bar.o
foo.o : foo.cxx
	${CXX} -c foo.cxx
bar.o : bar.cxx
	${CXX} -c bar.cxx
clean :
	rm -f *.o fooprog
