# -*- makefile -*-
################################################################
################################################################
####
#### Makefile for:
####     Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2023
####
################################################################
################################################################

info ::
	@echo "Do: make pdf"
	@echo "to format the book"

FILE = EijkhoutIntroToHPC
LATEX = xelatex
.PHONY: onepass pdf
onepass :
	@TEXINPUTS=${TEXINPUTS}:graphics:macros:applications:.. \
	    ${LATEX} ${FILE}
pdf :
	@make --no-print-directory onepass
	@cd exercises && \
	for e in *.tex ; do \
	  if [ $$( cat $$e | grep label | wc -l ) -eq 1 ] ; then \
	    export nam=$$( cat $$e | grep label | sed -e 's/^.*label.//' -e 's/\}//' ) \
	     && if [ "$$e" != "$$nam.tex" ] ; then \
		    cp $$e $$nam.tex ; fi \
	  fi ; \
	done
	@make --no-print-directory onepass
	@make --no-print-directory onepass
	@cp ${FILE}.pdf ../ 

info ::
	@echo "Do: make clean"
	@echo "to clean up temporary files"
clean ::
	@/bin/rm -f *.{aux,blg,ilg,log,out,toc} *~ comment.cut \
	    exercises/*.tex
