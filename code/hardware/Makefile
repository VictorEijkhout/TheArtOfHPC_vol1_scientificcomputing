################################################################
################################################################
####
#### Makefile for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2024
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
    branch loopexchange saturation template denormal unroll

MODE = omp
MODULES = cxxopts
LANGUAGE = CXX

EXTRA_OBJS = clock.o allocation.o
include ../../makefiles/Make.compile
CPPSTANDARD = 2b
allocation.o : allocation.hpp
clock.o : clock.hpp

EXTRA_INCLUDES = \
    $$( pkg-config --cflags cxxopts ) 
EXTRA_OPTIONS_intel = -qopt-report
## EXTRA_OPTIONS += -DFMT_ENFORCE_COMPILE_STRING
EXTRA_OPTIONS += ${EXTRA_OPTIONS_${TACC_FAMILY_COMPILER}}
EXTRA_LIBS =
RPATH = ${TACC_FMTLIB_LIB}
info ::
	@echo "note: EXTRA_OPTIONS set to: ${EXTRA_OPTIONS}, use EXTRA_EXTRA_OPTIONS"

RUNS =
info ::
	@echo "---- custom runs:"
	@echo "make run_whatever"
	@echo "    [ GITADD= (nonzero for git add) ]"
include ../../makefiles/Make.omp_run

RUNS += run_associativity
REPEATS = 10000
info ::
	@echo "make run_associativity"
	@echo "    [ EXTRAID=... ] [ REPEATS=123 ( default=${REPEATS} ) ]"
run_associativity : associativity
	@program=$@ && program=$${program##run_} \
	 && runoutid=${TACC_SYSTEM} \
	 && if [ ! -z "${EXTRAID}" ] ; then \
	      runoutid=$${runoutid}-${EXTRAID} ; fi \
	 && results=$${program}-$${runoutid}.out \
	 \
	 && maxassoc=14 && minassoc=4 \
	 && assoc_values=$$( seq -s "," $$minassoc $$maxassoc ) \
	 && cmdline="./associativity --associativity $${assoc_values} -r ${REPEATS}" \
	 && if [ ${ECHO} -gt 0 ] ; then \
	      echo "Executing: $$cmdline" \
	    ; fi \
	 && $$cmdline >$${results} \
	 && echo "---- $${results}" && cat $${results} \
	 \
	 && if [ ! -z ${GITADD} ] ; then \
	      mv $${results} $${results%%.out}.runout \
	       && git add $${results%%.out}.runout \
	       && git commit -m "$${program} scaling output for $${runoutid}" \
	    ; fi 

GITADD = 
NSIZE = 1000
RUNS += run_bandwidth
ITERATIONS= 10
EXTRAID = 
info ::
	@echo "make run_bandwidth"
	@echo "    [ NSIZE= (default: ${NSIZE}) ] [ ITERATIONS= (default ${ITERATIONS}) ]"
	@echo "    [ RUN_OPTIONS=... ] [ EXTRAID=string ]"
run_bandwidth : bandwidth
	@program=$@ && program=$${program##run_} \
	 && runoutid=${TACC_SYSTEM}${NSIZE} \
	 && if [ ! -z "${EXTRAID}" ] ; then \
	      runoutid=$${runoutid}-${EXTRAID} ; fi \
	 && results=$${program}-$${runoutid}.out \
	 && make --no-print-directory omp_scaling PROGRAM=$${program} \
	    ECHO=${ECHO} NDIV=${NDIV} RUNOUTID=$${runoutid} RESULTS="$${results}" \
	    RUN_OPTIONS="-k ${NSIZE} -i ${ITERATIONS} " \
	 && if [ ! -z ${GITADD} ] ; then \
	      mv $${results} $${results%%.out}.runout \
	       && git add $${results%%.out}.runout \
	       && git commit -m "$${program} scaling output for $${runoutid}" \
	    ; fi 

RUNS += run_cachesize
run_cachesize : cachesize
	@program=$@ && program=$${program##run_} \
	 && runoutid=${TACC_SYSTEM} \
	 && if [ ! -z "${EXTRAID}" ] ; then \
	      runoutid=$${runoutid}-${EXTRAID} ; fi \
	 && results=$${program}-$${runoutid}.out \
	 && cmdline="./cachesize -B 11000 ${RUN_OPTIONS}" \
	 && if [ "${ECHO}" = "1" ] ; then \
	      echo "cmdline=$$cmdline" && echo "  into $$results" ; fi \
	 && eval $$cmdline | tee $$results \
	 && if [ ! -z ${GITADD} ] ; then \
	      mv $${results} $${results%%.out}.runout \
	       && git add $${results%%.out}.runout \
	       && git commit -m "$${program} scaling output for $${runoutid}" \
	    ; fi 

RUNS += run_denormal
run_denormal : 
	@program=$@ && program=$${program##run_} \
	 && runoutid=${TACC_SYSTEM} \
	 && if [ ! -z "${EXTRAID}" ] ; then \
	      runoutid=$${runoutid}-${EXTRAID} ; fi \
	 && results=$${program}-$${runoutid}.out && rm -f $$results \
	 \
	 && make --no-print-directory clean \
	 && echo "==== Flush to zero" | tee -a $$results \
	 && make --no-print-directory denormal ECHO=${ECHO} \
	        EXTRA_OPTIONS="${EXTRA_OPTIONS} -ftz" \
	 && ./denormal | tee -a $$results \
	 \
	 && make --no-print-directory clean \
	 && echo "==== No flush to zero" | tee -a $$results \
	 && make --no-print-directory denormal ECHO=${ECHO} \
	        EXTRA_OPTIONS="${EXTRA_OPTIONS} -no-ftz" \
	 && ./denormal | tee -a $$results \
	 && if [ ! -z ${GITADD} ] ; then \
	      mv $${results} $${results%%.out}.runout \
	       && git add $${results%%.out}.runout \
	       && git commit -m "$${program} scaling output for $${runoutid}" \
	    ; fi 

RUNS += run_stride
info ::
	@echo "run_stride"
	@echo "    [ NSIZE= (data set in kwords, default=${NSIZE} ) ]"
run_stride : stride
	@program=$@ && program=$${program##run_} \
	 && runoutid=${TACC_SYSTEM}${NSIZE} \
	 && if [ ! -z "${EXTRAID}" ] ; then \
	      runoutid=$${runoutid}-${EXTRAID} ; fi \
	 && results=$${program}-$${runoutid}.out \
	 && make --no-print-directory omp_scaling PROGRAM=$${program} \
	    ECHO=${ECHO} NDIV=${NDIV} RUNOUTID=$${runoutid} RESULTS="$${results}" \
	    RUN_OPTIONS="-D ${NSIZE}" \
	 && if [ ! -z ${GITADD} ] ; then \
	      mv $${results} $${results%%.out}.runout \
	       && git add $${results%%.out}.runout \
	       && git commit -m "$${program} scaling output for $${runoutid}" \
	    ; fi 


####
#### old tests to be redone
####

RUNS += run_unroll
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

run_old_associativity : associativity
	@cmdline="./associativity ${RUN_OPTS}" \
	 && if [ ${ECHO} -gt 0 ] ; then \
	      echo "Executing: $$cmdline" \
	    ; fi \
	 && $$cmdline

RUNS += run_falsesharing
run_falsesharing : falsesharing-omp
	@make --no-print-directory omp_run PROGRAM=falsesharing-omp \
	    ECHO=${ECHO}

# RUNS += run_falsesharing
# .PHONY: run_falsesharing-thread
# run_falsesharing-thread : falsesharing-thread
# 	@OMP_NUM_THREADS=${NP} \
# 	    ./falsesharing-thread

RUNS += run_saturation
run_saturation : saturation
	@./saturation
.PHONY: ${RUNS}

PUBLICEXTS = cxx hpp runout
include ../../makefiles/Make.public

.PHONY: ${RUNS}

clean :
	@rm -rf ${PROGRAMS} *.o *.o.tmp *~ *.dSYM 
	@rm -f *.gch *.pchi *.optrpt *.opt.yaml
	@rm -f *.out
