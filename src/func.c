/*	
	Author: Pacuraru Mihai Dorin
	Faculty of Automatic Control and Computer Science,
	Polytechnic University of Bucharest
*/

#include "lib.h"

// print in middle of a window the string
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color){	
    int length, x, y;
	float temp;
	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

// generate a random position
int random_pos(int lower, int upper){
    int num;
	num = (rand() % (upper - lower + 1)) + lower;
	return num;
}

// search the character c in word
int find(char *word, char c){
	int i;
	for (i = 0; i < strlen(word); i++)
		if (word[i] == c)
			return 1;
	return 0;
}

// colors the keyboard based on letter position in word
void color_keyboard(WINDOW *win, char *k1, char *k2, char *k3, char key, chtype color){
	int i;
	for (i = 0; i < strlen(k1); i++)
		if (tolower(k1[i]) == tolower(key)){
			wattron(win, color);
			if (key >= 'a' && key <= 'z')
				mvwprintw(win, Y1, X1 + i, "%c", key - 32);
			if (key >= 'A' && key <= 'Z')
				mvwprintw(win, Y1, X1 + i, "%c", key);
			wattroff(win, color);
			wrefresh(win);
		}
	for (i = 0; i < strlen(k2); i++)
		if (tolower(k2[i]) == tolower(key)){
			wattron(win, color);
			if (key >= 'a' && key <= 'z')
				mvwprintw(win, Y2, X2 + i, "%c", key - 32);
			if (key >= 'A' && key <= 'Z')
				mvwprintw(win, Y2, X2 + i, "%c", key);
			wattroff(win, color);
			wrefresh(win);
		}
	for (i = 0; i < strlen(k3); i++)
		if (tolower(k3[i]) == tolower(key)){
			wattron(win, color);
			if (key >= 'a' && key <= 'z')
				mvwprintw(win, Y3, X3 + i, "%c", key - 32);
			if (key >= 'A' && key <= 'Z')
				mvwprintw(win, Y3, X3 + i, "%c", key);
			wattroff(win, color);
			refresh();
			wrefresh(win);
		}
}

// color the word
void colorc(WINDOW *win, TASTA *key, char *word, int y, int x, char *k1, char *k2, char *k3){
	int i;
	for (i = 0; i < 5; i++){
		if(tolower(word[i]) == tolower(key[i].name))
			key[i].poz = 2;
		if (find(word, key[i].name) == 0)
			key[i].poz = 0;
		if (find(word, key[i].name) == 1 && tolower(word[i]) != tolower(key[i].name))
			key[i].poz = 1;
	}
	for (i = 0; i < 5; i++){
		if(key[i].poz == 0){
			color_keyboard(win, k1, k2, k3, key[i].name, COLOR_PAIR(4));
			wattron(win, COLOR_PAIR(4));
			if(key[i].name >= 'A' && key[i].name <= 'Z')
				mvwprintw(win, y, x + 2 * i, "%c", key[i].name);
			if(key[i].name >= 'a' && key[i].name <= 'z')
				mvwprintw(win, y, x + 2 * i, "%c", key[i].name - 32);
			wattroff(win, COLOR_PAIR(4));
		}
		if(key[i].poz == 1){
			color_keyboard(win, k1, k2, k3, key[i].name, COLOR_PAIR(2));
			wattron(win, COLOR_PAIR(2));
			if(key[i].name >= 'A' && key[i].name <= 'Z')
				mvwprintw(win, y, x + 2 * i, "%c", key[i].name);
			if(key[i].name >= 'a' && key[i].name <= 'z')
				mvwprintw(win, y, x + 2 * i, "%c", key[i].name - 32);
			wattroff(win, COLOR_PAIR(2));
		}
		if(key[i].poz == 2){
			color_keyboard(win, k1, k2, k3, key[i].name, COLOR_PAIR(3));
			wattron(win, COLOR_PAIR(3));
			if(key[i].name >= 'A' && key[i].name <= 'Z')
				mvwprintw(win, y, x + 2 * i, "%c", key[i].name);
			if(key[i].name >= 'a' && key[i].name <= 'z')
				mvwprintw(win, y, x + 2 * i, "%c", key[i].name - 32);
			wattroff(win, COLOR_PAIR(3));
		}
	}
	wrefresh(win);
}

// create a new menu
void create_menu(char **choices, MENU **main_menu, ITEM ***my_items, WINDOW **win, chtype color, 
int ywin, int xwin, char *s, int ys, int xs, int slen, int nlines, int ncols, int y, int x, int chx)
{
	int i;
    curs_set(0);
    *my_items = (ITEM **)calloc(MENU_SIZE, sizeof(ITEM *));
    for(i = 0; i < MENU_SIZE; i++){
        (*my_items)[i] = new_item(choices[i], NULL);
    }
	*main_menu = new_menu((ITEM **)*my_items);
    *win = newwin(nlines, ncols, ywin, xwin);
    keypad(*win, TRUE);
    set_menu_win(*main_menu, *win);
    set_menu_sub(*main_menu, derwin(*win, 2, 15, y, x));
	set_menu_mark(*main_menu, " > ");
    box(*win, 0, 0);
	print_in_middle(*win, ys, xs, slen, s, color);
	mvwaddch(*win, 2, 0, ACS_LTEE);
	mvwhline(*win, 2, 1, ACS_HLINE, 80);
	mvwaddch(*win, 2, chx, ACS_RTEE);
	post_menu(*main_menu);
	wrefresh(*win);
	refresh();
}

// create a new window
void create_win(WINDOW **my_win, int *yi, int *xi, int *key_poz)
{
	curs_set(1);
	*my_win = newwin(39, 80, YWIN, XWIN);
	keypad(*my_win, TRUE);
	box(*my_win, 0, 0);
	print_in_middle(*my_win, 1, 35, 8, "WORDLE", COLOR_PAIR(1));
	mvwaddch(*my_win, 2, 0, ACS_LTEE);
	mvwhline(*my_win, 2, 1, ACS_HLINE, 80);
	mvwaddch(*my_win, 2, 79, ACS_RTEE);
	wattron(*my_win, COLOR_PAIR(1));
	mvwprintw(*my_win, 37, 2, "Press : to open the menu");
	wattroff(*my_win, COLOR_PAIR(1));
	char keyboard1[] = {"Q W E R T Y U I O P"}, keyboard2[] = {"A S D F G H J K L"}, keyboard3[] = {"Z X C V B N M"};
	mvwprintw(*my_win, Y1, X1, "%s", keyboard1);
	mvwprintw(*my_win, Y2, X2, "%s", keyboard2);
	mvwprintw(*my_win, Y3, X3, "%s", keyboard3);
	*yi = Y;
	*xi = X;
	*key_poz = 0;
	wmove(*my_win, *yi, *xi);
	refresh();
	wrefresh(*my_win);
}