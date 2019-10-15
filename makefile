all: src/main.o src/dinamico.o src/guloso.o src/core.o
	gcc -O3 src/main.o src/dinamico.o src/guloso.o src/core.o -o tp2
	make clean
	clear

dinamico.o: src/dinamico.c includes/dinamico.h
	gcc -O3 -c src/dinamico.c

core.o: src/core.c includes/core.h
	gcc -O3 -c src/core.c

guloso.o: src/guloso.c includes/guloso.h
	gcc -O3 -c src/guloso.c

main.o: src/main.c
	gcc -O3 -c src/main.c

clean:
	rm src/*.o