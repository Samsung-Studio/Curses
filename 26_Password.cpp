#include <curses.h>
#include <string.h>
#include <ctype.h>

#define MAX_PASSWORD_LEN 20

void draw_form(WINDOW *win, char *password) {
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 1, 2, "Enter Password:");

    // Masked password display
    mvwprintw(win, 3, 2, "Password: ");
    for (int i = 0; i < strlen(password); i++) {
        mvwprintw(win, 3, 12 + i, "*");
    }

    mvwprintw(win, 5, 2, "Press ENTER to submit.");
    wrefresh(win);
}

void submit_form(WINDOW *win, char *password) {
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 2, 2, "Password Submitted!");
    mvwprintw(win, 4, 2, "Entered: %s", password);  // Normally, you wouldn't show this in real apps!
    mvwprintw(win, 6, 2, "Press any key to exit.");
    wrefresh(win);
    getch();
}

int main() {
    initscr();
    noecho();
    curs_set(1);
    keypad(stdscr, TRUE);
    refresh();

    int win_height = 10, win_width = 40;
    int start_y = (LINES - win_height) / 2;
    int start_x = (COLS - win_width) / 2;

    WINDOW *form_win = newwin(win_height, win_width, start_y, start_x);
    box(form_win, 0, 0);

    char password[MAX_PASSWORD_LEN + 1] = "";
    int len = 0;

    draw_form(form_win, password);

    int ch;
    while ((ch = getch()) != '\n') {
        if (ch == KEY_BACKSPACE || ch == 127) {  // Handle backspace
            if (len > 0) password[--len] = '\0';
        } else if (isprint(ch) && len < MAX_PASSWORD_LEN) {  // Add character if within limit
            password[len++] = ch;
            password[len] = '\0';
        }
        draw_form(form_win, password);
    }

    submit_form(form_win, password);

    delwin(form_win);
    endwin();
    return 0;
}