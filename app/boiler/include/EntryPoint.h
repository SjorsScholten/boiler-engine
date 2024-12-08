
#ifndef BOILER_ENTRYPOINT
#define BOILER_ENTRYPOINT

#include <stdio.h>

#include <SDL2/SDL.h>

extern void OnEngineInit();

SDL_Window      *window;
SDL_Renderer    *renderer;

int InitializeEngine()
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
}

int main(int argc, char *argv)
{
    if(InitializeEngine() < 0)
    {

    }

    
}

#endif
