all: src/main.c
	gcc -o miniSQL src/main.c -Wall `pkg-config --cflags --libs gtk+-3.0`

run:
	./miniSQL