#include "geometry.h"
#include "constants.h"
#include <math.h>

/**
 * normalizeAngle - Normalize an angle to be within the range [0, 2*PI).
 * @angle: A pointer to the angle to be normalized.
 */
void normalizeAngle(float *angle)
{
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0)
		*angle = TWO_PI + *angle;
}

/**
 * calculateDistance - Calculate the Euclidean distance between two points.
 * @x1: The x-coordinate of the first point.
 * @y1: The y-coordinate of the first point.
 * @x2: The x-coordinate of the second point.
 * @y2: The y-coordinate of the second point.
 * Return: The Euclidean distance between the two points.
 */
int calculateDistance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
