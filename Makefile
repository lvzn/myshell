wish: main.o
	gcc main.o -o wish -Wall

main.o: main.c
	gcc -Wall -c main.c

clean:
	rm *.o wish
