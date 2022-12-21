################################################################
####
#### Makefile for fft examples
####
################################################################

.PHONY: info
info ::
	@echo "Available targets:"

info ::
	@echo "make run PROGRAM=... (in ${PROGRAMS})"
PROGRAMS = basic_usage twod_usage
PROGRAM = basic_usage
info ::
	@echo "specific options:"
	@echo "  basic_usage: DEFINES=-DN=20 for problem size"

#
# compile rules
#
MODE = mpi
include Makefile.compile
LOAD_LIBS = -L${TACC_FFTW3_LIB} -lfftw3_mpi -lfftw3
INCLUDES  = -I${TACC_FFTW3_INC}
package ::
	@cp ../../code/Makefile.compile .

.PHONY: run
run : ${PROGRAM}
	@if [ -z "${PROGRAM}" ] ; then \
	    echo "Please specify PROGRAM variable"; \
	fi
	./${PROGRAM}

#
# clean
#
include ../../makefiles/Make.clean
clean ::
	@/bin/rm -f ${PROGRAMS}
package ::
	@cp ../../makefiles/Make.clean .

#
# maintainance stuff, only for victor
#
info ::
	@if [ "`whoami`" = "eijkhout" ] ; then \
	   echo "make package: copy make include files here" ; \
	 fi
.PHONY: package
package ::
