#include <stdlib.h>
#include <time.h>

#include "life.h"

// Grid is allocated to be a 3D array, as if:
// 
// char grid[2][LIFE_ROWS][LIFE_COLS]
//
// If the grid element is `1`, the cell is alive. If it's `0`, the cell
// is dead.
// 
// `grid[0]` and `grid[1]` are used for double-buffering the cell data
// from generation to generation.

static char ***grid;
static int read_grid = 0; // idx of grid we're reading from

static int get_neighbor_count(int r, int c)
{
    // Compute neighbor indexes, wrapping around
    int n = r - 1 < 0? LIFE_ROWS - 1: r - 1;
    int s = (r + 1) % LIFE_ROWS;
    int w = c - 1 < 0? LIFE_COLS - 1: c - 1;
    int e = (c + 1) % LIFE_COLS;

    // Count neighbors
    char **g = grid[read_grid];

    return
        g[n][w] + g[n][c] + g[n][e] +
        g[r][w] +    0    + g[r][e] +
        g[s][w] + g[s][c] + g[s][e];
}

static void update_cell(int r, int c)
{
    int write_grid = !read_grid;

    int neighbor_count = get_neighbor_count(r, c);
    int cell_alive = grid[read_grid][r][c];
    int new_state;

    if (cell_alive)
        if (neighbor_count < 2 || neighbor_count > 3)
            new_state = 0; // death by underpopulation
        else
            new_state = 1; // stays alive
    else // cell is dead
        if (neighbor_count == 3)
            new_state = 1; // comes to life
        else
            new_state = 0; // stays dead

    grid[write_grid][r][c] = new_state;
}

static void randomize(void)
{
    srand(time(NULL));

    for (int r = 0; r < LIFE_ROWS; r++)
        for (int c = 0; c < LIFE_COLS; c++)
            grid[read_grid][r][c] = rand() & 1;
}

static void grid_alloc(void)
{
    // Allocate space for double buffer
    grid = malloc(sizeof(char **) * 2);

    for (int g = 0; g < 2; g++) {
        // Allocate space for each row
        grid[g] = malloc(sizeof(char *) * LIFE_ROWS);

        for (int r = 0; r < LIFE_ROWS; r++) 
            // Allocate space for each column
            grid[g][r] = malloc(sizeof(char) * LIFE_COLS);
    }
}

static void grid_free(void)
{
    for (int g = 0; g < 2; g++) {
        for (int r = 0; r < LIFE_ROWS; r++) 
            // Free space for each column
            free(grid[g][r]);
        // Free space for each row
        free(grid[g]);
    }
    // Free space for double buffer
    free(grid);
}

void life_init(void)
{
    grid_alloc();
    randomize();
}

void life_shutdown(void)
{
    grid_free();
}

void life_update(void)
{
    for (int r = 0; r < LIFE_ROWS; r++)
        for (int c = 0; c < LIFE_COLS; c++)
            update_cell(r, c);

    read_grid = !read_grid;
}

char **life_get_cells(void)
{
    return grid[read_grid];
}

