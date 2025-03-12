# PDCurses: Portable Console UI Library for Windows

## Overview
PDCurses (Public Domain Curses) is a free and open-source implementation of the curses library for creating text-based user interfaces (TUI). It provides functions for handling keyboard input, window management, color handling, and more.

PDCurses is particularly useful for Windows systems, as the standard `ncurses` library is not available natively. It allows you to build cross-platform console applications with a UI framework similar to `ncurses`.

## Features
- Supports Windows, DOS, OS/2, and SDL2-based environments.
- Provides functions for handling windows, colors, and keyboard inputs.
- Works with compilers like MinGW, MSVC, and GCC.
- Includes mouse support and enhanced console UI features.
- Licensed under the Public Domain.

---

## Installation
### Windows (MinGW / MSYS2)
1. Install `MSYS2` (if not already installed):
   - Download from: [https://www.msys2.org](https://www.msys2.org)
   - Follow the installation instructions and update the package database:
     ```sh
     pacman -Syu
     ```
2. Install `PDCurses` using `pacman`:
   ```sh
   pacman -S mingw-w64-x86_64-pdcurses
   ```
3. Verify installation by checking the library files:
   ```sh
   ls /mingw64/include/curses.h
   ls /mingw64/lib/libpdcurses.a
   ```
4. Compile a test program:
   ```sh
   g++ test.cpp -o test -lpdcurses
   ```

### Windows (Manual Installation)
1. Clone the PDCurses repository:
   ```sh
   git clone https://github.com/wmcbrine/PDCurses.git
   ```
2. Build it using MinGW:
   ```sh
   cd PDCurses/wincon
   mingw32-make -f Makefile.mingw
   ```
3. Copy the compiled libraries to the appropriate locations:
   - Copy `pdcurses.a` to `/mingw64/lib/` and rename it to `libpdcurses.a`
   - Copy `curses.h` and `panel.h` to `/mingw64/include/`

---

## Usage
### Writing a Simple PDCurses Program
Save the following code as `test.cpp`:
```cpp
#include <curses.h>

int main() {
    initscr();            // Initialize the screen
    printw("Hello, PDCurses!"); // Print text
    refresh();            // Refresh screen to apply changes
    getch();              // Wait for user input
    endwin();             // End curses mode
    return 0;
}
```
### Compiling & Running
Compile the program with:
```sh
g++ test.cpp -o test -lpdcurses
```
Run the executable:
```sh
./test
```

---

## Next Steps
- Learn window management (`newwin`, `box`, `wprintw`)
- Implement keyboard handling (`getch`, `keypad`)
- Use color handling (`start_color`, `init_pair`)
- Create a full-fledged CLI UI with buttons, menus, and panels

For advanced tutorials, visit: [https://github.com/wmcbrine/PDCurses](https://github.com/wmcbrine/PDCurses)

---

## Conclusion
PDCurses is a powerful tool for building console-based UIs in C and C++. By mastering its functions, you can develop feature-rich terminal applications with full control over UI elements.