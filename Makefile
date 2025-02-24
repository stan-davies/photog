CMD = gcc

FILES = main.c util/ppmio.c

OUT = pio

all : compile
compile :
	${CMD} ${FILES} -o ${OUT}
