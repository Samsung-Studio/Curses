#include <curses.h>

int main() {
    initscr();               // Initialize screen
    start_color();           // Enable color mode

    init_pair(1, COLOR_RED, COLOR_BLACK);   // Define color pair (ID 1)
    init_pair(2, COLOR_GREEN, COLOR_WHITE);   // Define color pair (ID 2)
    
    attron(COLOR_PAIR(1));   // Activate color pair 1
    printw("This text is RED!\n");
    attroff(COLOR_PAIR(1));  // Deactivate color

    attron(COLOR_PAIR(2));   // Activate color pair 2
    printw("This text is GREEN!\n");
    attroff(COLOR_PAIR(2));  // Deactivate color

    getch();                 // Wait for key press
    endwin();                // Restore terminal
    return 0;
}

/*
    Colour Modes -->

    Color Name	    Code
    COLOR_BLACK	    0
    COLOR_RED	    1
    COLOR_GREEN	    2
    COLOR_YELLOW	3
    COLOR_BLUE	    4
    COLOR_MAGENTA	5
    COLOR_CYAN	    6
    COLOR_WHITE	    7
*/