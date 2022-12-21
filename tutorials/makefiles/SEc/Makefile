SRC := ${wildcard src/*.c}
OBJ := ${patsubst src/%,obj/%,${patsubst %.c,%.o,${SRC}}}
info :
	@echo Srcs: $(SRC)
	@echo Objs: ${OBJ}

all : ${OBJ}
obj/%.o : src/%.c
	cc -o $@ -c $<
