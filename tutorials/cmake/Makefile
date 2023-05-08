# -*- makefile -*-
################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2022
####
#### makefile for Cmake tutorial projects
####
################################################################
################################################################

info ::

CFLAGS = -O2 -std=c99
MODE = seq

PROJECTS = 
info ::
	@echo "make build install run PROJECT=..."
	@echo "    in: ${PROJECTS}"
	@echo "    default: ${PROJECT}"
	@echo "    [ VERBOSE=0/1 ] verbose cmake & make output "
	@echo "    [ ECHO=0/1 ]    commandline echoing"
	@echo "    [ CMAKE_OPTIONS=... ]"

PROJECT = siliceum1
BOOKPROJECTS = \
    single single17 multiple includedir privatelib withlib publiclib pclib \
    cxxopts fmtlib fmtliblib eigen cuda \
    message mpiprog petscprog \
    mklcmake mklpc oneapi openmp \
    somelib
BOOKPROJECTSf = singlef withlibf
OTHERPROJECTS = arias_demo petsc_prog siliceum1 multimain \
    cmakegood1a cmakegood1b cmakegood1c cmakegood2a cmakegood2b cmakegood2e
PROJECTS += ${BOOKPROJECTS} ${BOOKPROJECTSf}

.PHONY: build install
options_cmakegood2b = --log-level=NOTICE -D MYVAR=myvalue
MAIN_single = program
MAIN = ${MAIN_${PROJECT}}
options_somelib = \
    -D CMAKE_SOMELIB_INCLUDE=$( command pwd )/install-withlib/include
pkgconfig_fmtlib = ${HOME}/Installation/fmtlib/installation-git/lib/pkgconfig
pkgconfig_petsc = ${PETSC_DIR}/${PETSC_ARCH}/lib/pkgconfig
prefixpath_oneapi = ${MKLROOT}/../2022.0.2/lib/cmake/mkl/
env_usepubliclib = \
    export TACC_AUX_LIB=../install-publiclib/lib && export TACC_AUX_INC=../install-publiclib/include
options_usepubliclib = \
    -D AUX_LIBRARY_DIR=../install-publiclib/lib -D AUX_INCLUDE_DIR=../install-publiclib/include
ECHO = 0
build :
	@export project=${PROJECT} \
	 && if [ "${ECHO}" = "1" ] ; then set -x ; fi \
	 && export builddir=build-$${project} \
	 && export installdir=install-$${project} \
	 && echo "========" && echo "Project $${project}" \
	 && echo "build dir: $${builddir}" && echo "install dir: $${installdir}" \
	 && echo "========" && echo "Setting up directories" && echo "--------" \
	 && rm -rf $$builddir && mkdir $$builddir \
	 && if [ ! -z "${CMAKE_OPTIONS}${options_${PROJECT}}" ] ; then \
	        echo ".. with options: ${CMAKE_OPTIONS} ${options_${PROJECT}}" \
	    ; fi \
	 && echo "--------" \
	 && ( \
	    cd $$builddir \
	     && source ${MAKEINCLUDES}/compilers.sh && setcompilers \
	     && export CXX=$${cxx} && export CC=$${cc} \
	     && if [ ! -z "${pkgconfig_${PROJECT}}" ] ; then \
	            export PKG_CONFIG_PATH=${pkgconfig_${PROJECT}}:${PKG_CONFIG_PATH} \
	        ; fi \
	     && if [ ! -z "${prefixpath_${PROJECT}}" ] ; then \
	            echo " .. adding prefix path: ${prefixpath_${PROJECT}}" \
	             && export CMAKE_PREFIX_PATH=${prefixpath_${PROJECT}}:${CMAKE_PREFIX_PATH} \
	        ; fi \
	     && if [ ! -z "${env_${PROJECT}}" ] ; then \
	            echo " .. adding environment: ${env_${PROJECT}}" \
	             && eval ${env_${PROJECT}} \
	        ; fi \
	     && if [ "${VERBOSE}" = "1" ] ; then verbose="-DCMAKE_VERBOSE_MAKEFILE=1" ; fi \
	     && cmdline="cmake ${CMAKE_OPTIONS} ${options_${PROJECT}} \
	            -D CMAKE_INSTALL_PREFIX=../$$installdir \
	            $$verbose \
	            ../$${project}" \
	     && if [ "${ECHO}" = "1" ] ; then echo "cmake: $$cmdline" ; fi \
	     && eval $$cmdline \
	     && echo "========" && echo "Making" && echo "--------" \
	     && echo not make V=1 \
	     && cmake --build . \
	    ) 2>&1 | tee build.log \
	 && echo "see build.log for output"

nobuild :
	foo \
	 && echo pkgconfig=$$( make -p 2>&1 | awk '/'$$project'/ {print}' ) \
	    && echo "pkgconfig: $$pkgconfig" \
	 && if [ ! -z "${pkgconfig_${PROJECT}}" ] ; then \
	        echo ".. with pkg config: ${pkgconfig_${PROJECT}}" \
	    ; fi \
	bar
install :
	@export project=${PROJECT} \
	 && export builddir=build-$${project} \
	 && export installdir=install-$${project} \
	 && rm -rf $$installdir && mkdir $$installdir \
	 && echo "========" && echo "Installing into $${installdir}" && echo "--------" \
	 && cmake --install $$builddir

info ::
	@echo "make run PROJECT=..."
run :
	@export project=${PROJECT} \
	 && export installdir=install-$${project} \
	 && main_single=program main_multiple=program \
	 && main=${MAIN} \
	 && if [ -z "$${main}" ] ; then \
	        if [ -f $${installdir}/program ] ; then \
	            main=program \
	        ; else \
	            echo "No MAIN_PROJECT macro defined for PROJECT=${PROJECT}" && exit 1 \
	        ; fi \
	    ; fi \
	 && cmdline=$${installdir}/$${main} \
	 && if [ $$project = "mpiprog" -o $$project = "petscprog" ] ; then \
	        cmdline="mpiexec -n 4 $$cmdline" ; fi \
	 && echo Executing: $$cmdline && eval $$cmdline

info ::
	@echo "make demo PROJECT=... (default: ${PROJECT})"
	@echo "    try: multiple"
.PHONY: demo
demo :
	@make --no-print-directory build install PROJECT="${PROJECT}"
	@export project=${PROJECT} \
	 && export builddir=build-$${project} \
	 && export installdir=install-$${project} \
	 && case $${project} in \
	    ( siliceum1 ) \
	        echo "----------------" \
	        && echo "touch a source file and make:" \
	        && touch $${project}/hello.cxx \
	        && ( cd $$builddir && make ) \
	        && echo "----------------" \
	        && echo "touch a header file and make:" \
	        && touch $${project}/funlib/fun.h \
	        && ( cd $$builddir && make ) \
	        ;; \
	    ( multiple ) \
	        ( echo "----------------" \
	        && echo "touch a source file and make:" \
	        && touch $${project}/aux.cxx \
	        && ( cd $$builddir && make ) \
	        ) > $${project}-touch1.txt \
	        && ( echo "----------------" \
	        && echo "touch a header file and make:" \
	        && touch $${project}/aux.h \
	        && ( cd $$builddir && make ) \
	        ) > $${project}-touch2.txt \
	        && git add $${project}-touch*.txt \
	        ;; \
	    ( * ) \
	        echo "ERROR: unknown project <<$$project>>" \
	        exit 1 \
	        ;; \
	    esac

info ::
	@echo "make book : try all book projects"
.PHONY: book
book :
	@for p in ${BOOKPROJECTS} ; do \
	    make build install run PROJECT=$$p \
	 ; done

info ::
	@echo "make clean"
.PHONY: clean
clean ::
	@find . -name \*~ -exec rm {} \;
	@rm -rf build-* install-*
