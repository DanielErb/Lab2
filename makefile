all: myshell

mypipe: mypipe.o
	gcc -g -Wall -m32 -o mypipe mypipe.o

mypipe.o: mypipe.c
	gcc -g -Wall -m32 -c -o mypipe.o mypipe.c

looper: looper.o
	gcc -g -Wall -m32 -o looper looper.o

myshell: myshell.o LineParser.o
	gcc -g -Wall -m32 -o myshell myshell.o LineParser.o

myshell.o: myshell.c
	gcc -g -Wall -m32 -c -o myshell.o myshell.c

looper.o: looper.c
	gcc -g -Wall -m32 -c -o looper.o looper.c

LineParser.o: LineParser.c
	gcc -g -Wall -m32 -c -o LineParser.o LineParser.c



.PHONY: clean

clean:
	rm -f *.o myshell





