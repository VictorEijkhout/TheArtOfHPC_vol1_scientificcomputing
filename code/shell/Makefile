################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
####
#### copyright 2010-2021 Victor Eijkhout
####
#### makefile for graph computations
####     code/shell
####
################################################################
################################################################

.PHONY: info
info ::

RUNS =
info ::
	@echo "make RUN (where RUN in: ${RUNS})"

RUNS += run_arguments
.PHONY: arguments run_arguments
arguments :
run_arguments :
	./arguments.sh the quick "brown fox" jumps

RUNS += run_hello
.PHONY: hello run_hello
run_hello :
	@echo "once:" && ./hello.sh
	@echo "twice:" && ./hello.sh -n 2
	@echo "thrice upper :" && ./hello.sh -n 3 -u
	@echo "error" && ./hello.sh -e

RUNS += run_submission
.PHONY: submission run_submission
submission:
run_submission :
	./submit.sh student1
	./submit.sh student2
	./submit.sh cheat1
	./submit.sh cheat2

include ../../makefiles/Make.run

include ../../makefiles/Make.public

include ../../makefiles/Make.clean
clean ::
	@echo "cleaning submissions"
	@cd submissions \
	&& for f in * ; do \
	     if [ "$$f" != "README" ] ; then \
	        /bin/rm -f "$$f" ; \
	     fi ; \
	   done
