#include "sdl_graphics.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static uint32_t	*colorBuffer = NULL;
static SDL_Texture *colorBufferTexture;

/**
 * initWindow - Function to intiliaze a Window and Renderer.
 */
bool initWindow(void)
{
	/*Initialize SDL*/
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}

	/*Create a new window instance*/
	window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
				SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		return (1);
	}

	/*Create a new renderer instance linked to the window*/
	renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return (1);
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	/* Allocate memory for the color buffer*/
	colorBuffer = (uint32_t*)malloc(sizeof(uint32_t) *
			(uint32_t)SCREEN_WIDTH * (uint32_t)SCREEN_HEIGHT);

	/* Create an SDL_texture to display the color buffer */
	colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,				SDL_TEXTUREACCESS_STREAMING,
				SCREEN_WIDTH, SCREEN_HEIGHT);

	return (0);
}

/**
 * destroyWindow - Clean up SDL_Instance and associated resources.
 */
void destroyWindow(void)
{
	free(colorBuffer);
	SDL_DestroyTexture(colorBufferTexture);
   	SDL_DestroyRenderer(renderer);
    	SDL_DestroyWindow(window);
    	SDL_Quit();
}

/**
 * clearColorBuffer - Fill the color buffer with a specified color.
 * @color: The color to fill the buffer with.
 */
void clearColorBuffer(color_t color)
{
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
	{
		colorBuffer[i] = color;
	}
}

/**
 * renderColorBuffer - Update and render the color buffer.
 */
void renderColorBuffer(void)
{
    SDL_UpdateTexture(
        colorBufferTexture,
        NULL,
        colorBuffer,
        (int)((uint32_t)SCREEN_WIDTH * sizeof(color_t))
    );
    SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

/**
 * drawPixel - Set the color of a specific pixel in the color buffer.
 * @x: The x-coordinate of the pixel.
 * @y: The y-coordinate of the pixel.
 * @color: The color to set for the pixel.
 */
void drawPixel(int x, int y, color_t color) {
    colorBuffer[(SCREEN_WIDTH * y) + x] = color;
}

/**
 * drawFilledRect - Draw a filled rectangle in the color buffer.
 * @x: The x-coordinate of the top-left corner of the rectangle.
 * @y: The y-coordinate of the top-left corner of the rectangle.
 * @width: The width of the rectangle.
 * @height: The height of the rectangle.
 * @color: The color to fill the rectangle with.
 */
void drawFilledRect(int x, int y, int width, int height, color_t color) {
    for (int i = x; i <= (x + width); i++) {
        for (int j = y; j < (y + height); j++) {
            drawPixel(i, j, color);
        }
    }
}

/**
 * drawLine - Draw a line between two points in the color buffer.
 * @x0: The x-coordinate of the starting point.
 * @y0: The y-coordinate of the starting point.
 * @x1: The x-coordinate of the ending point.
 * @y1: The y-coordinate of the ending point.
 * @color: The color of the line.
 */
void drawLine(int x0, int y0, int x1, int y1, color_t color)
{
    int deltaX;
    int deltaY;
    int longestSideLength;
    float xIncrement;
    float yIncrement;
    float currentX;
    float currentY;

    // Differences between start and end of the line
    deltaX = (x1 - x0);
    deltaY = (y1 - y0);

    // Longest side of the line
    longestSideLength = (abs(deltaX) >= abs(deltaY)) ? abs(deltaX) : abs(deltaY);

    // Find the increment values
    xIncrement = deltaX / (float)longestSideLength;
    yIncrement = deltaY / (float)longestSideLength;

    // Start point
    currentX = x0;
    currentY = y0;

    // Loop all the longest side until the end
    for (int i = 0; i < longestSideLength; i++) {
        // Draw pixel, rounding the values to integer to get the nearest pixel
        drawPixel(round(currentX), round(currentY), color);

        // Increment the slope to get the next pixel
        currentX += xIncrement;
        currentY += yIncrement;
    }
}
