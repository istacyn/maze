#ifndef RAY_DIRECTION_H
#define RAY_DIRECTION_H

#include <stdbool.h>
#include "constants.h"

bool isRayFacingDown(float angle);
bool isRayFacingUp(float angle);
bool isRayFacingRight(float angle);
bool isRayFacingLeft(float angle);

#endif /* RAY_DIRECTION_H */
