#include <SDL2/SDL.h>
#include "window.h"

/**
 * cleanUpAndExit - Function to handle cleanup in case of error.
 * @instance: A pointer to the SDL_Instance object.
 * @errorCode: The error code if any.
 * Return: Nothing
 */

void cleanUpAndExit(SDL_Instance *instance, int errorCode)
{
	if (instance->renderer != NULL)
	{
		SDL_DestroyRenderer(instance->renderer);
	}
	if (instance->window != NULL)
	{
		SDL_DestroyWindow(instance->window);
	}
	SDL_Quit();
	exit(errorCode);
}
