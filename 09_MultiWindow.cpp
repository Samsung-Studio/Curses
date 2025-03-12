#include <curses.h>

int main() {
    initscr();          // Initialize PDCurses
    noecho();           // Don't echo user input
    curs_set(0);        // Hide the cursor
    refresh();

    // Create two windows
    WINDOW *win1 = newwin(10, 30, 3, 5);   // Height, Width, Start Y, Start X
    WINDOW *win2 = newwin(10, 30, 3, 40);

    // Draw borders for both windows
    box(win1, 0, 0);
    box(win2, 0, 0);

    // Print text inside each window
    mvwprintw(win1, 1, 1, "Window 1");
    mvwprintw(win2, 1, 1, "Window 2");

    // Refresh both windows
    wrefresh(win1);
    wrefresh(win2);

    getch();  // Wait for key press before exiting
    endwin(); // Restore terminal
    return 0;
}