#include "raycasting.h"
#include "utils.h"

ray_t rays[NUM_RAYS];

bool isRayFacingDown(float angle)
{
    return (angle > 0 && angle < PI);
}

bool isRayFacingUp(float angle)
{
    return (!isRayFacingDown(angle));
}

bool isRayFacingRight(float angle)
{
    return (angle < 0.5 * PI || angle > 1.5 * PI);
}

bool isRayFacingLeft(float angle)
{
    return (!isRayFacingRight(angle));
}

/**
 * castRay - Casts a ray to detect wall collisions and stores ray information.
 * @rayAngle: The angle at which the ray is cast.
 * @stripId: The ID of the ray strip for storing ray information.
 */
void castRay(float rayAngle, int stripId)
{
    float xintercept;
    float yintercept;
    float xstep;
    float ystep;

    // Horizontal ray
    bool foundHorzWallHit = false;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    int horzWallTexture = 0;
    float nextHorzTouchX;
    float nextHorzTouchY;
    float horzHitDistance;

    // Vertical ray
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

    // Horizontal Ray-Grid Intersection
    foundHorzWallHit = false;
    horzWallHitX = 0;
    horzWallHitY = 0;
    horzWallTexture = 0;

    yintercept = floor(player.y / CELL_SIZE) * CELL_SIZE;
    yintercept += isRayFacingDown(rayAngle) ? CELL_SIZE : 0;

    xintercept = player.x + (yintercept - player.y) / tan(rayAngle);

    ystep = CELL_SIZE;
    ystep *= isRayFacingUp(rayAngle) ? -1 : 1;

    xstep = CELL_SIZE / tan(rayAngle);
    xstep *= (isRayFacingLeft(rayAngle) && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight(rayAngle) && xstep < 0) ? -1 : 1;

    nextHorzTouchX = xintercept;
    nextHorzTouchY = yintercept;

    while (isWithinMapBounds(nextHorzTouchX, nextHorzTouchY))
    {
        xToCheck = nextHorzTouchX;
        yToCheck = nextHorzTouchY + (isRayFacingUp(rayAngle) ? -1 : 0);

        if (isWallAt(xToCheck, yToCheck))
        {
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            horzWallTexture = getCellValue((int)floor(yToCheck / CELL_SIZE), (int)floor(xToCheck / CELL_SIZE));
            foundHorzWallHit = true;
            break;
        }
        else
        {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }

    // Vertical Ray-Grid Intersection
    foundVertWallHit = false;
    vertWallHitX = 0;
    vertWallHitY = 0;
    vertWallTexture = 0;

    xintercept = floor(player.x / CELL_SIZE) * CELL_SIZE;
    xintercept += isRayFacingRight(rayAngle) ? CELL_SIZE : 0;

    yintercept = player.y + (xintercept - player.x) * tan(rayAngle);

    xstep = CELL_SIZE;
    xstep *= isRayFacingLeft(rayAngle) ? -1 : 1;

    ystep = CELL_SIZE * tan(rayAngle);
    ystep *= (isRayFacingUp(rayAngle) && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown(rayAngle) && ystep < 0) ? -1 : 1;

    nextVertTouchX = xintercept;
    nextVertTouchY = yintercept;

    while (isWithinMapBounds(nextVertTouchX, nextVertTouchY))
    {
        xToCheck = nextVertTouchX + (isRayFacingLeft(rayAngle) ? -1 : 0);
        yToCheck = nextVertTouchY;

        if (isWallAt(xToCheck, yToCheck))
        {
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            vertWallTexture = getCellValue((int)floor(yToCheck / CELL_SIZE), (int)floor(xToCheck / CELL_SIZE));
            foundVertWallHit = true;
            break;
        }
        else
        {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
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
        rays[stripId].distance = vertHitDistance;
        rays[stripId].wallHitX = vertWallHitX;
        rays[stripId].wallHitY = vertWallHitY;
        rays[stripId].texture = vertWallTexture;
        rays[stripId].wasHitVertical = true;
        rays[stripId].rayAngle = rayAngle;
    }
    else
    {
        rays[stripId].distance = horzHitDistance;
        rays[stripId].wallHitX = horzWallHitX;
        rays[stripId].wallHitY = horzWallHitY;
        rays[stripId].texture = horzWallTexture;
        rays[stripId].wasHitVertical = false;
        rays[stripId].rayAngle = rayAngle;
    }
}

/**
 * castAllRays - Cast rays for all columns to create the 3D rendering effect.
 */
void castAllRays(void)
{
    float rayAngle;
    float distanceProjPlane;

        distanceProjPlane = (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2);

    for (int col = 0; col < NUM_RAYS; col++)
    {
        rayAngle = player.rotationAngle + atan((col - NUM_RAYS / 2) / distanceProjPlane);
        castRay(rayAngle, col);
    }
}

void renderMapRays(void)
{
    for (int i = 0; i < NUM_RAYS; i += 50)
    {
        drawLine(
            player.x * MINIMAP_SCALE_FACTOR,
            player.y * MINIMAP_SCALE_FACTOR,
            rays[i].wallHitX * MINIMAP_SCALE_FACTOR,
            rays[i].wallHitY * MINIMAP_SCALE_FACTOR,
            0xFF0000FF
        );
    }
}


