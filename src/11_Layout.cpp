#include <curses.h>

int main() {
    initscr();
    noecho();
    curs_set(0);
    refresh();  // Ensure screen updates before creating windows

    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);  // Get terminal size

    int header_height = 3, header_width = screen_width; // Header takes full width
    int sidebar_width = screen_width / 4;               // Sidebar takes 1/4 of screen
    int content_width = screen_width - sidebar_width;   // Remaining space
    int content_height = screen_height - header_height; // Full height minus header

    // Create header, sidebar, and content area
    WINDOW *header = newwin(header_height, header_width, 0, 0);
    WINDOW *sidebar = newwin(content_height, sidebar_width, header_height, 0);
    WINDOW *content = newwin(content_height, content_width, header_height, sidebar_width);

    // Draw borders
    box(header, 0, 0);
    box(sidebar, 0, 0);
    box(content, 0, 0);

    // Add labels
    mvwprintw(header, 1, (header_width / 2) - 7, " PDCurses UI ");
    mvwprintw(sidebar, 1, 1, "Sidebar");
    mvwprintw(content, 1, 1, "Main Content");

    // Refresh all windows
    wrefresh(header);
    wrefresh(sidebar);
    wrefresh(content);

    getch();  // Wait for key press
    endwin(); // Restore terminal
    return 0;
}