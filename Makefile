CC = g++
CPPFLAGS = -std=c++11 -Wall

default:
	${CC} ${CPPFLAGS} TicTacToe.cpp -o TicTacToe
clean:
	rm -f TicTacToe
new:
	make clean default