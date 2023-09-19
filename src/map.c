#include "map.h"

/* Define the game map layout */
static const int map[MAP_HEIGHT][MAP_WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 5, 0, 6, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 2, 2, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 5, 0, 0, 5},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 5, 0, 0, 5},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 5, 0, 0, 5},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5}
};

/**
 * isWallAt - Check if there's a wall at the given coordinates.
 * @x: The x-coordinate to check.
 * @y: The y-coordinate to check.
 * Return: true if there's a wall at the coordinates, false otherwise.
 */
bool isWallAt(float x, float y)
{
	int mapGridIndexX;
	int mapGridIndexY;

	if (x < 0 || x >= MAP_WIDTH * CELL_SIZE ||
		y < 0 || y >= MAP_HEIGHT * CELL_SIZE)
		return (true);

	mapGridIndexX = (int)(x / CELL_SIZE);
	mapGridIndexY = (int)(y / CELL_SIZE);
	return (map[mapGridIndexY][mapGridIndexX] != 0);
}

/**
 * isWithinMapBounds - Check if a given point is within the map boundaries.
 * @x: The x-coordinate to check.
 * @y: The y-coordinate to check.
 * Return: true if the point is within the map bounds, false otherwise.
 */
bool isWithinMapBounds(float x, float y)
{
	return (x >= 0 && x <= MAP_WIDTH * CELL_SIZE &&
		y >= 0 && y <= MAP_HEIGHT * CELL_SIZE);
}

/**
 * getCellValue - Get the value of the cell at a specific map position.
 * @i: The row index in the map.
 * @j: The column index in the map.
 * Return: The value of the cell at the specified map position.
 */
int getCellValue(int i, int j)
{
	return (map[i][j]);
}

/**
 * drawMapGrid - Render the map grid for visualization.
 */
void drawMapGrid(void)
{
	int cellX;
	int cellY;
	color_t cellColor;

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			cellX = j * CELL_SIZE;
			cellY = i * CELL_SIZE;
			cellColor = map[i][j] != 0 ? 0xFFFFFFFF : 0x00000000;

			drawFilledRect(
					cellX * MINIMAP_SCALE,
					cellY * MINIMAP_SCALE,
					CELL_SIZE * MINIMAP_SCALE,
					CELL_SIZE * MINIMAP_SCALE,
					cellColor
			);
		}
	}
}
