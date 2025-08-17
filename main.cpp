#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Graphics.hpp"

static Graphics graphics;

// This function runs once at application startup. Initialize all subsystems.
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    SDL_SetAppMetadata("Hijinks Demo", "1.0.0", "mmyerspnw.hijinksdemo");

    if (!graphics.Initialize())
        return SDL_APP_FAILURE;

    return SDL_APP_CONTINUE;
}

// This function runs when a new event(mouse input, keypresses, etc) occurs.
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_KEY_DOWN ||
        event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

// This function runs once per frame and is the main update loop.
SDL_AppResult SDL_AppIterate(void* appstate)
{
    graphics.Update();

    return SDL_APP_CONTINUE;
}

// This function runs once at application shutdown. Shut down all subsystems.
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    graphics.Shutdown();

    SDL_Quit();
}
