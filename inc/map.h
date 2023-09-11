#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include "constants.h"
#include "sdl_graphics.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 13

/* Declare functions for map management */
bool isWallAt(float x, float y);
bool isWithinMapBounds(float x, float y);
int getCellValue(int row, int col);
void renderMapGrid(void);

#endif /* MAP_H */
