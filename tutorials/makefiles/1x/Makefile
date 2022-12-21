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
####
################################################################
################################################################

fooprog : foo.o bar.o
	icpc -o fooprog foo.o bar.o
foo.o : foo.cxx
	icpc -c foo.cxx
bar.o : bar.cxx
	icpc -c bar.cxx
clean :
	rm -f *.o fooprog
