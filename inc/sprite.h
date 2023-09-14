#ifndef SPRITE_H
#define SPRITE_H

#include "constants.h"
#include "sdl_graphics.h"
#include "player.h"
#include "textures.h"

/**
 * struct sprite_s - Store information about sprites.
 * @x: The x-coordinate of the sprite's position.
 * @y: The y-coordinate of the sprite's position.
 * @distance: The distance from the player to the sprite.
 * @angle: The angle between the player's view direction and sprite direction.
 * @visible: Indicates whether sprite is currently visible within player's FOV.
 * @texture: Index to be used to look up texture associated with the sprite.
 */
typedef struct sprite_s
{
	float x;
	float y;
	float distance;
	float angle;
	bool visible;
	int texture;
}	sprite_t;

void renderSpriteProjection(void);
void drawMapSprites(void);

#endif /* SPRITE_H */

