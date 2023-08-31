#include "rendering.h"
#include "raycasting.h"
#include <SDL2/SDL.h>

/**
 * renderWallColumn - Draw a vertical wall column on the screen using renderer.
 * @renderer: A pointer to the SDL renderer.
 * @x: The X-coordinate of column on screen where wall will be rendered.
 * @drawStart: The starting Y-coordinate of wall segment to be rendered.
 * @drawEnd: The ending Y-coordinate wall segment to be rendered.
 */
void renderWallColumn(SDL_Renderer *renderer,
		int x, int drawStart, int drawEnd)
{
	/* Set color for rendering walls*/
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	/* Draw the wall column */
	SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
}
