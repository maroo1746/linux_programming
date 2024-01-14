main: main.o print.o word.o
	gcc -o main main.o print.o word.o
main.o: main.c print.h word.h
	gcc -c main.c
print.o: print.c
	gcc -c print.c
word.o: word.c
	gcc -c word.c
