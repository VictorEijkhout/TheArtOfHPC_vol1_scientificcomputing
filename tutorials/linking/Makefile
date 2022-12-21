# -*- makefile -*-
################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-9
####
#### makefile for linking
####
################################################################
################################################################

info ::

CC = clang
CXX = clang++
FC = gfortran
OPTLEVEL = 2
CFLAGS = -O${OPTLEVEL} -std=c99
PROGRAMS = 

info ::
	@echo "make binary, xbinary"
.PHONY: binary xbinary
PROGRAMS += binary_write_c binary_write_f binary_read_c
binary :
	${CC} -o binary_write_c binary_write.c
	./binary_write_c
	hexdump binarydata.out
	${CC} -o binary_read_c binary_read.c
	./binary_read_c
xbinary :
	${FC} -o binary_write_f binary_write.F90
	./binary_write_f
	hexdump binarydata.out

info ::
	@echo "make file"
.PHONY: file
file :
	@for f in {c,f}prog.{c,F} ; do \
	    echo "%%%% $$f %%%%" \
	    && file $$f \
	    ; done

info ::
	@echo "make string"
.PHONY: string
PROGRAMS += string
string :
	${CC} -c cstring.c
	${FC} -c fstring.F90
	${FC} -o $@ fstring.o cstring.o

info ::
	@echo "make scalar"
.PHONY: scalar
PROGRAMS += scalar
scalar :
	${CC} -c scalarfunc.c
	${FC} -c fscalar.F90
	${FC} -o $@ fscalar.o scalarfunc.o

info ::
	@echo "make array"
.PHONY: array
PROGRAMS += array
array :
	${CC} -c carraylib.c
	${FC} -c carraycall.F90
	${FC} -o $@ carraylib.o carraycall.o

info ::
	@echo "make plusplus"
.PHONY: plusplus
PROGRAMS += plusplus
plusplus :
	${CXX} -c plusfunc.cxx
	${CC} -c pluscall.c
	${CC} -o pluscall.o plusfunc.o

.PHONY: ctype
# cp Python-using-C-CPP-libraries-with-ctypes/using_c_libs_from_python/*mylib.{c,h,py} .
ctype :
	${CC} -std=c11 -c -fPIC mylib.c -o mylib.o
	${CC} -shared mylib.o -o mylib.dylib

include ../../makefiles/Make.clean
clean ::
	-@/bin/rm -f *.o *~ *.mod \
	  ${PROGRAMS} \
	  carray carraycall carraylib clink cpplink cprog cstring \
	  fbind findata fprog fstring
