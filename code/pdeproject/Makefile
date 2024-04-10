

info ::

ifdef PETSC_DIR
include ${PETSC_DIR}/lib/petsc/conf/variables
endif

PROGS = construct power inverse system time dump restart
FPROGS = constructf

info ::
	@echo "make PROGRAM where PROGRAM=${PROGS} (or Fortran: ${FPROGS})"
% : %.c
	${CC} -o $@ $^ ${PETSC_INCLUDE} ${PETSC_LIB} \
	    -I${HDF5_INCLUDE_DIR} -L${HDF5_LIB_DIR} -lhdf5
% : %.F
	${FC} -o $@ $^ ${PETSC_INCLUDE} ${PETSC_LIB} \
	    -I${HDF5_INCLUDE_DIR} 

DT = .1
DX = .1
PLICIT = im
plotrun :
	export FILENAME=${PLICIT}plicit-${DX}-${DT} ; \
	  ./dump -${PLICIT}plicit -deltax ${DX} -deltat ${DT} ; \
	  mv plot.dat $$FILENAME.dat ; \
	  cat plot.cmd | sed s/FILENAME/$$FILENAME/ | gnuplot

include ../../makefiles/Make.public

info ::
	@echo "make clean"
include ../../makefiles/Make.clean
clean ::
	@/bin/rm -rf ${PROGS} {implicit,explicit}*.{dat,pdf} *.dat
