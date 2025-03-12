#include <curses.h>
#include <string.h>

void show_popup(const char *message) {
    int height = 5, width = 30;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;

    WINDOW *popup = newwin(height, width, start_y, start_x);
    box(popup, 0, 0);
    mvwprintw(popup, 2, (width - strlen(message)) / 2, "%s", message);
    wrefresh(popup);
    
    getch();
    delwin(popup);
}

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    refresh();

    printw("Press ENTER to show popup");
    refresh();
    getch();

    show_popup("Hello, this is a pop-up!");

    endwin();
    return 0;
}