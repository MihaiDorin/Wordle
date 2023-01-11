all: wordle

wordle: 
	gcc wordle.c -g -Wall -lncurses -lmenu -o wordle

clean: 
	rm wordle

run:
	gnome-terminal -- bash -c "./wordle; exec bash"
