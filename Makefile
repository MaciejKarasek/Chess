output: Piece.o Field.o Board.o game.o main.o
	g++ -std=c++20 main.o Piece.o Field.o Board.o game.o -o output

main.o: src/main.cpp
	g++ -std=c++20 -c src/main.cpp

game.o: src/lib/game.cpp src/lib/game.hpp
	g++ -std=c++20 -c src/lib/game.cpp
	
Board.o: src/lib/Board.cpp src/lib/Board.hpp
	g++ -std=c++20 -c src/lib/Board.cpp

Field.o: src/lib/Field.cpp src/lib/Field.hpp
	g++ -std=c++20 -c src/lib/Field.cpp

Piece.o: src/lib/Piece.cpp src/lib/Piece.hpp
	g++ -std=c++20 -c src/lib/Piece.cpp

clean:
	rm *.o output*