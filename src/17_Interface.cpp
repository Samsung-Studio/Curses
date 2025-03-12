#include <curses.h>
#include <string.h>

#define MENU_ITEMS 4

void show_popup(WINDOW *content, const char *message) {
    int height = 5, width = 40;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;

    WINDOW *popup = newwin(height, width, start_y, start_x);
    box(popup, 0, 0);
    mvwprintw(popup, 2, (width - strlen(message)) / 2, "%s", message);
    wrefresh(popup);

    getch();  // Wait for key press

    delwin(popup);  // Delete pop-up window
    werase(content); // Clear content window
    box(content, 0, 0);  // Re-draw border
    wrefresh(content); // Refresh content window
}

void capture_input(WINDOW *content) {
    char name[50];
    
    werase(content);
    box(content, 0, 0);
    mvwprintw(content, 2, 2, "Enter your name: ");
    wrefresh(content);

    echo();
    curs_set(1);
    wmove(content, 2, 20);
    wgetnstr(content, name, 20);
    noecho();
    curs_set(0);

    werase(content);
    box(content, 0, 0);
    mvwprintw(content, 2, 2, "Hello, %s!", name);
    wrefresh(content);
}

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
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
    const char *menu_items[MENU_ITEMS] = {"Home", "Form", "Popup", "Exit"};
    const char *content_messages[MENU_ITEMS] = {
        "Welcome to Home Page.",
        "Fill out the form.",
        "Show a popup message.",
        "Exiting application..."
    };

    int selected = 0;

    int ch;
    while (1) {
        // Clear sidebar and redraw border
        werase(sidebar);
        box(sidebar, 0, 0);
        mvwprintw(sidebar, 1, 2, " MENU "); // Sidebar title

        // Draw menu
        for (int i = 0; i < MENU_ITEMS; i++) {
            if (i == selected) {
                wattron(sidebar, A_REVERSE);
                mvwprintw(sidebar, i + 3, 2, "%s", menu_items[i]);
                wattroff(sidebar, A_REVERSE);
            } else {
                mvwprintw(sidebar, i + 3, 2, "%s", menu_items[i]);
            }
        }
        wrefresh(sidebar);

        // Handle key input
        ch = getch();
        switch (ch) {
            case KEY_UP:
                selected = (selected == 0) ? MENU_ITEMS - 1 : selected - 1;
                break;
            case KEY_DOWN:
                selected = (selected == MENU_ITEMS - 1) ? 0 : selected + 1;
                break;
            case '\n': // ENTER key pressed
                werase(content);
                box(content, 0, 0);
                if (selected == 1) {
                    capture_input(content);
                } else if (selected == 2) {
                    show_popup(content, "This is a pop-up message!");
                } else if (selected == 3) {
                    endwin();
                    return 0;
                } else {
                    mvwprintw(content, 2, 2, "%s", content_messages[selected]);
                    wrefresh(content);
                }
                break;
            case 'q': // Quit on 'q'
                endwin();
                return 0;
        }
    }

    endwin();
    return 0;
}