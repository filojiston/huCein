/**
 * @file RenderWindow.hpp
 * @author Seyitahmet Genç
 * @brief RenderWindow class and its function definitions
 * @date 2021-05-13
 *
 */

#pragma once

#include <SDL2/SDL.h>

#include "Entity.hpp"

/**
 * @brief RenderWindow class used for drawing entities on screen.
 * Also, it loads textures to memory, so we can add textures to entities
 * and draw them.
 */
class RenderWindow
{
  public:
    /**
     * @brief Construct a new RenderWindow object
     *
     * @param title title of our window
     * @param screenWidth width of new window
     * @param screenHeight height of new window
     */
    RenderWindow(const char *title, int screenWidth, int screenHeight);

    /**
     * @brief load png files to the program
     *
     * @param filePath path of the png file
     * @return SDL_Texture* newly created texture from png file
     */
    SDL_Texture *loadTexture(const char *filePath);

    /**
     * @brief clear previous frame's drawings
     *
     */
    void clear();

    /**
     * @brief render given entity on the screen
     *
     * @param entity entity to be drawn on the screen
     */
    void render(Entity &entity);

    /**
     * @brief render current frame (call after all drawing is done)
     */
    void display();

    /**
     * @brief destroy our window and renderer
     *
     */
    void destroy();

    SDL_Renderer *getRenderer() { return this->renderer; }

  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Color bgColor;
};
