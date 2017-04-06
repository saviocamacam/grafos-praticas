all:
	gcc -c graphlib.c
	gcc main.c graphlib.o
	./a.out
