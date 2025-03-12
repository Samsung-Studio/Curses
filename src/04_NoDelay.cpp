#include <curses.h>

int main() {
    initscr();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);  // Non-blocking mode
    noecho();

    printw("Press 'q' to exit...\n");
    refresh();

    int ch;
    while ((ch = getch()) != 'q') {
        if (ch != ERR) {  // Only process valid key presses
            printw("You pressed: %c\n", ch);
            refresh();
        }
    }

    endwin();
    return 0;
}