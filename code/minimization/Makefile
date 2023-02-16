################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2022
####
#### makefile for neural net minimization
####
################################################################
################################################################

.PHONY: info
info ::

.SECONDEXPANSION:
# libraries
vectorlib.o : vectorlib.h
minimlib.o : minimlib.h vectorlib.h
INCLUDES = -I${HOME}/Installation/cli11/installation/include -I${TACC_CXXOPTS_INC}
LANGUAGE = CXX

# ellipse program
PROGRAMS = ellipse pi
EXTRA_OBJS = minimlib.o vectorlib.o
include ../../makefiles/Make.compile

ellipse.o : minimlib.h vectorlib.h
pi.o : pi.h
.PHONY: run_ellipse run_pi run_descentcircle run_descentellipse
RUNS += run_ellipse run_pi run_descentcircle run_descentellipse
run_ellipse : ellipse
	@./ellipse
run_pi : pi
	@./pi
run_descentcircle : ellipse
	@./ellipse \
	| awk '/descentcircle/ {p=0} p==1 {print} /DescentCircle/ {p=1} '
run_descentellipse : ellipse
	@./ellipse \
	| awk '/descentellipse/ {p=0} p==1 {print} /DescentEllipse/ {p=1} '

PROGRAMS += neuralnet
neuralnet.o : minimlib.h vectorlib.h
.PHONY: run_neuralnet
RUNS += run_neuralnet
run_neuralnet : neuralnet
	@./neuralnet

include ../../makefiles/Make.run

include ../../makefiles/Make.public

##
## Cleanup : also remove programs
##
include ../../makefiles/Make.clean
clean ::
	@/bin/rm -f ${PROGRAMS}
