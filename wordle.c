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
    ITEM **my_items;
	int c, x, y;				
	MENU *my_menu;
    WINDOW *my_menu_win;
    int n_choices, i;
	char *choices[] = {"START JOC", "IESIRE JOC"};
	/* Initialize curses */
	initscr();
    getmaxyx(stdscr, y, x);
	start_color();
    cbreak();
    noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_CYAN, COLOR_BLACK);

	/* Create items */
    n_choices = ARRAY_SIZE(choices);
    my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
    for(i = 0; i < n_choices; i++){
        my_items[i] = new_item(choices[i], NULL);
    }
	/* Crate menu */
	my_menu = new_menu((ITEM **)my_items);

	/* Create the window to be associated with the menu */
    my_menu_win = newwin(20, 80, 16, 53);
    keypad(my_menu_win, TRUE);
     
	/* Set main window and sub window */
    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win, 2, 20, 9, 30));

    wresize(stdscr, y, x);

	/* Set menu mark to the string */
	set_menu_mark(my_menu, " < ");
	set_menu_format(my_menu, 2, 1); 
    /* Print a border around the main window and print a title */
    box(my_menu_win, 0, 0);
	print_in_middle(my_menu_win, 1, 4, 70, "BUN VENIT LA WORDLE! APASA START PENTRU A INCEPE JOCUL", COLOR_PAIR(1));
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 80);
	mvwaddch(my_menu_win, 2, 79, ACS_RTEE);
	refresh();
        
	/* Post the menu */
	post_menu(my_menu);
	wrefresh(my_menu_win);

    curs_set(0);

	while(TRUE)
	{       
		c = wgetch(my_menu_win);
        switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
            case 10:
                {	ITEM *curr;
                    curr = current_item(my_menu);
                    pos_menu_cursor(my_menu);
					if (strcmp(item_name(curr), "IESIRE JOC") == 0)
						goto exit;
					if (strcmp(item_name(curr), "START JOC") == 0){
						
					}
                    break;
                }
			default: break;
            }
        wrefresh(my_menu_win);
	}
	exit:
	/* Unpost and free all the memory taken up */
    unpost_menu(my_menu);
    free_menu(my_menu);
    for(i = 0; i < n_choices; i++){
        free_item(my_items[i]);}
	endwin();
    return 0;
}