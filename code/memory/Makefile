################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2020
####
#### makefile for memory exploration
####
################################################################
################################################################

.PHONY: info
info ::

PROGRAMS =  freemem 
XPROGRAMS  = freememx
LANGUAGE = C
MODE = seq
include ../../makefiles/Make.compile

# .SECONDEXPANSION:
# ${PROGRAMS} : $$@.o
# 	${C_COMPILER} -o $@ $^

freememx : 
	make LANGUAGE=CXX MODE=seq freememx.o
	${CXX_COMPILER} -o $@ freememx.o

include ../../makefiles/Make.public

##
## Cleanup : also remove programs
##
include ../../makefiles/Make.clean
clean ::
	@/bin/rm -f ${PROGRAMS} ${XPROGRAMS}
