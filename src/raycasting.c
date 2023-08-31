#include <math.h>
#include "raycasting.h"
#include "rendering.h"
#include "map.h"
#include <SDL2/SDL.h>

/**
 * performRaycasting - Calculates and performs raycasting to
 * render the 3D scene on the screen.
 * It casts rays from the player's viewpoint and renders vertical
 * wall columns based on the calculated distances
 * to simulate a 3D perspective.
 *
 * @instance: Pointer to SDL_Instance object that holds window and renderer.
 * @player: Pointer to Player structure representing player's view and position.
 * @rays: Array of Ray structures representing rays cast from player's view.
 */
void performRaycasting(SDL_Instance *instance, Player *player, Ray *rays)
{
	double cameraX;
	double rayDirX, rayDirY;
	double mapX, mapY;
	double sideDistX, sideDistY;
	double deltaDistX, deltaDistY;
	double perpWallDist;
	int stepX, stepY;
	int hit = 0, side;

	calculateRayDirection(player, cameraX, &rayDirX, &rayDirY);
	/* Loop through each column of pixels on the screen */
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		/* Calculate ray position and direction */
		cameraX = 2 * x / (double)SCREEN_WIDTH - 1; /*x-coordinate in camera space*/
		calculateRayDirection(player, cameraX, &rayDirX, &rayDirY);
		// rayDirX = player->dirX + player->planeX * cameraX;
		// rayDirY = player->dirY + player->planeY * cameraX;

		/* Map position of player to the grid */
		mapX = (int)player->posX;
		mapY = (int)player->posY;

		/* Calculate delta distance for x and y */
		calculateDeltaDistances(rayDirX, rayDirY, &sideDistX, &sideDistY);
		// deltaDistX = fabs(1 / rayDirX);
		// deltaDistY = fabs(1 / rayDirY);

		/* Initialize sideDist values based on ray direction */
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->posX) * deltaDistX;
		}
		if (rayDirY < 0)
                {
                        stepY = -1;
                        sideDistY = (player->posY - mapY) * deltaDistY;
                }
                else
                {
                        stepY = 1;
                        sideDistY = (mapY + 1.0 - player->posY) * deltaDistY;
                }

		/* Perform DDA algorithm to find distance to the wall*/
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
                                mapY += stepY;
                                side = 1;
			}
			/* Check if ray has hit a wall*/
			// if (getMapValue(gameMap, mapX, mapY) > 0)
			// {
			//	hit = 1;
			// }
		}

		/* Store distance in rays array*/
		rays[x].distance = (side == 0)
			? (mapX - player->posX + (1 - stepX) / 2) / rayDirX
			: (mapY - player->posY + (1 - stepY) / 2) / rayDirY;

		/* Calculate perpendicular wall distance */
		// if (side == 0)
		// {
		//	perpWallDist = (mapX - player->posX + (1 - stepX) / 2) / rayDirX;
		// }
		// else
		//{
		//	perpWallDist = (mapY - player->posY + (1 - stepY) / 2) / rayDirY;
		// }

		/* Calculate perpendicular wall distance if needed */
                double perpWallDist = rays[x].distance;

		/* Calculate wall height and draw the wall column*/
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;

		/* Render the wall column*/
		renderWallColumn(instance->renderer, x, drawStart, drawEnd);

		hit = 0;
	}

	SDL_RenderPresent(instance->renderer);
}

void calculateRayDirection(Player *player, double cameraX, double *rayDirX, double *rayDirY)
{
    *rayDirX = player->dirX + player->planeX * cameraX;
    *rayDirY = player->dirY + player->planeY * cameraX;
}

void calculateDeltaDistances(double rayDirX, double rayDirY, double *deltaDistX, double *deltaDistY)
{
    *deltaDistX = fabs(1 / rayDirX);
    *deltaDistY = fabs(1 / rayDirY);
}
