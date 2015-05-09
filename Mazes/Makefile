#The compiler is g++ for compiling c++.
CC=g++

CFLAGS=-std=c++11 -pthread -g


all: mgen

mgen: main.cpp include/* src/*
	$(CC) $(CFLAGS) -o mgen main.cpp src/*

#	g++ -std=c++11  -pthread -g -o mgen main.cpp src/*


clean:
	rm mgen

