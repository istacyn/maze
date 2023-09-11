#ifndef RAYCASTNG_H
#define RAYCASTNG_H

#include <stdbool.h>
#include <limits.h>
#include "constants.h"
#include "player.h"

typedef struct	{
	float	rayAngle;
	float	wallHitX;
	float	wallHitY;
	float	distance;
	bool	wasHitVertical;
	int		texture;
}			ray_t;

extern ray_t rays[NUM_RAYS];

bool	isRayFacingUp(float angle);
bool	isRayFacingDown(float angle);
bool	isRayFacingLeft(float angle);
bool	isRayFacingRight(float angle);
void	castAllRays(void);
void	castRay(float rayAngle, int stripId);
void	renderMapRays(void);

#endif /* RAYCASTING_H */
