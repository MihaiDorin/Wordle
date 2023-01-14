#include <menu.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define XWIN 66
#define YWIN 6
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

void color(WINDOW *win, TASTA *key, char *word, int y, int x, char *k1, char *k2, char *k3){
	int i;
	for (i = 0; i < 5; i++){
		if(tolower(word[i]) == tolower(key[i].name))
			key[i].poz = 2;
		if (aparitie(word, key[i].name) == 0)
			key[i].poz = 0;
		if (aparitie(word, key[i].name) == 1 && tolower(word[i]) != tolower(key[i].name))
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

int main(){	
    ITEM **my_items, **items;
	int c, x, y, key, mkey;	
	MENU *main_menu, *menu;
    WINDOW *main_menu_win, *my_win, *menu_win;
    int n_choices, nitems, i, xi, yi, word_poz, key_poz;
	char *choices[] = {"START GAME", "   QUIT"}, *mitems[] = {"NEW GAME", "  QUIT"}, *word, *gitems[] = {"RETRY", "QUIT"},
	*word_list[] = {"arici", "atent", "baiat", "ceata", "debut", "peste", "fixat", "hamac", "harta", "jalon", "jucam", "lacat", "magie",
	"nufar", "oaste", "perus", "rigle", "roman", "sanie", "scris", "sonda", "texte", "tipar", "titan", "zebra", "vapor", "vatra", "regie", "perie"};
	TASTA tasta[5]; char cuvant[5];
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
    main_menu_win = newwin(39, 80, YWIN, XWIN);
    keypad(main_menu_win, TRUE);
    set_menu_win(main_menu, main_menu_win);
    set_menu_sub(main_menu, derwin(main_menu_win, 2, 15, 19, 31));
    wresize(stdscr, y, x);
	set_menu_mark(main_menu, " > ");
    box(main_menu_win, 0, 0);
	print_in_middle(main_menu_win, 1, 4, 75, "Welcome to WORDLE! Press START to begin your adventure", COLOR_PAIR(1));
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
					curs_set(1);
					my_win = newwin(39, 80, YWIN, XWIN);
					keypad(my_win, TRUE);
					wresize(stdscr, y, x);
					box(my_win, 0, 0);
					print_in_middle(my_win, 1, 35, 8, "WORDLE", COLOR_PAIR(1));
					mvwaddch(my_win, 2, 0, ACS_LTEE);
					mvwhline(my_win, 2, 1, ACS_HLINE, 80);
					mvwaddch(my_win, 2, 79, ACS_RTEE);
					wattron(my_win, COLOR_PAIR(1));
					mvwprintw(my_win, 37, 2, "Press : to open the menu");
					wattroff(my_win, COLOR_PAIR(1));
					char keyboard1[] = {"Q W E R T Y U I O P"}, keyboard2[] = {"A S D F G H J K L"}, keyboard3[] = {"Z X C V B N M"};
					mvwprintw(my_win, Y1, X1, "%s", keyboard1);
					mvwprintw(my_win, Y2, X2, "%s", keyboard2);
					mvwprintw(my_win, Y3, X3, "%s", keyboard3);
					srand(time(NULL));
					word_poz = random_poz(0, ARRAY_SIZE(word_list) - 1);
					word = strdup(word_list[word_poz]);
					yi = Y;
					xi = X;
					key_poz = 0;
					wmove(my_win, yi, xi);
					refresh();
					wrefresh(my_win);
					while(TRUE){
						key = wgetch(my_win);
						if (key == KEY_BACKSPACE){
							if (key_poz > 0)
								key_poz--;
							mvwprintw(my_win, yi, xi + 2 * key_poz, "%c", ' ');
							if (key_poz > 0)
								wmove(my_win, yi, xi + 2 * key_poz);
							if (key_poz == 0)
								wmove(my_win, yi, xi);
						}
						if (key == ':'){
							curs_set(0);
							nitems = ARRAY_SIZE(mitems);
							items = (ITEM **)calloc(nitems, sizeof(ITEM *));
							for(i = 0; i < nitems; i++){
								items[i] = new_item(mitems[i], NULL);
							}
							menu = new_menu((ITEM**)items);
							menu_win = newwin(15, 40, YMENU, XMENU);
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
							wmove(my_win, yi, xi);
						}
						else if (key == 10 && key_poz == 5){
							for (i = 0; i < 5; i++)
								cuvant[i] = tasta[i].name;
							cuvant[key_poz] = 0;
							char keyboard1[] = {"Q W E R T Y U I O P"}, keyboard2[] = {"A S D F G H J K L"}, keyboard3[] = {"Z X C V B N M"};
							color(my_win, tasta, word, yi, xi, keyboard1, keyboard2, keyboard3);
							if (strcmp(cuvant, word) == 0){
								curs_set(0);
								nitems = ARRAY_SIZE(mitems);
								items = (ITEM **)calloc(nitems, sizeof(ITEM *));
								for(i = 0; i < nitems; i++){
									items[i] = new_item(mitems[i], NULL);
								}
								menu = new_menu((ITEM**)items);
								menu_win = newwin(15, 40, YMENU, XMENU);
								keypad(menu_win, TRUE);
								set_menu_win(menu, menu_win);
								set_menu_sub(menu, derwin(menu_win, 2, 15, 7, 13));
								set_menu_mark(menu, " > ");
								box(menu_win, 0, 0);
								print_in_middle(menu_win, 1, 15, 10, "YOU WON", COLOR_PAIR(3));
								mvwaddch(menu_win, 2, 0, ACS_LTEE);
								mvwhline(menu_win, 2, 1, ACS_HLINE, 40);
								mvwaddch(menu_win, 2, 39, ACS_RTEE);
								post_menu(menu);
								refresh();
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
							if (yi - Y == 10 && strcmp(cuvant, word) != 0){
								curs_set(0);
								nitems = ARRAY_SIZE(gitems);
								items = (ITEM **)calloc(nitems, sizeof(ITEM *));
								for(i = 0; i < nitems; i++){
									items[i] = new_item(gitems[i], NULL);
								}
								menu = new_menu((ITEM**)items);
								menu_win = newwin(15, 40, YMENU, XMENU);
								keypad(menu_win, TRUE);
								set_menu_win(menu, menu_win);
								set_menu_sub(menu, derwin(menu_win, 2, 15, 7, 13));
								set_menu_mark(menu, " > ");
								box(menu_win, 0, 0);
								print_in_middle(menu_win, 1, 15, 10, "GAME OVER", COLOR_PAIR(4));
								mvwaddch(menu_win, 2, 0, ACS_LTEE);
								mvwhline(menu_win, 2, 1, ACS_HLINE, 40);
								mvwaddch(menu_win, 2, 39, ACS_RTEE);
								post_menu(menu);
								refresh();
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
											if (strcmp(item_name(curr), "QUIT") == 0){
												free(word);
												unpost_menu(menu);
												free_menu(menu);
												for(i = 0; i < nitems; i++){
													free_item(items[i]);}
												goto exit;
											}
											if (strcmp(item_name(curr), "RETRY") == 0){
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
							key_poz = 0; yi += 2; wmove(my_win, yi, xi);
						}
						else if ((key < 'a' || key > 'z') && (key < 'A' || key > 'Z'))
							continue;
						else{
							if(key_poz >= 5)
								continue;
							if(key_poz < 5){
								tasta[key_poz].name = tolower(key);
								if (key >= 'a' && key <= 'z')
									mvwprintw(my_win, yi, xi + 2 * key_poz, "%c", key - 32);
								if (key >= 'A' && key <= 'Z')
									mvwprintw(my_win, yi, xi + 2 * key_poz, "%c", key);
							}
							key_poz++;
							if (key_poz < 5)
								wmove(my_win, yi, xi + 2 * key_poz);
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