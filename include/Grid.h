#ifndef BOILER_GRID
#define BOILER_GRID

typedef struct SDL_Renderer SDL_Renderer;

typedef struct {
    int columns;
    int rows;
} Grid;

void Grid_Create(Grid *grid, int columns, int rows);

void Grid_Draw(Grid *grid, SDL_Renderer *renderer);

#endif