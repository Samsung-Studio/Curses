#include <curses.h>
#include <string.h>

#define TABS 3  // Number of tabs

const char *tab_titles[TABS] = {"Home", "Settings", "About"};

void draw_ui(WINDOW *header, WINDOW *content, int current_tab) {
    werase(header);
    box(header, 0, 0);
    mvwprintw(header, 1, 2, "Tabs: ");

    // Dynamically space tabs based on their lengths
    int start_x = 10;
    for (int i = 0; i < TABS; i++) {
        if (i == current_tab) {
            wattron(header, A_REVERSE);
            mvwprintw(header, 1, start_x, "[ %s ]", tab_titles[i]);
            wattroff(header, A_REVERSE);
        } else {
            mvwprintw(header, 1, start_x, "[ %s ]", tab_titles[i]);
        }
        start_x += strlen(tab_titles[i]) + 6;  // Adjust spacing dynamically
    }
    wrefresh(header);

    werase(content);
    box(content, 0, 0);
    mvwprintw(content, 1, 2, "Current Tab: %s", tab_titles[current_tab]);
    
    switch (current_tab) {
        case 0:
            mvwprintw(content, 3, 2, "Welcome to the Home tab!");
            break;
        case 1:
            mvwprintw(content, 3, 2, "Adjust your settings here.");
            break;
        case 2:
            mvwprintw(content, 3, 2, "This is the About section.");
            break;
    }
    wrefresh(content);
}

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    refresh();

    int height, width;
    getmaxyx(stdscr, height, width);
    
    int header_height = 3;
    int content_height = height - header_height;
    
    WINDOW *header = newwin(header_height, width, 0, 0);
    WINDOW *content = newwin(content_height, width, header_height, 0);

    int current_tab = 0;
    draw_ui(header, content, current_tab);

    int ch;
    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_LEFT:
                if (current_tab > 0) current_tab--;
                break;
            case KEY_RIGHT:
                if (current_tab < TABS - 1) current_tab++;
                break;
        }
        draw_ui(header, content, current_tab);
    }

    delwin(header);
    delwin(content);
    endwin();
    return 0;
}