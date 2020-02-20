bytepole.out: bytepole.c
	gcc -std=c99 -Wall -o bytepole bytepole.c

clean:
	rm bytepole.out