/**
 * @file Entity.hpp
 * @author Seyitahmet Genç
 * @brief Entity class and its function definitions
 * @date 2021-05-13
 *
 */

#pragma once

#include <SDL2/SDL.h>

/**
 * @brief Base class for objects that needs to be drawn on the screen.
 * All other classes inherits this one.
 *
 */
class Entity
{
  public:
    /**
     * @brief Construct a new Entity object
     *
     * @param xpos x position of new entity object
     * @param ypos y position of new entity object
     * @param width width of new entity object
     * @param height height of new entity object
     * @param tex texture of new entity object
     */
    Entity(int xpos, int ypos, int width, int height, SDL_Texture *tex);

    SDL_Texture *getTexture() { return this->tex; }
    void setPosition(int xpos, int ypos);
    int getXPosition() { return this->xpos; }
    int getYPosition() { return this->ypos; }
    int getWidth() { return this->width; }
    int getHeight() { return this->height; }

    void setXPosition(int xpos) { this->xpos = xpos; }
    void setYPosition(int ypos) { this->ypos = ypos; }
    void setWidth(int width) { this->width = width; }
    void setHeight(int height) { this->height = height; }

  private:
    int xpos, ypos;
    int width, height;
    SDL_Texture *tex;
};
