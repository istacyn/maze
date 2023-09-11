#ifndef SDL_GRAPHICS_H
#define SDL_GRAPHICS_H

#include "constants.h"
#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>


bool initWindow(void);
void destroyWindow(void);
void clearColorBuffer(color_t color);
void renderColorBuffer(void);
void drawPixel(int x, int y, color_t color);
void drawFilledRect(int x, int y, int width, int height, color_t color);
void drawLine(int x0, int y0, int x1, int y1, color_t color);

#endif /*SDL_GRAPHICS_H*/
