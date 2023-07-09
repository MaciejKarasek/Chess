output: main.o chess.o
	g++ main.o chess.o -o output

main.o: src/main.cpp
	g++ -c src/main.cpp

chess.o: src/lib/chess.cpp src/lib/chess.hpp
	g++ -c src/lib/chess.cpp

clean:
	rm *.o output