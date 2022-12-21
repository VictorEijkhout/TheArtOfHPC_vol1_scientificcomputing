# -*- makefile -*-
################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2022
####
#### makefile for HDF5 tutorial projects
####
################################################################
################################################################

info ::
	@echo "make examples [${EXAMPLES}]"

EXAMPLES = create dataset parmdataset parmwrite allread \
    h5ex
SOURCES = ${patsubst %,%.c,${EXAMPLES}}
OBJECTS = ${patsubst %,%.o,${EXAMPLES}}
${OBJECTS} : myh5defs.h

.SECONDEXPANSION:
${EXAMPLES} : h5check $$@.o
	${CC} -o $@ $@.o -L${HDF5_LIB_DIR} -lhdf5
%.o : %.c
	${CC} -c $< -I. -I${HDF5_INCLUDE_DIR} -DH5_USE_16_API

.PHONY: clean h5check
h5check :
	@if [ `env | grep -i hdf5_ | wc -l` -lt 1 ] ; then \
	  echo ; echo "Please load the hdf5 module"; echo ; \
	  exit 1 ; fi
clean ::
	@rm -f *~ *.o ${EXAMPLES} *.h5

