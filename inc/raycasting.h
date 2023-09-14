#ifndef RAYCASTNG_H
#define RAYCASTNG_H

#include <stdbool.h>
#include <limits.h>
#include "constants.h"
#include "player.h"
#include "ray_direction.h"

/**
 * struct ray_s - Stores information about a ray.
 * @rayAngle: The angle at which the ray was cast.
 * @wallHitX: The x-coordinate of the point where the ray hit a wall.
 * @wallHitY: The y-coordinate of the point where the ray hit a wall.
 * @distance: Distance from the player's position to the wall hit by the ray.
 * @wasHitVertical: Whether ray hit wall vertically (true) or horizontally.
 * @texture: The texture ID associated with the wall hit by the ray.
 */
typedef struct ray_s
{
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;
	bool wasHitVertical;
	int texture;
} ray_t;

extern ray_t rays[NUM_RAYS];

void calculateRayCollision(float rayAngle, int rayId);
void castPlayerRays(void);
void drawMapRays(void);

#endif /* RAYCASTING_H */
