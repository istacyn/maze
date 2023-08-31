#ifndef RENDERING_H
#define RENDERING_H

#include "raycasting.h"
#include "window.h"

/* Declare rendering functions */
void renderWallColumn(SDL_Renderer * renderer,
		int x, int drawStart, int drawEnd);

#endif /* RENDERING_H */
