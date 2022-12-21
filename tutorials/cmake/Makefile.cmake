# -*- makefile -*-

include ../../../Makefile.clean
clean ::
	@rm -rf CMakeCache.txt CMakeFiles Makefile cmake_install.cmake
	@echo "PROGRAM=<<${PROGRAM}>>"
	@if [ ! -z "${PROGRAM}" ] ; then rm ${PROGRAM} ; fi
