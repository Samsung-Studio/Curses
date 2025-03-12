#include <curses.h>
#include <string.h>

#define TOTAL_ROWS 5
#define COLS 3
#define COL_WIDTH 12
#define LEFT_PADDING 5

char data[TOTAL_ROWS][COLS][20] = {
    {"ID", "Name", "Score"},
    {"1", "Alice", "90"},
    {"2", "Bob", "85"},
    {"3", "Charlie", "78"},
    {"4", "David", "92"}
};

void draw_table(WINDOW *win, int selected_row, int selected_col) {
    werase(win);
    box(win, 0, 0);

    for (int i = 0; i < TOTAL_ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int x_pos = LEFT_PADDING + j * COL_WIDTH;
            int y_pos = 2 + i;

            if (i == selected_row && j == selected_col) {
                wattron(win, A_REVERSE);
                mvwprintw(win, y_pos, x_pos, "%s", data[i][j]);
                wattroff(win, A_REVERSE);
            } else {
                mvwprintw(win, y_pos, x_pos, "%s", data[i][j]);
            }
        }
    }
    wrefresh(win);
}

void edit_cell(WINDOW *win, int row, int col) {
    if (row == 0) return;  // Prevent editing header

    char input[20];
    mvwprintw(win, 2 + row, LEFT_PADDING + col * COL_WIDTH, "               "); // Clear existing text
    mvwgetnstr(win, 2 + row, LEFT_PADDING + col * COL_WIDTH, input, 19);

    strcpy(data[row][col], input);  // Update table data
}

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    refresh();

    int win_height = 10, win_width = 50;
    int start_y = (LINES - win_height) / 2;
    int start_x = 5;  // Window starts 5 spaces from the left

    WINDOW *table_win = newwin(win_height, win_width, start_y, start_x);
    box(table_win, 0, 0);

    int selected_row = 1, selected_col = 0;
    draw_table(table_win, selected_row, selected_col);

    int ch;
    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_UP:
                if (selected_row > 1) selected_row--;
                break;
            case KEY_DOWN:
                if (selected_row < TOTAL_ROWS - 1) selected_row++;
                break;
            case KEY_LEFT:
                if (selected_col > 0) selected_col--;
                break;
            case KEY_RIGHT:
                if (selected_col < COLS - 1) selected_col++;
                break;
            case '\n': // Press ENTER to edit
                curs_set(1);
                echo();
                edit_cell(table_win, selected_row, selected_col);
                noecho();
                curs_set(0);
                break;
        }
        draw_table(table_win, selected_row, selected_col);
    }

    delwin(table_win);
    endwin();
    return 0;
}