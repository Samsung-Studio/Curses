#include <curses.h>

int main() {
    initscr();           // Initialize screen
    refresh();           // Refresh to make changes visible

    WINDOW *win = newwin(10, 30, 5, 10);  // Create a window
    box(win, 0, 0);      // Draw a border around the window
    mvwprintw(win, 1, 1, "Test Window");  // Print text inside the window
    wrefresh(win);       // Refresh window

    getch();             // Wait for key press
    endwin();            // Restore terminal
    return 0;
}

/*
    Print -->

    printw("Hello, PDCurses!\n");               // Print a message
    mvprintw(5, 10, "Hello, PDCurses!");        // Print a message at a specific location
    mvwprintw(win, 1, 1, "Test Window");        // Print text inside the window
*/