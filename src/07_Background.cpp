#include <curses.h>

int main() {
    initscr();
    start_color();
    
    init_pair(1, COLOR_WHITE, COLOR_BLUE);  // White text on Blue background
    bkgd(COLOR_PAIR(1));  // Apply background color

    printw("This is a full-screen colored UI!");
    refresh();

    getch();
    endwin();
    return 0;
}