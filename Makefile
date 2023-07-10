output: main.o chess.o game.o
	g++ main.o chess.o game.o -o output

main.o: src/main.cpp
	g++ -c src/main.cpp

chess.o: src/lib/chess.cpp src/lib/chess.hpp
	g++ -c src/lib/chess.cpp

game.o: src/lib/game.cpp src/lib/game.hpp
	g++ -c src/lib/game.cpp

clean:
	rm *.o output