#include <curses.h>

int main() {
    initscr();            // Initialize PDCurses
    noecho();             // Don't echo user input
    cbreak();             // Disable line buffering
    keypad(stdscr, TRUE); // Enable function keys
    curs_set(0);          // Hide the cursor

    printw("Hello, PDCurses! Press any key to exit.\n");        // Print a message
    mvprintw(5, 10, "Hello, PDCurses! Press any key to exit."); // Print a message at a specific location
    refresh(); // Update the screen

    getch();   // Wait for user input
    endwin();  // Restore the terminal

    return 0;
}