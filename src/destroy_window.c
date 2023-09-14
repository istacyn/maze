#include "sdl_graphics.h"

/**
 * destroyWindow - Clean up SDL_Instance and associated resources.
 */
void destroyWindow(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

