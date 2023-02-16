################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
####
#### copyright 2010-2020
####
#### makefile for neural net minimization
####
################################################################
################################################################

.PHONY: info
info ::

PROGRAMS = bitp bits intc power ellipse pi
LANGUAGE = CXX
include ../../makefiles/Make.compile

.SECONDEXPANSION:
# libraries
INCLUDES = -I${HOME}/Installation/cli11/installation/include
# https://cliutils.github.io/CLI11/class_c_l_i_1_1_app.html
# https://cliutils.github.io/CLI11/book/chapters/options.html
# %.o : %.cxx
# 	${CXX} -std=c++17 -g -O2 \
# 	    ${INCLUDES} \
# 	    -c $^

# ellipse program
LIBS = minimlib.o vectorlib.o
ellipse,pi : $$@.o ${LIBS}
	${CXX} -o $@ $< ${LIBS}
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
neuralnet : $$@.o vectorlib.o
	${CXX} -o $@ $^
.PHONY: run_neuralnet
RUNS += run_neuralnet
run_neuralnet : neuralnet
	@./neuralnet

PUBLICEXTS = py c cxx h runout
include ../../makefiles/Make.public

include ../../makefiles/Make.run

##
## Cleanup : also remove programs
##
include ../../makefiles/Make.clean
clean ::
	@/bin/rm -f ${PROGRAMS}
