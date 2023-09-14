#include "player.h"
#include "geometry.h"

player_t player = {
	.x = SCREEN_WIDTH / 2,
	.y = SCREEN_HEIGHT / 2,
	.width = 1,
	.height = 1,
	.turnDirection = 0,
	.walkDirection = 0,
	.rotationAngle = PI / 2,
	.moveSpeed = 100,
	.rotationSpeed = 45 * (PI / 180)
};

/**
 * movePlayer - Move the player based on input and elapsed time.
 * @deltaTime: The elapsed time since the last frame.
 */
void movePlayer(float deltaTime)
{
	float stepSize;
	float newPlayerX;
	float newPlayerY;

	/* Update the player's rotation angle */
	player.rotationAngle += player.turnDirection *
		player.rotationSpeed * deltaTime;
	normalizeAngle(&player.rotationAngle);

	/* Calculate step size based on movement direction and speed */
	stepSize = player.walkDirection * player.moveSpeed * deltaTime;

	/* Calculate new player position*/
	newPlayerX = player.x + cos(player.rotationAngle) * stepSize;
	newPlayerY = player.y + sin(player.rotationAngle) * stepSize;

	/* Check for collisions with walls before updating player's position */
	if (!isWallAt(newPlayerX, newPlayerY))
	{
		player.x = newPlayerX;
		player.y = newPlayerY;
	}
}

/**
 * drawPlayerOnMinimap - Render the player on the minimap.
 */
void drawPlayerOnMinimap(void)
{
	/* Draw a rectangle representing the player on the minimap */
	drawFilledRect
	(
		player.x * MINIMAP_SCALE,
		player.y * MINIMAP_SCALE,
		player.width * MINIMAP_SCALE,
		player.height * MINIMAP_SCALE,
		0xFFFFFFFF
	);
}
