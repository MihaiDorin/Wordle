all: build

build: bin bin/wordle

bin/wordle : bin/main.o bin/func.o
	gcc -o bin/wordle bin/main.o bin/func.o src/lib.h -lncurses -lmenu

bin/main.o: src/main.c
	gcc -c src/main.c -g -Wall -o bin/main.o

bin/func.o: src/func.c
	gcc -c src/func.c -g -Wall -o bin/func.o

bin:
	mkdir bin

run:
	xterm -fa 'Monospace' -fs 10 -maximized -e ./bin/wordle &

.PHONY: clean

clean:
	rm -rf bin