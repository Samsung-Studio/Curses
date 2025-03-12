#include <curses.h>

#define MENU_ITEMS 4  // Number of menu options

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);  // Enable arrow keys
    refresh();

    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);

    int header_height = 3, header_width = screen_width;
    int sidebar_width = screen_width / 5;
    int content_width = screen_width - sidebar_width;
    int content_height = screen_height - header_height;

    // Create windows
    WINDOW *header = newwin(header_height, header_width, 0, 0);
    WINDOW *sidebar = newwin(content_height, sidebar_width, header_height, 0);
    WINDOW *content = newwin(content_height, content_width, header_height, sidebar_width);

    // Draw initial borders
    box(header, 0, 0);
    box(sidebar, 0, 0);
    box(content, 0, 0);

    // Add header title
    mvwprintw(header, 1, (header_width / 2) - 7, " PDCurses UI ");
    wrefresh(header);
    wrefresh(sidebar);
    wrefresh(content);

    // Menu items (Fixed: Using `const char*`)
    const char *menu_items[MENU_ITEMS] = {"Home", "Settings", "About", "Exit"};
    int selected = 0;  // Currently selected menu item

    int ch;
    while (1) {
        // Clear sidebar and redraw border
        werase(sidebar);
        box(sidebar, 0, 0);
        mvwprintw(sidebar, 1, 2, " MENU "); // Sidebar title

        // Draw menu
        for (int i = 0; i < MENU_ITEMS; i++) {
            if (i == selected) {
                wattron(sidebar, A_REVERSE);  // Highlight selection
                mvwprintw(sidebar, i + 3, 2, "%s", menu_items[i]);
                wattroff(sidebar, A_REVERSE);
            } else {
                mvwprintw(sidebar, i + 3, 2, "%s", menu_items[i]);
            }
        }
        wrefresh(sidebar); // Ensure sidebar updates

        // Handle key input
        ch = getch();
        switch (ch) {
            case KEY_UP:
                selected = (selected == 0) ? MENU_ITEMS - 1 : selected - 1;
                break;
            case KEY_DOWN:
                selected = (selected == MENU_ITEMS - 1) ? 0 : selected + 1;
                break;
            case 'q':  // Quit on 'q'
                endwin();
                return 0;
        }
    }

    endwin();
    return 0;
}

/*
    Attributes -->

    attron() and attroff() are used to apply text attributes like bold, reverse video,
    underline, and colors to printed text.

    Attribute	    Description

    A_BOLD	        Makes text bold
    A_UNDERLINE	    Underlines text
    A_REVERSE	    Reverses foreground and background colors
    A_DIM	        Makes text dim
    A_STANDOUT	    Similar to reverse, highlights text
    A_BLINK	        Makes text blink (might not work in all terminals)
*/