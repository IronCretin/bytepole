bytepole.out: bytepole.c
	gcc -std=c99 -Wall -o bytepole.out bytepole.c -lreadline

clean:
	rm bytepole.out
