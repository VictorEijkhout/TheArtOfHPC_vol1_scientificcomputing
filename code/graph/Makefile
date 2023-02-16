################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
####
#### copyright 2010-2023 Victor Eijkhout
####
#### makefile for graph computations
####     code/graph
####
################################################################
################################################################

info ::
	@echo

PROGRAMS = graphmvp
include ../../makefiles/Make.compile
LANGUAGE = CXX
MODE = seq

RUNS =

RUNS += run_graph1
.PHONY: run_graph1 graph1
run_graph1 : graphmvp
	@./graphmvp \
	| awk '/example1/ {p=0} p==1 {print} /EXAMPLE1/ {p=1}'

RUNS += run_graph2
.PHONY: run_graph2 graph2
run_graph2 : graphmvp
	@./graphmvp \
	| awk '/example2/ {p=0} p==1 {print} /EXAMPLE2/ {p=1}'

include ../../makefiles/Make.run

PUBLICEXTS = runout
PUBLICFILES = README
include ../../makefiles/Make.public

include ../../makefiles/Make.clean
clean :: 
	@rm -f ${PROGRAMS}
