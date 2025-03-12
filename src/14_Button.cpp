#include <curses.h>

#define BUTTONS 2

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    refresh();

    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);

    int content_width = screen_width / 2;
    int content_height = screen_height / 2;
    int start_y = (screen_height - content_height) / 2;
    int start_x = (screen_width - content_width) / 2;

    // Create content window
    WINDOW *content = newwin(content_height, content_width, start_y, start_x);
    box(content, 0, 0);
    mvwprintw(content, 2, (content_width / 2) - 6, "Choose an option:");
    wrefresh(content);

    // Buttons
    const char *buttons[BUTTONS] = {"OK", "Cancel"};
    int selected = 0;
    
    int ch;
    while (1) {
        // Clear content window and redraw border
        werase(content);
        box(content, 0, 0);
        mvwprintw(content, 2, (content_width / 2) - 6, "Choose an option:");

        // Draw buttons
        for (int i = 0; i < BUTTONS; i++) {
            if (i == selected) {
                wattron(content, A_REVERSE);
                mvwprintw(content, content_height - 3, (content_width / 2) - 5 + (i * 10), "[ %s ]", buttons[i]);
                wattroff(content, A_REVERSE);
            } else {
                mvwprintw(content, content_height - 3, (content_width / 2) - 5 + (i * 10), "[ %s ]", buttons[i]);
            }
        }
        wrefresh(content);

        // Handle key input
        ch = getch();
        switch (ch) {
            case KEY_LEFT:
                selected = (selected == 0) ? BUTTONS - 1 : selected - 1;
                break;
            case KEY_RIGHT:
                selected = (selected == BUTTONS - 1) ? 0 : selected + 1;
                break;
            case '\n':  // ENTER key
                if (selected == 0) {
                    mvwprintw(content, content_height - 2, 2, "You selected OK.");
                } else {
                    mvwprintw(content, content_height - 2, 2, "You selected Cancel.");
                }
                wrefresh(content);
                getch();
                endwin();
                return 0;
        }
    }

    endwin();
    return 0;
}