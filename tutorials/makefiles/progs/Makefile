info ::
	@echo "make main1/2/3"

PROGS = main1 main2 main3

.SECONDEXPANSION:
${PROGS} : $$@.o
	${CC} -DCUSTOM -o $@ $^
main3 : lib.o

clean :
	rm -f *.o *~ ${PROGS}
