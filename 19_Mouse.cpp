#include <curses.h>
#include <stdio.h>

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    printf("\033[?1002h"); fflush(stdout); // Enable terminal mouse reporting

    if (!has_mouse()) {
        printw("Mouse not supported!");
        refresh();
        getch();
        endwin();
        return 1;
    }

    mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED | REPORT_MOUSE_POSITION, NULL); // ✅ Ensure clicks are captured

    printw("Click anywhere! Press 'q' to exit.");
    refresh();

    int ch, btn, x, y;
    while ((ch = getch()) != 'q') {
        if (ch == KEY_MOUSE) {
            MEVENT event;
            if (getmouse() == OK) {
                btn = event.bstate;
                x = event.x;
                y = event.y;
            }
            mvprintw(LINES - 3, 2, "Mouse Click at (%d, %d)", x, y);
            refresh();
        }
    }

    printf("\033[?1002l");
    fflush(stdout); // Disable mouse reporting before exit
    endwin();
    return 0;
}