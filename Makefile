COMPILER = g
COMPILER_FLAG = -std=c++23

output: Piece.o Field.o Board.o game.o main.o
	g++-10 main.o Piece.o Field.o Board.o game.o ${COMPILER_FLAG} -o output

main.o: src/main.cpp
	${COMPILER} -c ${COMPILER_FLAG} src/main.cpp

game.o: src/lib/game.cpp src/lib/game.hpp
	${COMPILER} -c ${COMPILER_FLAG} src/lib/game.cpp
	
Board.o: src/lib/Board.cpp src/lib/Board.hpp
	${COMPILER} -c ${COMPILER_FLAG} src/lib/Board.cpp

Field.o: src/lib/Field.cpp src/lib/Field.hpp
	${COMPILER} -c ${COMPILER_FLAG} src/lib/Field.cpp

Piece.o: src/lib/Piece.cpp src/lib/Piece.hpp
	${COMPILER} -c ${COMPILER_FLAG} src/lib/Piece.cpp

clean:
	rm *.o output*