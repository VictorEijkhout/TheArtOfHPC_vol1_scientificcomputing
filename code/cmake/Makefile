################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
####
#### copyright 2010-2020 Victor Eijkhout
####
#### makefile for CMake tutorials
####
################################################################
################################################################

info ::
	@echo && echo "CMake demonstration projects" && echo 

PROJECTS = version hello hellolib hellolibdir \
    arias
PROJECT = hello
.PHONY : cmake build install run check_project_var
info ::
	@echo "make cmake build install run PROJECT=... (in: ${PROJECTS})"
	@echo "make do PROJECT=.... for short"
check_project_var :
	@if [ -z "${PROJECT}-example" ] ; then \
	    echo "Please set PROJECT variable" && exit 1 ; fi
	@if [ ! -d "${PROJECT}-example" ] ; then \
	    echo "Can not find directory ${PROJECT}-example" \
	    && exit 1 ; fi
	@if [ ! -d "${PROJECT}-example/${PROJECT}" ] ; then \
	    echo "Can not find source directory ${PROJECT}-example/${PROJECT}" \
	    && exit 1 ; fi
do : cmake build run
cmake : check_project_var
	@echo "Cmaking <<${PROJECT}>>" \
	 && cd ${PROJECT}-example \
	 && rm -rf installation build \
	 && mkdir installation build \
	 && cd build \
	 && cmake \
	        -D CMAKE_INSTALL_PREFIX=../installation \
	        ../${PROJECT} \
	 && echo ".. done cmaking"
build : check_project_var
	@echo "Building <<${PROJECT}>>" \
	 && cd  ${PROJECT}-example/build \
	 && make \
	 && echo ".. done building"
install : check_project_var
	@echo "Installing <<${PROJECT}>>" \
	 && cd  ${PROJECT}-example/build \
	 && make install \
	 && echo ".. done installing"

run : check_project_var
	@cd ${PROJECT}-example/build \
	 && ./${PROJECT}

include ../../makefiles/Make.public

include ../../makefiles/Make.clean
clean :: basic_clean
	@find . -name \*~ -exec rm -f {} \;
	@for p in ${PROJECTS} ; do \
	    echo "cleaning <<$$p>>" \
	     && rm -rf $$p-example/{build,installation} \
	     && find $$p-example -name \*~ -exec rm -f {} \; \
	 ; done
