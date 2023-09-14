#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "constants.h"
#include "sdl_graphics.h"
#include "map.h"
#include "player.h"
#include "raycasting.h"
#include "wall.h"
#include "sprite.h"
#include "textures.h"

bool isGameActive = false;
int ticksLastFrame;

/**
 * setup - Initializes game resources and prepares for execution.
 * Loads textures and sets up the game environment.
 */
void setup(void)
{
	/* Initializes game decoding PNG files and loads */
	/* textures into wallTextures array */
	initializeTextures();
}

/**
 * processInput - Handles user input and updates game state accordingly.
 * Detects user input events such as keyboard actions and responds to them.
 */
void processInput(void)
{
	SDL_Event event;

	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
		{
			isGameActive = false;
			break;
		}
		case SDL_KEYDOWN:
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				isGameActive = false;
			if (event.key.keysym.sym == SDLK_UP)
				player.walkDirection = +1;
			if (event.key.keysym.sym == SDLK_DOWN)
				player.walkDirection = -1;
			if (event.key.keysym.sym == SDLK_RIGHT)
				player.turnDirection = +1;
			if (event.key.keysym.sym == SDLK_LEFT)
				player.turnDirection = -1;
			break;
		}
		case SDL_KEYUP:
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				isGameActive = false;
			if (event.key.keysym.sym == SDLK_UP)
				player.walkDirection = 0;
			if (event.key.keysym.sym == SDLK_DOWN)
				player.walkDirection = 0;
			if (event.key.keysym.sym == SDLK_RIGHT)
				player.turnDirection = 0;
			if (event.key.keysym.sym == SDLK_LEFT)
				player.turnDirection = 0;
			break;
		}
	}
}

/**
 * update - Updates the game state based on elapsed time.
 * Calculates game object movements and interactions over time.
 */
void update(void)
{
	int timeToWait;
	float deltaTime;

	/* Compute how long until we reach the target frame time in milliseconds */
	timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticksLastFrame);

	/* Only delay execution if frame rate is too fast */
	if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH)
	{
		SDL_Delay(timeToWait);
	}

	/* Compute delta time to be used as an update factor */
	/* when changing game objects */
	deltaTime = (SDL_GetTicks() - ticksLastFrame) / 2000.0f;

	/* Store the milliseconds of the current frame to be used in the future */
	ticksLastFrame = SDL_GetTicks();

	movePlayer(deltaTime);
	castPlayerRays();
}

/**
 * render - Render the current game frame.
 * Clears the color buffer, renders game objects, and displays the frame.
 */
void render(void)
{
	/* Clear the color buffer */
	clearColorBuffer(0xFF000000);

	/* Render the wall and sprites */
	renderWallProjection();
	renderSpriteProjection();

	/* Render the minimap and its objects */
	drawMapGrid();
	drawMapRays();
	drawMapSprites();
	drawPlayerOnMinimap();

	renderColorBuffer();
}

/**
 * releaseResources - Release allocated resources and clean up.
 * Frees memory and performs cleanup before exiting the game.
 */
void releaseResources(void)
{
	freeTextures();
	destroyWindow();
}

/**
 * main - The main entry point of the game program.
 * Initializes the game, runs the game loop, and handles cleanup.
 * Return: The exit status of the game program.
 */
int main(void)
{
	isGameActive = initWindow();

	setup();

	while (isGameActive)
	{
		processInput();
		update();
		render();
	}

	releaseResources();

	return (EXIT_SUCCESS);
}
