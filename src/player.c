#include "player.h"
#include "utils.h"
#include "sdl_graphics.h"

player_t player = 
{
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
	player.rotationAngle += player.rotationSpeed * player.turnDirection *deltaTime;
	normalizeAngle(&player.rotationAngle);

	/* Calculate step size based on movement direction and speed */
	stepSize = player.moveSpeed * player.walkDirection * deltaTime;

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
 * renderMapPlayer - Render the player on the minimap.
 */
void renderMapPlayer(void) {
    // Draw a rectangle representing the player on the minimap
    drawFilledRect(
        player.x * MINIMAP_SCALE_FACTOR,
        player.y * MINIMAP_SCALE_FACTOR,
        player.width * MINIMAP_SCALE_FACTOR,
        player.height * MINIMAP_SCALE_FACTOR,
        0xFFFFFFFF
    );
}
