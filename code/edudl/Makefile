################################################################
####
#### Makefile for building EduDL network
####
################################################################

info ::
	@echo && echo "%%%% Edu DL %%%%" && echo "Available rules:"

include Make.inc

#
# for now just a single build line
#
LIBSRCS := vector2.cpp matrix.cpp net.cpp dataset.cpp layer.cpp funcs.cpp vector.cpp 
ifeq "${USE_BLIS}" "1"
 LIBSRCS += matrix_impl_blis.cpp vector_impl_blis.cpp vectorbatch_impl_blis.cpp
else
 LIBSRCS += matrix_impl_reference.cpp vector_impl_reference.cpp vectorbatch_impl_reference.cpp
endif
LIBOBJS = $(patsubst %.cpp,%.o,${LIBSRCS})

%.o : %.cpp
	@echo "compiling $<"
	@${CXX} -c $< \
	    -I${CXXOPTS}/include \
	    ` if [ "${USE_BLIS}" = "1" ] ; then echo "-DBLISNN -I${BLIS_INC_DIR}" ; fi `

dataset.o funcs.o layer.o matrix.o net.o vector2.o : vector2.h
dataset.o layer.o matrix.o net.: matrix.h
dataset.o : dataset.h 
funcs.o : funcs.h matrix.h
layer.o : layer.h funcs.h
net.o : net.h dataset.h layer.h
test.o : matrix.h net.h dataset.h layer.h funcs.h

PROGRAMS = testdl posneg mpidl
info ::
	@echo "make PROGRAM (where PROGRAM in ${PROGRAMS}) : make application"
.SECONDEXPANSION:
testdl : test.o ${LIBOBJS}
	@echo "Linking test program <<$@>>"
	@${CXX} -o $@ $^ \
	    ` if [ "${USE_BLIS}" = "1" ] ; then echo "-L${BLIS_LIB_DIR} -lblis -lm" ; fi `
mpidl : test_mpi.o ${LIBOBJS} net_mpi.o
	@echo "Linking test program <<$@>>"
	@${CXX} -o $@ $^ \
	    ` if [ "${USE_BLIS}" = "1" ] ; then echo "-L${BLIS_LIB_DIR} -lblis -lm" ; fi `
posneg : $$@.o ${LIBOBJS}
	@echo "Linking test program <<$@>>"
	@${CXX} -o $@ $^ \
	    ` if [ "${USE_BLIS}" = "1" ] ; then echo "-L${BLIS_LIB_DIR} -lblis -lm" ; fi `
test.o posneg.o : vector2.h net.h dataset.h vector.h

include ../../makefiles/Make.public

.PHONY: clean
info ::
	@echo "make clean : remove junk and executables"
clean ::
	@rm -f *~ *.o *.o.tmp a.out ${PROGRAMS}
