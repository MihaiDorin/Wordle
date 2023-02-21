/*	
	Author: Pacuraru Mihai Dorin
	Faculty of Automatic Control and Computer Science,
	Polytechnic University of Bucharest
*/

#ifndef __LIB_H__
#define __LIB_H__

#include <menu.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define MENU_SIZE 2
#define XWIN 66
#define YWIN 7
#define XMENU 86
#define YMENU 16
#define X 34
#define Y 11
#define Y1 31
#define Y2 32
#define Y3 33
#define X1 30
#define X2 31
#define X3 33

typedef struct {
	char name;
	int poz;
} TASTA;

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

int random_pos(int lower, int upper);

int find(char *word, char c);

void color_keyboard(WINDOW *win, char *k1, char *k2, char *k3, char key, chtype color);

void colorc(WINDOW *win, TASTA *key, char *word, int y, int x, char *k1, char *k2, char *k3);

void create_menu(char **choices, MENU **main_menu, ITEM ***my_items, WINDOW **win, chtype color, 
int ywin, int xwin, char *s, int ys, int xs, int slen, int nlines, int ncols, int y, int x, int chx);

void create_win(WINDOW **my_win, int *yi, int *xi, int *key_poz);

#endif // __LIB_H__
