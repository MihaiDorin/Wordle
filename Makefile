all: wordle

wordle: 
	gcc main.c func.c -g -Wall -lncurses -lmenu -o wordle

clean: 
	rm wordle

run:
	xterm -fa 'Monospace' -fs 10 -maximized ./wordle
