#include "sdltemplate.h"
#include <assert.h>

int main() {
    // Initialize SDL
    sdltemplate::sdl();

    // Check if window and renderer are not null
    assert(sdltemplate::window != nullptr);
    assert(sdltemplate::renderer != nullptr);

    // Create a color
    SDL_Color color = sdltemplate::createColor(255, 255, 255, 255);

    // Check if the color is correct
    assert(color.r == 255);
    assert(color.g == 255);
    assert(color.b == 255);
    assert(color.a == 255);

    // Clean up
    SDL_DestroyRenderer(sdltemplate::renderer);
    SDL_DestroyWindow(sdltemplate::window);
    SDL_Quit();

    return 0;
}
