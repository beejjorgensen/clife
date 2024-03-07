#include <stdio.h>
#include "display.h"
#include "life.h"

static void clear_screen(void)
{
    // ANSI escape sequence to clear the screen
    printf("\e[2J"); fflush(stdout);
}

static void home_cursor(void)
{
    // ANSI escape sequence to home the cursor
    printf("\e[H"); fflush(stdout);
}

void display_init(void)
{
    clear_screen();
}

void display_update(char **cells)
{
    home_cursor();

    for (int r = 0; r < LIFE_ROWS; r++) {
        for (int c = 0; c < LIFE_COLS; c++)
            putchar(cells[r][c]? '#': '.');

        putchar('\n');
    }
}

