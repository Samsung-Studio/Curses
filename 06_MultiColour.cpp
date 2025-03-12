#include <curses.h>

int main() {
    initscr();
    start_color();

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    
    attron(COLOR_PAIR(1)); printw("Red Text\n"); attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2)); printw("Green Text\n"); attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(3)); printw("Blue Text\n"); attroff(COLOR_PAIR(3));

    getch();
    endwin();
    return 0;
}