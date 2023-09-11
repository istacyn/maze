#ifndef PLAYER_H
#define PLAYER_H

#include "constants.h"
#include "sdl_graphics.h"
#include "map.h"

typedef struct {
    float x; // X-coordinate of the player's position
    float y; // Y-coordinate of the player's position
    float width; // Width of the player's bounding box
    float height; // Height of the player's bounding box
    float rotationAngle; // Current rotation angle of the player
    float moveSpeed; // Speed at which the player moves
    float rotationSpeed; // Speed at which the player rotates
    int turnDirection; // Turn direction: -1 (left), 0 (none), 1 (right)
    int walkDirection; // Walk direction: -1 (backward), 0 (none), 1 (forward)
} player_t;

extern player_t	player;

void	movePlayer(float deltaTime);
void	drawPlayerOnMinimap(void);

#endif /* PLAYER_H */
