################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
####
#### copyright 2010-2023
####
#### makefile for computer arithmetic examples
####
################################################################
################################################################

.PHONY: info
info ::
	@echo "Available targets:"

##
## Applications in this directory
##
info ::
	@echo "make PROGRAM (in ${APPS})"
APPS = d1

LANGUAGE = CXX
MODE = seq
include ../../makefiles/Make.compile
ifeq "${TACC_SYSTEM}" "macbookair"
  CXXOPTS = ${HOME}/Installation/cxxopts/installation
else
  CXXOPTS = ${STOCKYARD}/cxxopts/installation-intel
endif
EXTRA_OPTIONS = -I${CXXOPTS}/include

PUBLICEXTS = cxx
include ../../makefiles/Make.public

####
#### cleaning
####

include ../../makefiles/Make.clean
clean ::
	@/bin/rm -f ${APPS}
