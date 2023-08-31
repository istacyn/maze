#include "window.h"
#include "utils.h"

int main() {
    SDL_Instance instance;

    /*Initialize the SDL instance*/
    if (init_instance(&instance) != 0)
    {
        return (1); // Initialization failed
    }

    // Main program loop
    // while (1) {
        // handleInput(); // Handle user input events

        // Render the scene
        // SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255);
        // SDL_RenderClear(instance.renderer);

        // Implement your raycasting or rendering logic here

        // SDL_RenderPresent(instance.renderer);
 //}

    // Clean up before exiting (This line will never be reached in this loop)
    // cleanupGame(&instance);
    cleanUpAndExit(&instance, 1);
    
    return (0); // Successful execution (This line will never be reached in this loop)
}
