all: main.o data.o
	gcc -o main main.o data.o

run: 
	./main

main.o: main.c
	gcc -o main.o -c main.c

data.o: data.c
	gcc -o data.o -c data.c