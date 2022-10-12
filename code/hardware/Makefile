################################################################
################################################################
####
#### Makefile for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2022
####
#### makefile for hardware effects
####
################################################################
################################################################

info ::
	@echo "make PROGRAM (in: ${PROGRAMS})"
	@echo "make run_PROGRAM (in: ${RUNS})"


PROGRAMS = arrayindex associativity bandwidth cachesize dependence stride strides  \
    falsesharing-omp falsesharing-thread falsesharing-spin \
    loopexchange saturation template denormal unroll

MODE = omp
LANGUAGE = CXX

include ../../makefiles/Make.compile
${PROGRAMS} : clock.o allocation.o
allocation.o : allocation.hpp
clock.o : clock.hpp

ifeq "${TACC_SYSTEM}" "macbookair"
  CXXOPTS = ${HOME}/Installation/cxxopts/installation
else
  CXXOPTS = ${TACC_CXXOPTS_INC}
endif
EXTRA_OPTIONS_intel = -qopt-report=5
EXTRA_OPTIONS += -I${CXXOPTS}/include ${EXTRA_OPTIONS_${TACC_FAMILY_COMPILER}}
info ::
	@echo "note: EXTRA_OPTIONS set to: ${EXTRA_OPTIONS}, use EXTRA_EXTRA_OPTIONS"

ifdef TACC_SYSTEM
EXTRA_LIBS=-lpthread
endif

NP = 24

RUNS =
include ../../makefiles/Make.omp_run

RUNS += run_cachesize
.PHONY: run_cachesize
run_cachesize : cachesize
	@./cachesize

RUNS += run_stride run_strides
.PHONY: run_stride run_strides
info ::
	@echo "special case:"
	@echo "    make run_stride run_strides"
	@echo "        [ FLUSH=0/1, default=${FLUSH} ]"
	@echo "        [ NP=..., default=${NP} : maximum #threads (run_strides only) ]"
FLUSH = 1
run_stride : stride
	@./stride \
	    `if [ "${FLUSH}" = "1" ] ; then echo "-f"; fi `
run_strides : strides
	@rm -f strides.tkz
	@make --no-print-directory omp_scaling PROGRAM=strides RUN_OPTIONS="-k 6000"
	@git add strides.tkz

RUNS += run_unroll
.PHONY: run_unroll
run_unroll : 
	@if [ "${TACC_FAMILY_COMPILER}" = "intel" ] ; then \
	    for model in fast precise ; do \
	        rm -f unroll unroll.o \
	         && make unroll EXTRA_EXTRA_OPTIONS="-fp-model $$model" ECHO=1 >/dev/null 2>&1 \
	         && ./unroll -m $$model \
	    ; done \
	; else \
	    make --no-print-directory unroll \
	     && ./unrol \
	; fi

RUNS += run_associativity
.PHONY: run_associativity
run_associativity : associativity
	@./associativity

RUNS += run_bandwidth
.PHONY: run_bandwidth
run_bandwidth : bandwidth
	@cmdline="OMP_PROC_BIND=true ./bandwidth -t `make --no-print-directory num_cores` -s 8 -k 64" \
	 && echo $$cmdline \
	 && eval $$cmdline

RUNS += run_denormal run_denormalflush
.PHONY: run_denormal run_denormalflush
run_denormal : 
	make --no-print-directory denormal \
	        EXTRA_OPTIONS="${EXTRA_OPTIONS} -no-ftz" \
	    ECHO=${ECHO}
	@./denormal
run_denormalflush : 
	make --no-print-directory denormal \
	        EXTRA_OPTIONS="${EXTRA_OPTIONS} -ftz" \
	    ECHO=${ECHO}
	@./denormal

RUNS += run_falsesharing
.PHONY: run_falsesharing
run_falsesharing : falsesharing-omp
	@make --no-print-directory omp_run PROGRAM=falsesharing-omp \
	    ECHO=${ECHO}

# RUNS += run_falsesharing
# .PHONY: run_falsesharing-thread
# run_falsesharing-thread : falsesharing-thread
# 	@OMP_NUM_THREADS=${NP} \
# 	    ./falsesharing-thread

RUNS += run_saturation
.PHONY: run_saturation
run_saturation : saturation
	@./saturation

clean :
	@rm -rf ${PROGRAMS} *.o *~ *.dSYM *.gch *.optrpt
