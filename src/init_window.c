#include "sdl_graphics.h"

SDL_Window *window;
SDL_Renderer *renderer;

/**
 * initWindow - Function to initialize a Window and Renderer.
 * Return: 0 on success.
 */
bool initWindow(void)
{
	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}

	/* Create a new window instance */
	window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		return (1);
	}

	/* Create a new renderer instance linked to the window */
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return (1);
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	return (0);
}
