bytepole.out: bytepole.c
	gcc -std=c99 -Wall -o bytepole.out bytepole.c

clean:
	rm bytepole.out