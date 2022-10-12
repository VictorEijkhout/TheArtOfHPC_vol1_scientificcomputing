# -*- makefile -*-
################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2021
####
#### makefile for LaTeX demos
####
################################################################
################################################################

info ::
	@echo "================================"
	@echo && echo "Make LaTeX examples for textbook"

TEXFILES = demo listing barchart
include ../../makefiles/Make.tex

include ../../makefiles/Make.public
MOREPUBLICFILES = *.tex barchart.bbl barchart.pdf demopage1.pdf demopage2.pdf listing.bbl listing.pdf

include ../../makefiles/Make.clean

