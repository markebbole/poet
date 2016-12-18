CC = g++
CFLAGS = -g -Wall -std=c++11
INC=-.
INC_PARAMS=$(foreach d, $(INC), -I$d)

OBJs =   expression.o token.o dictionary.o statement.o parser.o lexer.o interpreter.o runner.o

default: parser

parser: ${OBJs}
	${CC} ${CFLAGS} ${INC_PARAMS} ${OBJs} -o parser

	
lexer.o:	lexer.cpp
	${CC} ${CFLAGS} ${INC_PARAMS} -c lexer.cpp

statement.o: statement.cpp
	${CC} ${CFLAGS} ${INC_PARAMS} -c statement.cpp

expression.o: expression.cpp
	${CC} ${CFLAGS} ${INC_PARAMS} -c expression.cpp

parser.o: parser.cpp
	${CC} ${CFLAGS} ${INC_PARAMS} -c parser.cpp

interpreter.o: interpreter.cpp
	${CC} ${CFLAGS} ${INC_PARAMS} -c interpreter.cpp

dictionary.o: dictionary.cpp
	${CC} ${CFLAGS} ${INC_PARAMS} -c dictionary.cpp

runner.o: runner.cpp
	${CC} ${CFLAGS} ${INC_PARAMS} -c runner.cpp


clean:
	rm -f lexer *.o

depend:
	makedepend -I. *.c# DO NOT DELETE
