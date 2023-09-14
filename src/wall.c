#include "wall.h"

/**
 * changeColorIntensity - Adjust the intensity (brightness) of a color.
 * @color: A pointer to the color to be modified.
 * @factor: The scaling factor for adjusting color intensity (0 to 1).
 *
 * This function adjusts the intensity (brightness) of the input color while
 * preserving the alpha (transparency) component to achieve effects
 * like shading, darkening or lightening of colors. The factor
 * should be a value between 0 (completely dark) and 1 (unchanged).
 */
void changeColorIntensity(color_t *color, float factor)
{
	color_t	a;
	color_t	r;
	color_t	g;
	color_t	b;

	a = (*color & 0xFF000000);
	r = (*color & 0x00FF0000) * factor;
	g = (*color & 0x0000FF00) * factor;
	b = (*color & 0x000000FF) * factor;

	/* Recombine adjusted a, r, g, & b components to form final color. */
	*color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}

/**
 * renderWallProjection - Render a wall projection with textures and shading.
 *
 * This function renders a wall projection on the screen based
 * on the raycasting results. It takes care of drawing the
 * textured wall, applying shading if the ray hit was vertical,
 * and rendering the ceiling and floor areas.
 */
void renderWallProjection(void)
{
	float distanceProjPlane;
	float wallHeight;
	int wallTopY;
	int wallBottomY;
	float perpDistance;
	color_t	texelColor;
	color_t	*wallTextureBuffer;
	int textureOffsetX;
	int textureOffsetY;
	int distanceFromTop;
	int texNum;
	int textureWidth;
	int textureHeight;

	for (int x = 0; x < NUM_RAYS; x++)
	{
		/* Calculate distance from player to the projection plane */
		distanceProjPlane = (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2);

		/* Calculate perpendicular distance from player to */
		/* wall to avoid fish-eye distortion */
		perpDistance = rays[x].distance * cos(rays[x].rayAngle -
				player.rotationAngle);

		/* Calculate height of projected wall on screen */
		wallHeight = (CELL_SIZE / perpDistance) * distanceProjPlane;

		/* The Y-coordinates where the top of the wall should be drawn. */
		wallTopY = (SCREEN_HEIGHT / 2) - (wallHeight / 2);
		wallTopY = wallTopY < 0 ? 0 : wallTopY;

		/* The Y-coordinates where the bottom of the wall should be drawn. */
		wallBottomY = (SCREEN_HEIGHT / 2) + (wallHeight / 2);
		wallBottomY = wallBottomY > SCREEN_HEIGHT ? SCREEN_HEIGHT : wallBottomY;

		/* Draw the ceiling */
		for (int y = 0; y < wallTopY; y++)
			/* colorBuffer[(SCREEN_WIDTH * y) + x] = 0xFF444444; */
			drawPixel(x, y, 0xFF444444);

		/* Draw the textured wall */
		if (rays[x].wasHitVertical)
		{
			/* perform offset for the vertical hit */
			textureOffsetX = (int)rays[x].wallHitY % CELL_SIZE;
		}
		else
		{
			/* perform offset for the horizontal hit */
			textureOffsetX = (int)rays[x].wallHitX % CELL_SIZE;
		}

		/* Determine textutre to use map content */
		texNum = rays[x].texture - 1;

		/* Query the texture width and height from upng */
		textureWidth = upng_get_width(textures[texNum]);
		textureHeight = upng_get_height(textures[texNum]);

		/* Render the wall from wallTopY to wallBottomY */
		for (int y = wallTopY; y < wallBottomY; y++)
		{
			/* calculate textureOffsetY */
			distanceFromTop = y + (wallHeight / 2) - (SCREEN_HEIGHT / 2);
			textureOffsetY = distanceFromTop * ((float)textureHeight / wallHeight);

			/* Set the wall color based on the color from the texture */
			wallTextureBuffer = (color_t *)upng_get_buffer(textures[texNum]);
			texelColor = wallTextureBuffer[(textureWidth * textureOffsetY) + textureOffsetX];

			/* Make the pixel color darker if the ray hit was vertical */
			if (rays[x].wasHitVertical)
			{
				changeColorIntensity(&texelColor, 0.7);
			}

			/* colorBuffer[(WINDOW_WIDTH * y) + x] = texelColor; */
			drawPixel(x, y, texelColor);
		}
		/* Draw the floor */
		for (int y = wallBottomY; y < SCREEN_HEIGHT; y++)
			/* colorBuffer[(SCREEN_WIDTH * y) + x] = 0xFF777777; */
			drawPixel(x, y, 0xFF777777);
	}
}
