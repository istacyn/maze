#include "ray_direction.h"

/**
 * isRayFacingDown - Checks if a ray with the given angle is facing downward.
 * @angle: The angle to check.
 * Return: true if the ray is facing downward, false otherwise.
 */

bool isRayFacingDown(float angle)
{
	return (angle > 0 && angle < PI);
}

/**
 * isRayFacingUp - Checks if a ray with the given angle is facing upward.
 * @angle: The angle to check.
 * Return: true if the ray is facing upward, false otherwise.
 */
bool isRayFacingUp(float angle)
{
	return (!isRayFacingDown(angle));
}

/**
 * isRayFacingRight - Checks if a ray with the given angle is facing right.
 * @angle: The angle to check.
 * Return: true if the ray is facing right, false otherwise.
 */
bool isRayFacingRight(float angle)
{
	return (angle < 0.5 * PI || angle > 1.5 * PI);
}

/**
 * isRayFacingLeft - Checks if a ray with the given angle is facing left.
 * @angle: The angle to check.
 * Return: true if the ray is facing left, false otherwise.
 */
bool isRayFacingLeft(float angle)
{
	return (!isRayFacingRight(angle));
}
