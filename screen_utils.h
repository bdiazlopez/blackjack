#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

void save_screen();

void restore_screen();

void clear_screen();

void clear_lines(int num_of_lines);

void move_cursor(int num_of_lines);

#ifdef __cplusplus
}
#endif
