#include "Grid.h"

#include <SDL2/SDL.h>

void Grid_Create(Grid *grid, int columns, int rows)
{
    grid->columns   = columns;
    grid->rows      = rows;
}

// function should not be in here because the renderer handles drawing the grid
void Grid_Draw(Grid *grid, SDL_Renderer *renderer, int UNIT_SIZE)
{
    int lx = 0;
    int rx = grid->columns * UNIT_SIZE;
    int ty = 0;
    int by = grid->rows * UNIT_SIZE;

    for(int r = 0; r < grid->rows + 1; ++r) {
        int y = r * UNIT_SIZE;
        SDL_RenderDrawLine(renderer, lx, y, rx, y);
    }

    for(int c = 0; c < grid->columns + 1; ++c) {
        int x = c * UNIT_SIZE;
        SDL_RenderDrawLine(renderer, x, ty, x, by);
    }
}
