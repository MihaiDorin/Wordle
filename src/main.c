/*	
	Author: Pacuraru Mihai Dorin
	Faculty of Automatic Control and Computer Science,
	Polytechnic University of Bucharest
*/

#include "lib.h"

int main()
{	
    ITEM **my_items, **items, *curr;
	int c, key, mkey;
	MENU *main_menu, *menu;
    WINDOW *main_menu_win, *my_win, *menu_win;
    int i, xi, yi, word_pos, key_pos;
	char *choices[] = {"START GAME", "   QUIT"}, *mitems[] = {"NEW GAME", "  QUIT"}, *word, *gitems[] = {"RETRY", "QUIT"},
	*word_list[] = {"adult", "apple", "award", "beach", "brain", "bread", "chair", "child", "class", "dream", "dress", "drink", "earth", "event",
	"field", "floor", "frame", "grass","group","heart", "horse", "hotel", "house", "image", "index", "input", "level", "light", "lunch", "model",
	"music","night", "novel", "nurse", "offer", "owner", "paper", "party", "peace", "phone", "queen", "radio", "river", "route", "score", "sheep",
	"sheet", "title", "tower", "track", "uncle", "unity", "value", "video", "voice", "waste", "watch", "water", "youth"};
	TASTA tasta[5]; char cuvant[6], keyboard1[] = {"Q W E R T Y U I O P"}, keyboard2[] = {"A S D F G H J K L"}, keyboard3[] = {"Z X C V B N M"};

	initscr();
	keypad(stdscr, TRUE);
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
        switch(c){	
				case KEY_DOWN:
					menu_driver(main_menu, REQ_DOWN_ITEM);
					break;

				case KEY_UP:
					menu_driver(main_menu, REQ_UP_ITEM);
					break;

            	case 10:
					curr = current_item(main_menu);
					pos_menu_cursor(main_menu);

					if (strcmp(item_name(curr), "   QUIT") == 0)
						goto exit;

					if (strcmp(item_name(curr), "START GAME") == 0){
						newgame:
						create_win(&my_win, &yi, &xi, &key_pos);

						srand(time(NULL));
						word_pos = random_pos(0, ARRAY_SIZE(word_list) - 1);
						word = strdup(word_list[word_pos]);

						while(TRUE){
							key = wgetch(my_win);
							if (key == KEY_BACKSPACE){
								if (key_pos > 0)
									key_pos--;
								
								mvwprintw(my_win, yi, xi + 2 * key_pos, "%c", ' ');

								if (key_pos > 0)
									wmove(my_win, yi, xi + 2 * key_pos);
								
								if (key_pos == 0)
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
							if (key == 10 && key_pos != 5){
								for (i = 0; i < key_pos; i++)
									mvwprintw(my_win, yi, xi + 2 * i, "%c", ' ');
								
								key_pos = 0;
								wmove(my_win, yi, xi);
							}
							else if (key == 10 && key_pos == 5){
								for (i = 0; i < 5; i++)
									cuvant[i] = tasta[i].name;
								cuvant[key_pos] = 0;
								colorc(my_win, tasta, word, yi, xi, keyboard1, keyboard2, keyboard3);

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
									mvwprintw(menu_win, 5, 10, "The word was \"%s\"", word);
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
								key_pos = 0; yi += 2; wmove(my_win, yi, xi);
							}
							else if ((key < 'a' || key > 'z') && (key < 'A' || key > 'Z'))
								continue;
							else{
								if(key_pos >= 5)
									continue;
								if(key_pos < 5){
									tasta[key_pos].name = tolower(key);
									if (key >= 'a' && key <= 'z')
										mvwprintw(my_win, yi, xi + 2 * key_pos, "%c", key - 32);
									if (key >= 'A' && key <= 'Z')
										mvwprintw(my_win, yi, xi + 2 * key_pos, "%c", key);
								}

								key_pos++;
								if (key_pos < 5)
									wmove(my_win, yi, xi + 2 * key_pos);
							}
						}
						goto exit;
					}
					break;

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