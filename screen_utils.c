#include "screen_utils.h"

void save_screen() {
    // Hexadecimal x1B represents escape character (ASCII code 27)
    // ANSI escape code to save screen
    printf("\x1B[?1049h");
}

void restore_screen() {
    // ANSI escape code to restore screen
    printf("\x1B[?1049l");
}

void clear_screen() {
    // ANSI escape sequence to clear screen and move cursor to the top-left corner of terminal (row 1, column 1)
    printf("\x1B[2J\x1B[1;1H");
}

void clear_lines(int num_of_lines) {
    // ANSI escape code to move cursor up given number of lines
    printf("\x1B[%dA", num_of_lines);
    for (int i = 0; i < num_of_lines; i++) {
        // ANSI escape sequence to clear line and move cursor to next line
        printf("\x1B[K\x1B[1E");
    }
}

void move_cursor(int num_of_lines) {
    // ANSI escape code to move cursor up given number of lines
    printf("\x1B[%dA", num_of_lines);
}