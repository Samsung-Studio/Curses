#include <curses.h>

int main() {
    initscr();                 // Initialize screen
    printw("Press any key to continue...");  
    refresh();                 // Refresh screen to show output

    int ch = getch();          // Wait for a key press

    printw("\nYou pressed: %c", ch);  
    refresh();
    
    getch();                   // Wait for another key before exiting
    endwin();                  // Restore terminal
    return 0;
}