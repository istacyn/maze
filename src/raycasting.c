#include "raycasting.h"
#include "geometry.h"

ray_t rays[NUM_RAYS];

/**
 * calculateRayCollision - Casts a ray to detect wall collisions
				and stores ray information.
 * @rayAngle: The angle at which the ray is cast.
 * @rayId: The ID of the ray strip for storing ray information.
 */
void calculateRayCollision(float rayAngle, int rayId)
{
	float interceptX;
	float interceptY;
	float xStep;
	float yStep;

	/* Horizontal ray */
	bool foundHorzWallHit = false;
	float horzWallHitX = 0;
	float horzWallHitY = 0;
	int horzWallTexture = 0;
	float nextHorzTouchX;
	float nextHorzTouchY;
	float horzHitDistance;

	/* Vertical ray */
	bool foundVertWallHit = false;
	float vertWallHitX = 0;
	float vertWallHitY = 0;
	int vertWallTexture = 0;
	float nextVertTouchX;
	float nextVertTouchY;
	float vertHitDistance;

	float xToCheck;
	float yToCheck;

	normalizeAngle(&rayAngle);

	/* Horizontal Ray-Grid Intersection */
	foundHorzWallHit = false;
	horzWallHitX = 0;
	horzWallHitY = 0;
	horzWallTexture = 0;

	interceptY = floor(player.y / CELL_SIZE) * CELL_SIZE;
	interceptY += isRayFacingDown(rayAngle) ? CELL_SIZE : 0;

	interceptX = player.x + (interceptY - player.y) / tan(rayAngle);


	yStep = CELL_SIZE;
	yStep *= isRayFacingUp(rayAngle) ? -1 : 1;

	xStep = CELL_SIZE / tan(rayAngle);
	xStep *= (isRayFacingLeft(rayAngle) && xStep > 0) ? -1 : 1;
	xStep *= (isRayFacingRight(rayAngle) && xStep < 0) ? -1 : 1;

	nextHorzTouchX = interceptX;
	nextHorzTouchY = interceptY;

	while (isWithinMapBounds(nextHorzTouchX, nextHorzTouchY))
	{
		xToCheck = nextHorzTouchX;
		yToCheck = nextHorzTouchY + (isRayFacingUp(rayAngle) ? -1 : 0);

		if (isWallAt(xToCheck, yToCheck))
		{
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallTexture = getCellValue((int)floor(yToCheck / CELL_SIZE),
						(int)floor(xToCheck / CELL_SIZE));
			foundHorzWallHit = true;
			break;
		}
		else
		{
			nextHorzTouchX += xStep;
			nextHorzTouchY += yStep;
		}
	}

	/* Vertical Ray-Grid Intersection */
	foundVertWallHit = false;
	vertWallHitX = 0;
	vertWallHitY = 0;
	vertWallTexture = 0;

	interceptX = floor(player.x / CELL_SIZE) * CELL_SIZE;
	interceptX += isRayFacingRight(rayAngle) ? CELL_SIZE : 0;

	interceptY = player.y + (interceptX - player.x) * tan(rayAngle);

	xStep = CELL_SIZE;
	xStep *= isRayFacingLeft(rayAngle) ? -1 : 1;

	yStep = CELL_SIZE * tan(rayAngle);
	yStep *= (isRayFacingUp(rayAngle) && yStep > 0) ? -1 : 1;
	yStep *= (isRayFacingDown(rayAngle) && yStep < 0) ? -1 : 1;

	nextVertTouchX = interceptX;
	nextVertTouchY = interceptY;

	while (isWithinMapBounds(nextVertTouchX, nextVertTouchY))
	{
		xToCheck = nextVertTouchX + (isRayFacingLeft(rayAngle) ? -1 : 0);
		yToCheck = nextVertTouchY;

		if (isWallAt(xToCheck, yToCheck))
		{
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallTexture = getCellValue((int)floor(yToCheck / CELL_SIZE),
						(int)floor(xToCheck / CELL_SIZE));
			foundVertWallHit = true;
			break;
		}
		else
		{
			nextVertTouchX += xStep;
			nextVertTouchY += yStep;
		}
	}

	horzHitDistance = foundHorzWallHit
		? calculateDistance(player.x, player.y, horzWallHitX, horzWallHitY)
		: FLT_MAX;
	vertHitDistance = foundVertWallHit
		? calculateDistance(player.x, player.y, vertWallHitX, vertWallHitY)
		: FLT_MAX;

	if (vertHitDistance < horzHitDistance)
	{
		rays[rayId].distance = vertHitDistance;
		rays[rayId].wallHitX = vertWallHitX;
		rays[rayId].wallHitY = vertWallHitY;
		rays[rayId].texture = vertWallTexture;
		rays[rayId].wasHitVertical = true;
		rays[rayId].rayAngle = rayAngle;
	}
	else
	{
		rays[rayId].distance = horzHitDistance;
		rays[rayId].wallHitX = horzWallHitX;
		rays[rayId].wallHitY = horzWallHitY;
		rays[rayId].texture = horzWallTexture;
		rays[rayId].wasHitVertical = false;
		rays[rayId].rayAngle = rayAngle;
	}
}

/**
 * castPlayerRays - Cast rays for all columns to create the 3D rendering effect.
 */
void castPlayerRays(void)
{
	float rayAngle;
	float distanceProjPlane;

	distanceProjPlane = (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2);

	for (int col = 0; col < NUM_RAYS; col++)
	{
		rayAngle = player.rotationAngle + atan((col - NUM_RAYS / 2) /
				distanceProjPlane);
		calculateRayCollision(rayAngle, col);
	}
}

void drawMapRays(void)
{
	for (int i = 0; i < NUM_RAYS; i += 50)
	{
		drawLine(
			player.x * MINIMAP_SCALE,
			player.y * MINIMAP_SCALE,
			rays[i].wallHitX * MINIMAP_SCALE,
			rays[i].wallHitY * MINIMAP_SCALE,
			0xFF0000FF
		);
	}
}


