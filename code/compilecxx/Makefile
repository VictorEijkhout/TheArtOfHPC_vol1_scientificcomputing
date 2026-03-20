# -*- makefile -*-
################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2024
####
#### makefile for code/compilecxx
####
################################################################
################################################################

info ::

LANGUAGE = CXX
MODE = seq
PROGRAMS = hello fooprog oneprogram rotate 
include ../../makefiles/Make.compile

info ::
	@echo "make oneprogram"
oneprogram :: fooprog.o foosub.o

info ::
	@echo "%%%% illustration of compilation and linking"
	@echo "make run_makeoneprogram run_makeseparatecompile"
	@echo
RUNS += run_makeoneprogram run_makeseparatecompilex
run_makeoneprogram : example_clean
	${LINKER} -o oneprogram fooprog.cpp foosub.cpp
	./oneprogram
run_makeseparatecompilex : clean example_clean
	@make --no-print-directory fooprog.o ECHO=1 ECHOPREFIX=none
	@make --no-print-directory foosub.o ECHO=1  ECHOPREFIX=none
	@make --no-print-directory fooprog ECHO=1 EXTRA_OBJS=foosub.o ECHOPREFIX=none 2>/dev/null
	./fooprog

include ../../makefiles/Make.run

################
################ library rules
################
NMFLAGS = -C
include ../Make.libs

info ::
	@echo "make dynamicprogram"
PROGRAMS += dynamicprogram
dynamicprogram : fooprog.o makedynamiclib
	${LINKER} -o $@ fooprog.o -Llibs -lfoo
	@ls -l $@
info ::
	@echo "make rpathprogram"
PROGRAMS += rpathprogram
rpathprogram : fooprog.o  makedynamiclib
	${LINKER} -o $@ fooprog.o -Wl,-rpath=./libs -Llibs -lfoo
	@ls -l $@
SHAREOPTION = -shared
.PHONY: makedynamiclib showdynamiclib
RUNS += run_makedynamiclib run_showdynamiclib
makedynamiclib : example_clean 
	@make --no-print-directory PIC_OPTION=-fPIC libs/libfoo.so
run_makedynamiclib : 
	@echo "%%%%"; echo "Demonstration: making shared library" ; echo "%%%%"
	@make --no-print-directory makedynamiclib
showdynamiclib :
	@nm -C libs/libfoo.so | awk '$$2=="T" {print} $$1=="U" {print}'
run_showdynamiclib: 
	@echo "%%%%"; echo "Contents of shared library (U/T lines only)" ; echo "%%%%"
	@make --no-print-directory showdynamiclib

LIBS += libs/libfoo.so
libs/libfoo.so : foosub.o
	@mkdir -p libs
	@rm -f $@
	${LINKER} -o $@ ${SHAREOPTION} $^
info ::
	@echo

info ::
	@echo "%%%% illustration of static libraries"
	@echo "make run_staticprogram"
	@echo
RUNS += run_staticprogram
run_staticprogram : example_clean 
	@echo && echo "==== Use of static library ===="  && echo \
	 && make --no-print-directory staticprogram \
	 && echo && echo "---- running:" \
	 && ./staticprogram \
	 && echo "---- done"
# || echo ignoring >/dev/null 2>&1

info ::
	@echo "%%%% illustration of dynamic libraries"
	@echo "make run_dynamicprogram run_rpathprogram"
	@echo 
RUNS += run_dynamicprogram
run_dynamicprogram : example_clean
	@echo ; echo "Linking to shared library" ; echo
	@make --no-print-directory dynamicprogram
	@echo ; echo ".. note the size of the program" ; echo
	@ls -l dynamicprogram
	@echo ; echo ".. note unresolved link to a library" ; echo
	@cmd="ldd dynamicprogram | grep libfoo" \
	 && if [ `uname` = "Darwin" ] ; then \
	        cmd="otool -L dynamicprogram | grep libfoo" ; fi \
	 && echo $$cmd \
	 && eval $$cmd
	@echo ; echo ".. running by itself:" ; echo
	@make --no-print-directory run_shared_wrong
	@echo ; echo ".. note resolved with LD_LIBRARY_PATH" ; echo
	@cmd="LD_LIBRARY_PATH=\$${LD_LIBRARY_PATH}:./libs ldd dynamicprogram | grep libfoo" \
	 && if [ `uname` = "Darwin" ] ; then \
	        cmd="LD_LIBRARY_PATH=\$${LD_LIBRARY_PATH}:./libs otool -L dynamicprogram | grep libfoo" \
	    ; fi \
	 && echo $$cmd \
	 && eval $$cmd
	@echo ; echo ".. running with updated library path:" ; echo
	@make --no-print-directory run_shared_right
.PHONY: shared_wrong shared_right
RUNS += run_shared_wrong run_shared_right
run_shared_wrong : dynamicprogram
	@./dynamicprogram || /bin/true
run_shared_right : dynamicprogram
	@cmd="LD_LIBRARY_PATH=\$${LD_LIBRARY_PATH}:./libs dynamicprogram" \
	 && echo $$cmd \
	 && eval $$cmd
RUNS += run_rpathprogram
run_rpathprogram : rpathprogram
	./rpathprogram

info ::
	@echo "%%%% study of optimization levels"
	@echo "make run_rotate PROGRAM=... (from: ${ROTATE_PROGRAMS})"
	@echo "    (suggestion: compiler dependent, use OUTARCH)"
	@echo
ROTATE_PROGRAMS = rotate rotate_common
.PHONY: optimize
gcc_OPT_REPORT = -fopt-info
# -fprofile-report
intel_OPT_REPORT = -qopt-report=4
OPT_REPORT = ${${TACC_FAMILY_COMPILER}_OPT_REPORT}
RUNS += run_rotate
run_rotate :
	@if [ -z "${PROGRAM}" ] ; then \
	    echo "Please supply variable PROGRAM" && exit 1 ; fi
	@program=${PROGRAM} \
	 && for opt in 0 1 2 3 ; do \
	        echo "Optimization level $$opt" \
	         && rm -f $${program} $${program}.o \
	         && make --no-print-directory $${program} \
	                LANGUAGE=${LANGUAGE} MODE=${MODE} \
	                ECHO=${ECHO} OPTLEVEL=$$opt OPT_REPORT=${OPT_REPORT} \
	         && ./$${program} \
	    ; done

.PHONY: ${RUNS}

##
## code stripping
##
SOURCES = fooprog.c foosub.c rotate.c hello.c
info ::
	@echo "make strip_sources : remove header"
.PHONY: strip_sources
strip_sources :
	for s in ${SOURCES} ; do \
	    cat $$s | awk 'p==1 && !/snippet/ {print} NF==0 {p=1}' > $$s.stripped.out \
	    ; done
total_clean ::
	@rm -f *.stripped_out

##
## public copy
##
PUBLICEXTS = cpp runout
include ../../makefiles/Make.public

##
## clean rules
##
include ../../makefiles/Make.clean
clean ::
	@rm -f *.optrpt *.annot

.PHONY: example_clean
info ::
	@echo "make example_clean : remove local binaries"
example_clean ::
	@rm -f ${PROGRAMS} ${LIBS}
clean :: example_clean
	@rm -rf libs
