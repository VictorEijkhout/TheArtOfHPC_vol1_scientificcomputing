# -*- makefile -*-
################################################################
################################################################
####
#### Makefile for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2021
####
#### makefile for slides
####
################################################################
################################################################

info::

info ::
	@echo "make lecture [ LECTURE=... (default: ${LECTURE}) ]"
	@echo "    available: ${LECTURES}"
	@echo "make lectures : format all"
LECTURE = arithmetic
LECTURES = arithmetic cmake course debug git graph intro iterative linear \
    nbody parallel programming scaling unix
.PHONY: lecture lectures onepass pdf
lecture :
	make onepass FILE=hpc_${LECTURE}
	make upload_dropbox upload_publicpdf upload_studentrepo  FILE=hpc_${LECTURE}.pdf
lectures :
	@for l in ${LECTURES} ; do \
	    make lecture LECTURE=$$l \
	    ; done
onepass :
	TEXINPUTS=..//:${TEXINPUTS} pdflatex ${FILE}
pdf :
	make onepass FILE=${FILE}
	make onepass FILE=${FILE}
	make upload  FILE=${FILE}.pdf

info ::
	@echo "make preview"
.PHONY: preview
preview:
	xpdf -g 770x477 ${FILE}.pdf &

include ../booksources/makefiles/Make.upload
include ../booksources/makefiles/Make.clean
