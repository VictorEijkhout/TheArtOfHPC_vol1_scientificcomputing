info ::
	@echo "make <progname>"
	@echo "make clean"

PROGS = root root2 roots say square square1 square2 up
% : %.c
	cc -g -O0 -o $@ $@.c

info ::
	@echo "make fence"
fence :
	@cc -g -O0 -o fence up.c -L/opt/local/lib/ -lefence

clean ::
	@/bin/rm -rf ${PROGS} *~ *.o *.dSYM
