#include <curses.h>

int main() {
    initscr();
    echo();  // ✅ Enable input visibility
    curs_set(1);  // Show cursor for input
    keypad(stdscr, TRUE);
    refresh();

    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);

    int content_width = screen_width / 2;
    int content_height = screen_height / 3;
    int start_y = (screen_height - content_height) / 2;
    int start_x = (screen_width - content_width) / 2;

    // Create window
    WINDOW *form = newwin(content_height, content_width, start_y, start_x);
    box(form, 0, 0);
    mvwprintw(form, 2, 2, "Enter your name: ");
    wrefresh(form);

    char input[50];
    wmove(form, 2, 20);  // ✅ Move cursor to input position
    wrefresh(form);
    wgetnstr(form, input, 20);  // ✅ Capture and display user input

    werase(form);
    box(form, 0, 0);
    mvwprintw(form, 2, 2, "Hello, %s!", input);  // ✅ Display input
    wrefresh(form);

    getch();
    endwin();
    return 0;
}