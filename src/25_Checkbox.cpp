#include <curses.h>
#include <string.h>

#define CHECKBOX_COUNT 3
#define DROPDOWN_COUNT 4
#define MAX_OPTION_LENGTH 20

void draw_checkboxes(WINDOW *win, int selected, int checked[]) {
    const char *options[CHECKBOX_COUNT] = {"Option 1", "Option 2", "Option 3"};

    for (int i = 0; i < CHECKBOX_COUNT; i++) {
        if (selected == i) wattron(win, A_REVERSE);
        mvwprintw(win, 2 + i, 2, "[%c] %s", checked[i] ? 'X' : ' ', options[i]);
        wattroff(win, A_REVERSE);
    }
    wrefresh(win);
}

void draw_dropdown(WINDOW *win, int selected) {
    const char *options[DROPDOWN_COUNT] = {"Red", "Blue", "Green", "Yellow"};

    for (int i = 0; i < DROPDOWN_COUNT; i++) {
        if (selected == i) wattron(win, A_REVERSE);
        mvwprintw(win, 2 + i, 2, "%s", options[i]);
        wattroff(win, A_REVERSE);
    }
    wrefresh(win);
}

int select_dropdown(WINDOW *win) {
    int selected = 0;
    int ch;

    while (1) {
        draw_dropdown(win, selected);
        ch = getch();

        if (ch == KEY_UP && selected > 0) selected--;
        else if (ch == KEY_DOWN && selected < DROPDOWN_COUNT - 1) selected++;
        else if (ch == '\n') break;
    }
    return selected;
}

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    refresh();

    int win_height = 10, win_width = 30;
    int start_y = (LINES - win_height) / 2;
    int start_x = (COLS - win_width) / 2;

    WINDOW *checkbox_win = newwin(win_height, win_width, start_y, start_x);
    box(checkbox_win, 0, 0);
    mvwprintw(checkbox_win, 1, 2, "Select Options:");
    wrefresh(checkbox_win);

    int checked[CHECKBOX_COUNT] = {0, 0, 0};
    int selected_checkbox = 0;
    draw_checkboxes(checkbox_win, selected_checkbox, checked);

    int ch;
    while (1) {
        ch = getch();
        if (ch == KEY_UP && selected_checkbox > 0) selected_checkbox--;
        else if (ch == KEY_DOWN && selected_checkbox < CHECKBOX_COUNT - 1) selected_checkbox++;
        else if (ch == ' ') checked[selected_checkbox] = !checked[selected_checkbox];
        else if (ch == '\n') break;
        draw_checkboxes(checkbox_win, selected_checkbox, checked);
    }

    werase(checkbox_win);
    box(checkbox_win, 0, 0);
    mvwprintw(checkbox_win, 1, 2, "Select a Color:");
    wrefresh(checkbox_win);

    int selected_color = select_dropdown(checkbox_win);

    werase(checkbox_win);
    box(checkbox_win, 0, 0);
    mvwprintw(checkbox_win, 1, 2, "Selection Done!");
    mvwprintw(checkbox_win, 3, 2, "Color: %s", (selected_color == 0) ? "Red" :
                                             (selected_color == 1) ? "Blue" :
                                             (selected_color == 2) ? "Green" : "Yellow");
    mvwprintw(checkbox_win, 5, 2, "Press any key to exit.");
    wrefresh(checkbox_win);
    getch();

    delwin(checkbox_win);
    endwin();
    return 0;
}