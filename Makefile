all: build

build: wordle

wordle : main.o func.o
	gcc -o wordle main.o func.o lib.h -lncurses -lmenu

main.o: main.c
	gcc -c main.c -g -Wall -o main.o

func.o: func.c
	gcc -c func.c -g -Wall -o func.o

run:
	xterm -fa 'Monospace' -fs 10 -maximized -e ./wordle &

.PHONY: clean

clean:
	rm -f main.o func.o wordle