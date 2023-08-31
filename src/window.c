#include "window.h"
#include <SDL2/SDL.h>
#include "utils.h"

/**
 * init_instance - Function to intiliaze a Window and Renderer.
 * @instance: A pointer to SDL_Instance object.
 * Return: 0 on success, 1 0n failure
 */
int init_instance(SDL_Instance *instance)
{
	/*Initialize SDL*/
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}

	/*Create a new window instance*/
	instance->window = SDL_CreateWindow("Maze Demo", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	if (instance->window == NULL)
	{
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		cleanUpAndExit(instance, 1); /*Call cleanup function*/
	}

	/*Create a new renderer instance linked to the window*/
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		cleanUpAndExit(instance, 1);
	}
	return (0);
}
