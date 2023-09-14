#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdint.h>
#include "constants.h"
#include "upng.h"

upng_t	*textures[NUM_TEXTURES];

void initializeTextures(void);
void freeTextures(void);

#endif /* TEXTURES_H */

