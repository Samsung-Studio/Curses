#include <curses.h>
#include <time.h>
#include <unistd.h>

void draw_ui(WINDOW *header, WINDOW *content) {
    werase(header);
    box(header, 0, 0);
    mvwprintw(header, 1, 2, "Live System Monitor");
    wrefresh(header);

    werase(content);
    box(content, 0, 0);
    mvwprintw(content, 1, 2, "Press 'q' to exit.");
    wrefresh(content);
}

void update_time(WINDOW *content) {
    char time_str[20];
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(time_str, sizeof(time_str), "%H:%M:%S", timeinfo);

    mvwprintw(content, 3, 2, "Current Time: %s", time_str);
    wrefresh(content);
}

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    refresh();

    int height, width;
    getmaxyx(stdscr, height, width);
    
    int header_height = 3;
    int content_height = height - header_height;
    
    WINDOW *header = newwin(header_height, width, 0, 0);
    WINDOW *content = newwin(content_height, width, header_height, 0);

    draw_ui(header, content);

    int ch;
    while (1) {
        update_time(content);  // Update the clock

        // Wait for input, but timeout every 1 second to update UI
        timeout(1000);  // 1000ms = 1 second
        ch = getch();
        if (ch == 'q') break;
    }

    delwin(header);
    delwin(content);
    endwin();
    return 0;
}