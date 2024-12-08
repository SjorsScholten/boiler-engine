#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600
#define UNIT_SIZE       16
#define UNITS           3

SDL_Window      *window;
SDL_Renderer    *renderer;
SDL_Texture     *imageAtlas;

bool running;

int horizontal = 0;
int vertical = 0;
bool submit = false;

struct Unit {
    int x; // x coordinate
    int y; // y coordinate
    int m; // spaced it can move
} u1, u2, u3;

struct Grid {
    int columns;
    int rows;
} grid;

struct Cursor {
    int x;
    int y;
    SDL_Rect srcR;
} cursor;

int InitializeApplication()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    if(!IMG_Init(IMG_INIT_PNG))
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    if(!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(window, 0, NULL);

    if(!renderer)
    {
        return -1;
    }

    return 1;
}

void PollEvents()
{
    static SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            running = false;
            break;
        }
        else if(event.type == SDL_KEYDOWN)
        {
            if(event.key.keysym.sym == SDLK_RIGHT)
            {
                ++horizontal;
            }
            else if(event.key.keysym.sym == SDLK_LEFT)
            {
                --horizontal;
            }
            else if(event.key.keysym.sym == SDLK_DOWN)
            {
                ++vertical;
            }
            else if(event.key.keysym.sym == SDLK_UP)
            {
                --vertical;
            }
            else if(event.key.keysym.sym == SDLK_z)
            {
                submit = true;
            }
        }
    }

}

void DrawSprite(SDL_Rect const * const srcR, int x, int y)
{
    static SDL_Rect dstR;

    dstR.x = x;
    dstR.y = y;
    dstR.w = srcR->w;
    dstR.h = srcR->h;

    SDL_RenderCopy(renderer, imageAtlas, srcR, &dstR);
}

void GridDraw()
{
    int lx = 0;
    int rx = grid.columns * UNIT_SIZE;
    int ty = 0;
    int by = grid.rows * UNIT_SIZE;
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for(int r = 0; r < grid.rows + 1; ++r) {
        int y = r * UNIT_SIZE;
        SDL_RenderDrawLine(renderer, lx, y, rx, y);
    }

    for(int c = 0; c < grid.columns + 1; ++c) {
        int x = c * UNIT_SIZE;
        SDL_RenderDrawLine(renderer, x, ty, x, by);
    }
}

void ClearScreen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void PresentScreen()
{
    SDL_RenderPresent(renderer);
    SDL_Delay(1);
}

void SpriteSrcR(SDL_Rect *srcR, int c, int r)
{
    srcR->x = c * UNIT_SIZE + c;
    srcR->y = r * UNIT_SIZE + r;
    srcR->w = srcR->h = UNIT_SIZE;
}

int main(int argc, char* args[])
{
    InitializeApplication();

    char imagePath[] = "./resources/monochrome.png";
    imageAtlas = IMG_LoadTexture(renderer, imagePath);

    if(!imageAtlas)
    {
        printf("Could not load image on path: %s\n", imagePath);
        return -1;
    }

    grid.columns = grid.rows = 15;

    cursor.x = 7;
    cursor.y = 1;
    SpriteSrcR(&cursor.srcR, 19, 14);

    struct Unit units[UNITS];
    static struct Unit *selectedUnit;
    
    SDL_Rect unitR, selectedR;
    SpriteSrcR(&unitR,      25,   0);
    SpriteSrcR(&selectedR,  26,   0);
    
    units[0].x = 0;
    units[0].y = 7;
    units[0].m = 1;

    units[1].x = 7;
    units[1].y = 7;
    units[1].m = 2;

    units[2].x = grid.columns - 1;
    units[2].y = 7;
    units[2].m = 3;

    running = true;

    while(running)
    {
        horizontal = vertical = 0;
        submit = false;
        PollEvents();

        if(horizontal != 0)
        {
            int tox = cursor.x + horizontal;
            if(tox > -1 && tox < grid.columns)
            {
                cursor.x = tox;
            }
        }

        if(vertical != 0)
        {
            int toy = cursor.y + vertical;
            if(toy > -1 && toy < grid.rows)
            {
                cursor.y = toy;
            }
        }

        if(submit)
        {
            for(int i = 0; i < UNITS; ++i)
            {
                if(units[i].x == cursor.x && units[i].y == cursor.y)
                {
                    selectedUnit = &units[i];
                    break;
                }
            }
        }

        ClearScreen();

        for(int i = 0; i < UNITS; ++i)
        {
            SDL_Rect *srcR = (selectedUnit == &units[i]) ? &selectedR : &unitR;
            DrawSprite(srcR, units[i].x * UNIT_SIZE, units[i].y * UNIT_SIZE);
        }

        DrawSprite(&cursor.srcR, cursor.x * UNIT_SIZE, cursor.y * UNIT_SIZE);
        
        GridDraw();

        PresentScreen();
    }

    SDL_DestroyTexture(imageAtlas);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
