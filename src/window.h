#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <stdio.h>

/**
 * struct SDL_Instance - Holds pointers to an SDL window and renderer.
 * @window: Pointer to an SDL window.
 * @renderer: Pointer to an SDL renderer.
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *instance);

#endif /*WINDOW_H*/
