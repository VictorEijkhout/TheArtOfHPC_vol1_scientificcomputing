################################################################
################################################################
####
#### This Makefile belong with the sources
#### for Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2023
####
#### makefile for boost python interaction
####
################################################################
################################################################

info ::

#### https://stackoverflow.com/questions/35795820/how-to-use-boost-python

info ::
	@echo "================"
	@echo "make all : build library"

TARGET = hello_ext
HELLO = hello
all : ${TARGET}.so
PYTHON3VER = 7
PYTHON3m_7 = m
PYTHON3m_9 = 
PYTHON3m = ${PYTHON3m_${PYTHON3VER}}

ifeq "${TACC_FAMILY_COMPILER}" "intel"
  CXX = icpc
else
  CXX = g++
endif

${TARGET}.so : ${TARGET}.o ${HELLO}.o
	ls ${TACC_BOOST_LIB}/libboost_python*
	pythonver=`echo ${TACC_PYTHON_VER} | sed -e 's/\.//'` \
	 && if [ $$pythonver = "3.7" ] ; then pythonver=${pythonver}m ; fi \
	 && ${CXX} -shared -o $@ $^ \
	        -Wl,-rpath,${TACC_BOOST_LIB}  -L${TACC_BOOST_LIB}  -lboost_python$${pythonver} \
	        -Wl,-rpath,${TACC_PYTHON_LIB} -L${TACC_PYTHON_LIB} -lpython3
%.o : %.cxx
	pythonver=${TACC_PYTHON_VER} \
	 && if [ $$pythonver = "3.7" ] ; then pythonver=$${pythonver}m ; fi \
	 && cmd="${CXX} -c $< -fPIC \
	        -I. -I${TACC_BOOST_INC} -I${TACC_PYTHON_INC}/python$${pythonver}" \
	 && echo $$cmd && eval $$cmd

PUBLICEXTS = py cxx h
include ../../makefiles/Make.public

include ../../makefiles/Make.clean
clean ::
	@rm -f *.so
