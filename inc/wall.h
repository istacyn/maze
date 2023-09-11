#ifndef WALL_H
#define WALL_H

#include <math.h>
#include "constants.h"
#include "player.h"
#include "raycasting.h"
#include "sdl_graphics.h"
#include "textures.h"

// void changeColorIntensity(color_t *color, float factor);
// void renderWallStripe(int x, float perpDistance, int wallTopY, int wallBottomY, bool wasHitVertical, int textureOffsetX, int texNum);
void	renderWallProjection(void);
void renderWalls(void);

#endif /* WALL_H */
