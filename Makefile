main.o : main.cc
	g++ main.cc -o main -std=c++11
chip8.o : chip8.cc chip8.h
	g++ chip8.cc -o chip8 -std=c++11
clean :
	rm chip8 main

