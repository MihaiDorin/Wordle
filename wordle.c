#include <menu.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

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

int main(){	
    ITEM **my_items, **items;
	int c, x, y, key, mkey;	
	MENU *main_menu, *menu;
    WINDOW *main_menu_win, *my_win, *menu_win;
    int n_choices, nitems, i;
	char *choices[] = {"START GAME", "   QUIT"}, *mitems[] = {"NEW GAME", "  QUIT"}, *p;
	/* Initialize curses */
	initscr();
	keypad(stdscr, TRUE);
    getmaxyx(stdscr, y, x);
	start_color();
	raw();
    cbreak();
    noecho();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);

	/* Create items */
    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
    for(i = 0; i < n_choices; i++){
        my_items[i] = new_item(choices[i], NULL);
    }
	/* Crate menu */
	main_menu = new_menu((ITEM **)my_items);

	/* Create the window to be associated with the menu */
    main_menu_win = newwin(39, 80, 6, 53);
    keypad(main_menu_win, TRUE);
     
	/* Set main window and sub window */
    set_menu_win(main_menu, main_menu_win);
    set_menu_sub(main_menu, derwin(main_menu_win, 2, 15, 19, 31));

    wresize(stdscr, y, x);

	/* Set menu mark to the string */ 
	set_menu_mark(main_menu, " > ");

    /* Print a border around the main window and print a title */
    box(main_menu_win, 0, 0);
	print_in_middle(main_menu_win, 1, 4, 70, "Welcome to WORDLE! Press START to begin your adventure", COLOR_PAIR(1));
	mvwaddch(main_menu_win, 2, 0, ACS_LTEE);
	mvwhline(main_menu_win, 2, 1, ACS_HLINE, 80);
	mvwaddch(main_menu_win, 2, 79, ACS_RTEE);
	refresh();
        
	/* Post the menu */
	post_menu(main_menu);
	wrefresh(main_menu_win);

    curs_set(0);

	p = (char *)malloc(2 * sizeof(char));
	p[1] = 0;

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
				if (strcmp(item_name(curr), "START GAME") == 0)
				{
					newgame:
					my_win = newwin(39, 80, 6, 53);
					keypad(my_win, TRUE);
					wresize(stdscr, y, x);
					box(my_win, 0, 0);
					print_in_middle(my_win, 1, 4, 70, "WORDLE", COLOR_PAIR(1));
					mvwaddch(my_win, 2, 0, ACS_LTEE);
					mvwhline(my_win, 2, 1, ACS_HLINE, 80);
					mvwaddch(my_win, 2, 79, ACS_RTEE);
					mvwprintw(my_win, 37, 2, "Press : to open the menu");
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
							/* Set main window and sub window */
							set_menu_win(menu, menu_win);
							set_menu_sub(menu, derwin(menu_win, 2, 15, 7, 13));
							/* Set menu mark to the string */ 
							set_menu_mark(menu, " > ");
							/* Print a border around the main window and print a title */
							box(menu_win, 0, 0);
							print_in_middle(menu_win, 1, 15, 10, "MENU", COLOR_PAIR(1));
							mvwaddch(menu_win, 2, 0, ACS_LTEE);
							mvwhline(menu_win, 2, 1, ACS_HLINE, 40);
							mvwaddch(menu_win, 2, 39, ACS_RTEE);
							/* Post the menu */
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
											goto exit;
											unpost_menu(menu);
											free_menu(menu);
											for(i = 0; i < nitems; i++){
												free_item(items[i]);}
										}
										if (strcmp(item_name(curr), "NEW GAME") == 0){
											goto newgame;
											unpost_menu(menu);
											free_menu(menu);
											for(i = 0; i < nitems; i++){
												free_item(items[i]);}
										}
									}
									default: break;
								}
							}
						}
						else{
							p[0] = key;
							
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