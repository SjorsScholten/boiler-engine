
#include <stdlib.h>
#include "Window.h"

#include<SDL2/SDL.h>

WindowPtr WindowCreate(int width, int height)
{
    WindowPtr window = malloc(sizeof(struct Window));
    window->width = width;
    window->height = height;
    window->instance = SDL_CreateWindow()
}
