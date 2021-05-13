#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "Game.hpp"

bool init();

int main(int argc, char *argv[])
{
    if (!init())
        return 1;

    Game *game = new Game();

    while (game->getIsRunning())
    {
        game->processInput();
        if (!game->getIsPaused())
        {
            game->update();
        }
        game->render();
    }

    game->showGameOver();
    SDL_Delay(3000);

    SDL_Quit();
    return 0;
}

bool init()
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL_Init failed. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // initialize SDL image
    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "IMG_Init failed. Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // initialize SDL ttf
    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: "
                  << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}
