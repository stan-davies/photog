CMD = gcc

FILES = main.c util/ppmio.c util/imgform.c translate/translate.c

INC = -I .

OUT = pio

all : compile
compile :
	${CMD} ${FILES} ${INC} -o ${OUT}
