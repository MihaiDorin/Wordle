#include <menu.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define X 34
#define Y 11
#define Y1 31
#define Y2 32
#define Y3 33
#define X1 30
#define X2 31
#define X3 33

typedef struct{
	char name;
	int poz;
}TASTA;

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

int random_poz(int lower, int upper){
    int num;
	num = (rand() % (upper - lower + 1)) + lower;
	return num;
}

int aparitie (char *word, char c){
	int i;
	for (i = 0; i < strlen(word); i++)
		if (word[i] == c)
			return 1;
	return 0;
}

void color_keyboard(WINDOW *win, char *k1, char *k2, char *k3, char key){
	int i;
	for (i = 0; i < strlen(k1); i++)
		if (tolower(k1[i]) == tolower(key)){
			wattron(win, COLOR_PAIR(1));
			if (key >= 'a' && key <= 'z')
				mvwprintw(win, Y1, X1 + i, "%c", key - 32);
			if (key >= 'A' && key <= 'Z')
				mvwprintw(win, Y1, X1 + i, "%c", key);
			wattroff(win, COLOR_PAIR(1));
			wrefresh(win);
		}
	for (i = 0; i < strlen(k2); i++)
		if (tolower(k2[i]) == tolower(key)){
			wattron(win, COLOR_PAIR(1));
			if (key >= 'a' && key <= 'z')
				mvwprintw(win, Y2, X2 + i, "%c", key - 32);
			if (key >= 'A' && key <= 'Z')
				mvwprintw(win, Y2, X2 + i, "%c", key);
			wattroff(win, COLOR_PAIR(1));
			wrefresh(win);
		}
	for (i = 0; i < strlen(k3); i++)
		if (tolower(k3[i]) == tolower(key)){
			wattron(win, COLOR_PAIR(1));
			if (key >= 'a' && key <= 'z')
				mvwprintw(win, Y3, X3 + i, "%c", key - 32);
			if (key >= 'A' && key <= 'Z')
				mvwprintw(win, Y3, X3 + i, "%c", key);
			wattroff(win, COLOR_PAIR(1));
			wrefresh(win);
		}
}

int main(){	
    ITEM **my_items, **items;
	int c, x, y, key, mkey;	
	MENU *main_menu, *menu;
    WINDOW *main_menu_win, *my_win, *menu_win;
    int n_choices, nitems, i, j, xi, yi, word_poz, key_poz;
	char *choices[] = {"START GAME", "   QUIT"}, *mitems[] = {"NEW GAME", "  QUIT"}, *word, *gitems[] = {"RETRY", "QUIT"},
	keyboard1[] = {"Q W E R T Y U I O P"}, keyboard2[] = {"A S D F G H J K L"}, keyboard3[] = {"Z X C V B N M"},
	*word_list[] = {"arici", "atent", "baiat", "ceata", "debut", "peste", "fixat", "hamac", "harta", "jalon", "jucam", "lacat", "magie",
	"nufar", "oaste", "perus", "rigle", "roman", "sanie", "scris", "sonda", "texte", "tipar", "titan", "zebra", "vapor", "vatra", "regie"};
	TASTA tasta[5];
	initscr();
	keypad(stdscr, TRUE);
    getmaxyx(stdscr, y, x);
	start_color();
	raw();
    cbreak();
    noecho();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
    for(i = 0; i < n_choices; i++){
        my_items[i] = new_item(choices[i], NULL);
    }
	main_menu = new_menu((ITEM **)my_items);
    main_menu_win = newwin(39, 80, 6, 53);
    keypad(main_menu_win, TRUE);
    set_menu_win(main_menu, main_menu_win);
    set_menu_sub(main_menu, derwin(main_menu_win, 2, 15, 19, 31));
    wresize(stdscr, y, x);
	set_menu_mark(main_menu, " > ");
    box(main_menu_win, 0, 0);
	print_in_middle(main_menu_win, 1, 4, 70, "Welcome to WORDLE! Press START to begin your adventure", COLOR_PAIR(1));
	mvwaddch(main_menu_win, 2, 0, ACS_LTEE);
	mvwhline(main_menu_win, 2, 1, ACS_HLINE, 80);
	mvwaddch(main_menu_win, 2, 79, ACS_RTEE);
	refresh();
	post_menu(main_menu);
	wrefresh(main_menu_win);
    curs_set(0);
	while(TRUE)
	{       
		c = wgetch(main_menu_win);
        switch(c)
	        {	case KEY_DOWN:
				menu_driver(main_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(main_menu, REQ_UP_ITEM);
				break;
            case 10:{
				ITEM *curr;
				curr = current_item(main_menu);
				pos_menu_cursor(main_menu);
				if (strcmp(item_name(curr), "   QUIT") == 0)
					goto exit;
				if (strcmp(item_name(curr), "START GAME") == 0){
					newgame:
					my_win = newwin(39, 80, 6, 53);
					keypad(my_win, TRUE);
					wresize(stdscr, y, x);
					box(my_win, 0, 0);
					print_in_middle(my_win, 1, 4, 70, "WORDLE", COLOR_PAIR(1));
					mvwaddch(my_win, 2, 0, ACS_LTEE);
					mvwhline(my_win, 2, 1, ACS_HLINE, 80);
					mvwaddch(my_win, 2, 79, ACS_RTEE);
					wattron(my_win, COLOR_PAIR(1));
					mvwprintw(my_win, 37, 2, "Press : to open the menu");
					wattroff(my_win, COLOR_PAIR(1));
					mvwprintw(my_win, Y1, X1, "%s", keyboard1);
					mvwprintw(my_win, Y2, X2, "%s", keyboard2);
					mvwprintw(my_win, Y3, X3, "%s", keyboard3);
					srand(time(NULL));
					word_poz = random_poz(0, ARRAY_SIZE(word_list) - 1);
					word = strdup(word_list[word_poz]);
					mvwprintw(my_win, 4, 30, "%s", word);
					yi = Y;
					xi = X;
					key_poz = 0;
					refresh();
					wrefresh(my_win);
					while(TRUE){
						key = wgetch(my_win);
						if (key == ':'){
							nitems = ARRAY_SIZE(mitems);
							items = (ITEM **)calloc(nitems, sizeof(ITEM *));
							for(i = 0; i < nitems; i++){
								items[i] = new_item(mitems[i], NULL);
							}
							menu = new_menu((ITEM**)items);
							menu_win = newwin(15, 40, 16, 73);
							keypad(menu_win, TRUE);
							set_menu_win(menu, menu_win);
							set_menu_sub(menu, derwin(menu_win, 2, 15, 7, 13));
							set_menu_mark(menu, " > ");
							box(menu_win, 0, 0);
							print_in_middle(menu_win, 1, 15, 10, "MENU", COLOR_PAIR(1));
							mvwaddch(menu_win, 2, 0, ACS_LTEE);
							mvwhline(menu_win, 2, 1, ACS_HLINE, 40);
							mvwaddch(menu_win, 2, 39, ACS_RTEE);
							post_menu(menu);
							wrefresh(menu_win);
							while (TRUE){
								mkey = wgetch(menu_win);
								switch (mkey){
									case KEY_DOWN:
										menu_driver(menu, REQ_DOWN_ITEM);
										break;
									case KEY_UP:
										menu_driver(menu, REQ_UP_ITEM);
										break;
									case 10: {
										curr = current_item(menu);
										pos_menu_cursor(menu);
										if (strcmp(item_name(curr), "  QUIT") == 0){
											free(word);
											unpost_menu(menu);
											free_menu(menu);
											for(i = 0; i < nitems; i++){
												free_item(items[i]);}
											goto exit;
										}
										if (strcmp(item_name(curr), "NEW GAME") == 0){
											free(word);
											unpost_menu(menu);
											free_menu(menu);
											for(i = 0; i < nitems; i++){
												free_item(items[i]);}
											goto newgame;
										}
									}
									default: break;
								}
							}
						}
						if (key == 10 && key_poz != 5){
							for (i = 0; i < key_poz; i++)
								mvwprintw(my_win, yi, xi + 2 * i, "%c", ' ');
							key_poz = 0;
						}
						else if (key == 10 && key_poz == 5){
							
							for (i = 0; i < key_poz; i++){
							
							}
							key_poz = 0; yi += 2;
						}
						else{
							if(key_poz >= 5)
								continue;
							tasta[key_poz].name = key;
							if(key_poz < 5){
								color_keyboard(my_win, keyboard1, keyboard2, keyboard3, key);
								if (key >= 'a' && key <= 'z')
									mvwprintw(my_win, yi, xi + 2 * key_poz, "%c", key - 32);
								if (key >= 'A' && key <= 'Z')
									mvwprintw(my_win, yi, xi + 2 * key_poz, "%c", key);
							}
							key_poz++;
						}
					}
					goto exit;
				}
				break;
                }
			default: break;
            }
        wrefresh(main_menu_win);
	}
	exit:
    unpost_menu(main_menu);
    free_menu(main_menu);
    for(i = 0; i < n_choices; i++){
        free_item(my_items[i]);}
	endwin();
    return 0;
}