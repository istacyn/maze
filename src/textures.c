#include "textures.h"
#include <stdio.h>

/* An array that holds the file paths of textures. */
static const char *textureFilePaths[NUM_TEXTURES] = {
	"./images/redbrick.png",		/* [0]  */
	"./images/purplestone.png",		/* [1]  */
	"./images/mossystone.png",		/* [2]  */
	"./images/graystone.png",		/* [3]  */
	"./images/colorstone.png",		/* [4]  */
	"./images/bluestone.png",		/* [5]  */
	"./images/wood.png",			/* [6]  */
	"./images/eagle.png",			/* [7]  */
	"./images/pikuma.png",			/* [8]  */
	"./images/barrel.png",			/* [9]  */
	"./images/light.png",			/* [10] */
	"./images/table.png",			/* [11] */
	"./images/guard.png",			/* [12] */
	"./images/armor.png"			/* [13] */
};

/**
 * initializeTextures - Initializes game textures by
 *			loading them from file paths.
 */
void initializeTextures(void)
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		upng_t *upng;

		upng = upng_new_from_file(textureFilePaths[i]);
		if (upng != NULL)
		{
			upng_decode(upng);
			if (upng_get_error(upng) == UPNG_EOK)
			{
				textures[i] = upng;
			}
			else
			{
				printf("Error decoding texture file %s \n", textureFilePaths[i]);
			}
		}
		else
		{
			printf("Error loading texture %s \n", textureFilePaths[i]);
		}
	}

}

/**
 * freeTextures - Frees the memory associated with loaded textures.
 */
void freeTextures(void)
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		upng_free(textures[i]);
	}
}
