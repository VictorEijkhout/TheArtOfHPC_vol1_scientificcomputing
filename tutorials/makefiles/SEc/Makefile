##codesnippet makerulesrc
SRC := ${wildcard src/*.c}
##codesnippet end

##codesnippet makeruleobj
OBJ := ${patsubst src/%,obj/%,${patsubst %.c,%.o,${SRC}}}
##codesnippet end

##codesnippet makerulepre
PRE := ${addprefix /usr/lib,${SRC} othersrc moresrc}
##codesnippet end

##codesnippet makerulebak
BAK := ${addsuffix .bak,${SRC}}
##codesnippet end

EXAMPLES = src obj pre bak
info : ${EXAMPLES}
.PHONY: ${EXAMPLES}
src :
	@echo "SRC: $(SRC)"
obj :
	@echo "OBJ: ${OBJ}"
pre :
	@echo "PRE: ${PRE}"
bak :
	@echo "BAK: ${BAK}" 

all : ${OBJ}
obj/%.o : src/%.c
	cc -o $@ -c $<

include ../Make.snippets
