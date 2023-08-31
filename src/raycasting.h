#ifndef RAYCASTING_H
#define RAYCASTING_H

#include "window.h"
#include "map.h"

/* Define the maximum screen dimensions */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/* Define constants */
#define FOV 60.0
#define NUM_RAYS SCREEN_WIDTH

/**
 * struct Ray - Ray cast from the player's viewpoint.
 *
 * @angle: Direction in which the ray is cast from the player's viewpoint.
 * @distance: Calculated distance from player's position to wall hit by ray.
 */
typedef struct Ray
{
	double angle;
	double distance;
} Ray;

/**
 * struct Player - Stores player's position, viewing direction, camera plane.
 *
 * @posX: Horizontal position of the player.
 * @posY: Vertical position of the player.
 * @dirX: Horizontal direction that the player is facing.
 * @dirY: Vertical direction that the player is facing.
 * @planeX: Horizontal direction of the camera's plane of view.
 * @planeY: Vertical direction of the camera's plane of view.
 */
typedef struct Player
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
} Player;

/* Declare functions related to raycasting */
void performRaycasting(SDL_Instance *instance, Player *player, Ray *rays);
void calculateRayDirection(Player *player, double cameraX,
		double *rayDirX, double *rayDirY);
void calculateDeltaDistances(double rayDirX, double rayDirY,
		double *deltaDistX, double *deltaDistY);

#endif /* RAYCASTING_H */

