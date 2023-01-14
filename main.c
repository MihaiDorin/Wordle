#ifndef _LIB_
#define _LIB_

#include "lib.h"

#endif

int main()
{	
    ITEM **my_items, **items;
	int c, x, y, key, mkey;	
	MENU *main_menu, *menu;
    WINDOW *main_menu_win, *my_win, *menu_win;
    int nitems, i, xi, yi, word_poz, key_poz;
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
	create_menu(choices, &main_menu, &my_items, &main_menu_win, COLOR_PAIR(1), YWIN, XWIN, 
	"Welcome to WORDLE! Press START to begin your adventure", 1, 4, 75, 39, 80, 19, 31, 79);
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
							create_menu(mitems, &menu, &items, &menu_win, COLOR_PAIR(1), YMENU, XMENU, "MENU", 1, 15, 10, 15, 40, 7, 13, 39);
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
											for(i = 0; i < MENU_SIZE; i++){
												free_item(items[i]);}
											goto exit;
										}
										if (strcmp(item_name(curr), "NEW GAME") == 0){
											free(word);
											unpost_menu(menu);
											free_menu(menu);
											for(i = 0; i < MENU_SIZE; i++){
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
								create_menu(mitems, &menu, &items ,&menu_win, COLOR_PAIR(3), YMENU, XMENU, "YOU WON", 1, 15, 10, 15, 40, 7, 13, 39);
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
												for(i = 0; i < MENU_SIZE; i++){
													free_item(items[i]);}
												goto exit;
											}
											if (strcmp(item_name(curr), "NEW GAME") == 0){
												free(word);
												unpost_menu(menu);
												free_menu(menu);
												for(i = 0; i < MENU_SIZE; i++){
													free_item(items[i]);}
												goto newgame;
											}
										}
										default: break;
									}
								}
							}
							if (yi - Y == 10 && strcmp(cuvant, word) != 0){
								create_menu(gitems, &menu, &items, &menu_win, COLOR_PAIR(4), YMENU, XMENU, "GAME OVER", 1, 15, 10, 15, 40, 7, 13, 39);
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
												for(i = 0; i < MENU_SIZE; i++){
													free_item(items[i]);}
												goto exit;
											}
											if (strcmp(item_name(curr), "RETRY") == 0){
												free(word);
												unpost_menu(menu);
												free_menu(menu);
												for(i = 0; i < MENU_SIZE; i++){
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
	for (i = 0; i < MENU_SIZE; i++)
		free_item(my_items[i]);
	endwin();
    return 0;
}