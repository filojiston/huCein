#include "RenderWindow.hpp"

#include <SDL2/SDL_image.h>

#include <iostream>

RenderWindow::RenderWindow(const char *title, int screenWidth, int screenHeight)
    : window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, screenWidth,
                              screenHeight, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Window initialization failed. Error: " << SDL_GetError()
                  << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        std::cout << "Renderer initialization failed. Error: " << SDL_GetError()
                  << std::endl;
    }

    bgColor = {255, 255, 255, 255};
}

SDL_Texture *RenderWindow::loadTexture(const char *filePath)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, filePath);

    if (texture == NULL)
    {
        std::cout << "Failed to load texture. Error: " << SDL_GetError()
                  << std::endl;
    }

    return texture;
}

void RenderWindow::clear()
{
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b,
                           bgColor.a);
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity &entity)
{
    SDL_Rect dest;
    dest.x = entity.getXPosition();
    dest.y = entity.getYPosition();
    dest.w = entity.getWidth();
    dest.h = entity.getHeight();

    SDL_RenderCopy(renderer, entity.getTexture(), NULL, &dest);
}

void RenderWindow::display() { SDL_RenderPresent(renderer); }

void RenderWindow::destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
