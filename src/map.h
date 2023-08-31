#ifndef MAP_H
#define MAP_H

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

/* Declare functions for map management */
void loadMap(int map[][MAP_WIDTH]);
int getMapValue(int map[][MAP_WIDTH], int x, int y);

#endif /* MAP_H */
