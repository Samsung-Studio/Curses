#include <curses.h>
#include <string.h>

#define MAX_LINES 20    // Total lines of text
#define MAX_WIDTH 46    // Max width for wrapping (window width - padding)

void wrap_text(const char *text, WINDOW *win, int y) {
    char buffer[MAX_WIDTH + 1];
    int len = strlen(text);
    
    for (int i = 0; i < len; i += MAX_WIDTH) {
        strncpy(buffer, text + i, MAX_WIDTH);
        buffer[MAX_WIDTH] = '\0';  // Ensure null termination
        mvwprintw(win, y++, 2, "%s", buffer);
    }
}

void show_scrollable_content(WINDOW *win) {
    const char *text[MAX_LINES] = {
        "Welcome to the scrollable window example!",
        "This text will wrap correctly inside the box.",
        "Use the UP and DOWN arrow keys to navigate.",
        "Text that is too long will automatically wrap.",
        "PDCurses allows handling large text easily.",
        "This feature is useful for logs and chat UIs.",
        "You can implement paginated text viewers.",
        "Or display help sections dynamically.",
        "Custom CLI dashboards can be created.",
        "Let's keep scrolling...",
        "More lines to test scrolling behavior.",
        "Keep going...",
        "Handling large text blocks smoothly.",
        "Resizable layouts can also help.",
        "Combining colors makes UI better.",
        "Let's add dynamic updates next.",
        "Try modifying this for custom text.",
        "Scroll limits help in preventing errors.",
        "Almost at the end...",
        "End of scrollable content."
    };

    int max_display_lines = 8; // Visible lines in the window
    int start_line = 0;         // Current scrolling position
    int ch;

    while (1) {
        werase(win);
        box(win, 0, 0);
        
        // Display visible lines with proper wrapping
        int line_offset = 1;
        for (int i = 0; i < max_display_lines; i++) {
            if (start_line + i < MAX_LINES) {
                wrap_text(text[start_line + i], win, line_offset);
                line_offset += (strlen(text[start_line + i]) / MAX_WIDTH) + 1;
            }
        }
        wrefresh(win);

        ch = getch();
        switch (ch) {
            case KEY_UP:
                if (start_line > 0) start_line--;
                break;
            case KEY_DOWN:
                if (start_line < MAX_LINES - max_display_lines) start_line++;
                break;
            case 'q': // Quit scrolling
                return;
        }
    }
}

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    refresh();

    int win_height = 12, win_width = 50;
    int start_y = (LINES - win_height) / 2;
    int start_x = (COLS - win_width) / 2;

    // Create scrolling window
    WINDOW *scroll_win = newwin(win_height, win_width, start_y, start_x);
    box(scroll_win, 0, 0);
    mvwprintw(scroll_win, 1, 2, "Scrollable Content Example");
    wrefresh(scroll_win);

    show_scrollable_content(scroll_win);

    delwin(scroll_win);
    endwin();
    return 0;
}