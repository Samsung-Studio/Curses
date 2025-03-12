#include <curses.h>

#define MENU_ITEMS 4  // Number of menu options

void update_content(WINDOW *content, const char *message) {
    werase(content);       // Clear the content window
    box(content, 0, 0);    // Redraw border
    mvwprintw(content, 2, 2, "%s", message);  // Print the new message
    wrefresh(content);      // Refresh content window
}

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);  // Enable arrow keys
    refresh();

    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);

    int header_height = 3, header_width = screen_width;
    int sidebar_width = screen_width / 4;
    int content_width = screen_width - sidebar_width;
    int content_height = screen_height - header_height;

    // Create windows
    WINDOW *header = newwin(header_height, header_width, 0, 0);
    WINDOW *sidebar = newwin(content_height, sidebar_width, header_height, 0);
    WINDOW *content = newwin(content_height, content_width, header_height, sidebar_width);

    // Draw initial borders
    box(header, 0, 0);
    box(sidebar, 0, 0);
    box(content, 0, 0);

    // Add header title
    mvwprintw(header, 1, (header_width / 2) - 7, " PDCurses UI ");
    wrefresh(header);
    wrefresh(sidebar);
    wrefresh(content);

    // Menu items
    const char *menu_items[MENU_ITEMS] = {"Home", "Settings", "About", "Exit"};
    const char *content_messages[MENU_ITEMS] = {
        "Welcome to the Home page.",
        "Settings Page - Modify preferences.",
        "About Page - Learn about this app.",
        "Exiting application..."
    };

    int selected = 0;  // Currently selected menu item

    int ch;
    while (1) {
        // Clear sidebar and redraw border
        werase(sidebar);
        box(sidebar, 0, 0);
        mvwprintw(sidebar, 1, 2, " MENU "); // Sidebar title

        // Draw menu
        for (int i = 0; i < MENU_ITEMS; i++) {
            if (i == selected) {
                wattron(sidebar, A_REVERSE);  // Highlight selection
                mvwprintw(sidebar, i + 3, 2, "%s", menu_items[i]);
                wattroff(sidebar, A_REVERSE);
            } else {
                mvwprintw(sidebar, i + 3, 2, "%s", menu_items[i]);
            }
        }
        wrefresh(sidebar); // Ensure sidebar updates

        // Handle key input
        ch = getch();
        switch (ch) {
            case KEY_UP:
                selected = (selected == 0) ? MENU_ITEMS - 1 : selected - 1;
                break;
            case KEY_DOWN:
                selected = (selected == MENU_ITEMS - 1) ? 0 : selected + 1;
                break;
            case '\n':  // ENTER key pressed
                update_content(content, content_messages[selected]);
                if (selected == 3) {  // "Exit" selected
                    endwin();
                    return 0;
                }
                break;
            case 'q':  // Quit on 'q'
                endwin();
                return 0;
        }
    }

    endwin();
    return 0;
}