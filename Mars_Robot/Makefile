all: robot

run: 
	./robot

robot: matrix.o point.o rover.o Mars_Robot.o
	gcc -o robot Mars_Robot.o matrix.o point.o rover.o

Mars_Robot.o: Mars_Robot.c
	gcc -o Mars_Robot.o -c Mars_Robot.c 

matrix.o: matrix.c
	gcc -o matrix.o -c matrix.c

point.o: point.c
	gcc -o point.o -c point.c

rover.o: rover.c
	gcc -o rover.o -c rover.c