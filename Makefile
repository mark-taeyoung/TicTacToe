CC = g++
CPPFLAGS = -std=c++11 -Wall

TicTacToeRand:
	${CC} ${CPPFLAGS} TicTacToeRand.cpp -o TicTacToeRand

TicTacToeAi:
	${CC} ${CPPFLAGS} TicTacToeAi.cpp -o TicTacToeAi

clean:
	rm -f TicTacToeRand TicTacToeAi
new:
	make clean TicTacToeRand TicTacToeAi