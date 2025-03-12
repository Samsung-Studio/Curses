#include <curses.h>
#include <string.h>

#define TOTAL_ROWS 15  // Total rows in dataset
#define COLS 3
#define COL_WIDTH 12  // Column width
#define LEFT_PADDING 5
#define VISIBLE_ROWS 5  // Number of rows visible at a time

const char *data[TOTAL_ROWS][COLS] = {
    {"ID", "Name", "Score"},
    {"1", "Alice", "90"}, {"2", "Bob", "85"}, {"3", "Charlie", "78"}, {"4", "David", "92"},
    {"5", "Eve", "88"}, {"6", "Frank", "75"}, {"7", "Grace", "80"}, {"8", "Hank", "95"},
    {"9", "Ivy", "67"}, {"10", "Jack", "72"}, {"11", "Kim", "89"}, {"12", "Leo", "91"},
    {"13", "Mia", "85"}, {"14", "Noah", "79"}
};

void draw_table(WINDOW *win, int selected_row, int selected_col, int start_row) {
    werase(win);
    box(win, 0, 0);

    // Print header
    for (int j = 0; j < COLS; j++) {
        mvwprintw(win, 1, LEFT_PADDING + j * COL_WIDTH, "%s", data[0][j]); // Header row
    }
    mvwprintw(win, 1, LEFT_PADDING - 2, ">");

    // Print visible rows
    for (int i = 0; i < VISIBLE_ROWS; i++) {
        int data_row = start_row + i + 1; // Skip header row
        if (data_row >= TOTAL_ROWS) break;

        for (int j = 0; j < COLS; j++) {
            int x_pos = LEFT_PADDING + j * COL_WIDTH;
            int y_pos = 2 + i;

            if (data_row == selected_row) {
                wattron(win, A_REVERSE);
                mvwprintw(win, y_pos, x_pos, "%s", data[data_row][j]);
                wattroff(win, A_REVERSE);
            } else {
                mvwprintw(win, y_pos, x_pos, "%s", data[data_row][j]);
            }
        }
    }
    wrefresh(win);
}

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    refresh();

    int win_height = 8, win_width = 45;
    int start_y = (LINES - win_height) / 2;
    int start_x = 5;  // Window starts 5 spaces from the left

    WINDOW *table_win = newwin(win_height, win_width, start_y, start_x);
    box(table_win, 0, 0);

    int selected_row = 1, selected_col = 0, start_row = 0;
    draw_table(table_win, selected_row, selected_col, start_row);

    int ch;
    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_UP:
                if (selected_row > 1) {
                    selected_row--;
                    if (selected_row < start_row + 1) start_row--;
                }
                break;
            case KEY_DOWN:
                if (selected_row < TOTAL_ROWS - 1) {
                    selected_row++;
                    if (selected_row >= start_row + VISIBLE_ROWS) start_row++;
                }
                break;
            case KEY_LEFT:
                if (selected_col > 0) selected_col--;
                break;
            case KEY_RIGHT:
                if (selected_col < COLS - 1) selected_col++;
                break;
        }
        draw_table(table_win, selected_row, selected_col, start_row);
    }

    delwin(table_win);
    endwin();
    return 0;
}