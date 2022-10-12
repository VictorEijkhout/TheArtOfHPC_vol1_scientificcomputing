# -*- makefile -*-
################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2021
####
#### makefile for code/array
####
################################################################
################################################################

info ::

MODE = seq
LANGUAGE = C
include ../../makefiles/Make.compile
PROGRAMS = cansi c99 cmalloc cmalloc2d

RUNS += run_set1d run_set2d run_pass2d run_setstar
.PHONY: run_set1d run_set2d run_pass2d run_setstar
run_set1d run_set2d run_pass2d run_setstar : cansi
run_set1d :
	@./cansi \
	| awk '/set1d/ {p=0} p==1 {print} /SET1D/ {p=1}'
run_set2d :
	@./cansi \
	| awk '/set2d/ {p=0} p==1 {print} /SET2D/ {p=1}'
run_pass2d :
	@./cansi \
	| awk '/pass2d/ {p=0} p==1 {print} /PASS2D/ {p=1}'
run_setstar :
	@./cansi \
	| awk '/setstar/ {p=0} p==1 {print} /SETSTAR/ {p=1}'

RUNS += run_set99
.PHONY: run_set99
run_set99 : c99
	echo 5 | ./c99

RUNS += run_cmalloc2d
.PHONY: run_cmalloc2d
run_cmalloc2d : cmalloc2d
	( echo 5 && echo 6 ) | ./cmalloc2d
RUNS += run_rowlength
.PHONY: run_rowlength
run_rowlength : cmalloc2d
	( echo 5 && echo 6 ) | ./cmalloc2d \
	| awk '/rowlen/ {p=0} p==1 {print} /ROWLEN/ {p=1}'

RUNS += run_cmalloc run_cmallocpass
.PHONY: run_cmalloc run_cmallocpass
run_cmalloc run_cmallocpass : cmalloc
run_cmalloc :
	@echo 5 | ./cmalloc \
	| awk '/malloc1d/ {p=0} p==1 {print} /MALLOC1D/ {p=1} '
run_cmallocpass :
	@echo 5 | ./cmalloc \
	| awk '/malloc2d/ {p=0} p==1 {print} /MALLOC2D/ {p=1} '

include ../../makefiles/Make.run

include ../../makefiles/Make.public

include ../../makefiles/Make.clean
