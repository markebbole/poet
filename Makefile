CC = g++
CFLAGS = -g -Wall -std=c++0x
INC=-.
INC_PARAMS=$(foreach d, $(INC), -I$d)

OBJs =   token.o dictionary.o lexer.o

default: lexer

lexer: ${OBJs}
	${CC} ${CFLAGS} ${INC_PARAMS} ${OBJs} -o lexer


dictionary.o: dictionary.cpp
	${CC} ${CFLAGS} ${INC_PARAMS} -c dictionary.cpp
	
lexer.o:	lexer.cpp
	${CC} ${CFLAGS} ${INC_PARAMS} -c lexer.cpp


clean:
	rm -f lexer

depend:
	makedepend -I. *.c# DO NOT DELETE
