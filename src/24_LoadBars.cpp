#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BAR_WIDTH 30  // Max width of progress bars

void draw_ui(WINDOW *header, WINDOW *content) {
    werase(header);
    box(header, 0, 0);
    mvwprintw(header, 1, 2, "System Dashboard");
    wrefresh(header);

    werase(content);
    box(content, 0, 0);
    mvwprintw(content, 1, 2, "Press 'q' to exit.");
    wrefresh(content);
}

// Function to draw progress bars correctly
void draw_progress(WINDOW *content, int y, const char *label, int percentage) {
    int bar_width = (percentage * MAX_BAR_WIDTH) / 100;

    mvwprintw(content, y, 2, "%s [%3d%%] ", label, percentage);

    wattron(content, A_REVERSE);
    for (int i = 0; i < bar_width; i++) {
        mvwprintw(content, y, 20 + i, " ");
    }
    wattroff(content, A_REVERSE);

    // Draw empty bar space
    for (int i = bar_width; i < MAX_BAR_WIDTH; i++) {
        mvwprintw(content, y, 20 + i, " ");
    }

    wrefresh(content);
}

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    refresh();
    srand(time(0));  // Seed random numbers

    int height, width;
    getmaxyx(stdscr, height, width);
    
    int header_height = 3;
    int content_height = height - header_height;
    
    WINDOW *header = newwin(header_height, width, 0, 0);
    WINDOW *content = newwin(content_height, width, header_height, 0);

    draw_ui(header, content);

    int cpu_usage = 30, memory_usage = 50, disk_usage = 70;
    int ch;
    while (1) {
        draw_progress(content, 3, "CPU Usage  ", cpu_usage);
        draw_progress(content, 5, "Memory Used", memory_usage);
        draw_progress(content, 7, "Disk Usage ", disk_usage);

        // Simulate real-time change
        cpu_usage = (cpu_usage + (rand() % 10 - 5)) % 101;
        memory_usage = (memory_usage + (rand() % 5 - 2)) % 101;
        disk_usage = (disk_usage + (rand() % 8 - 3)) % 101;

        if (cpu_usage < 0) cpu_usage = 0;
        if (memory_usage < 0) memory_usage = 0;
        if (disk_usage < 0) disk_usage = 0;

        timeout(1000);  // Wait 1 second
        ch = getch();
        if (ch == 'q') break;
    }

    delwin(header);
    delwin(content);
    endwin();
    return 0;
}