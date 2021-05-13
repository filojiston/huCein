/**
 * @file Player.hpp
 * @author Seyitahmet Genç
 * @brief Player class and its function definitions
 * @date 2021-05-13
 *
 */

#pragma once

#include "Entity.hpp"

/**
 * @brief Our player class. It inherites entity because it should be
 * drawable on our screen.
 */
class Player : public Entity
{
  public:
    /**
     * @brief Construct a new Player object
     *
     * @param xpos x position of new player object
     * @param ypos y position of new player object
     * @param width width of new player object (used for drawing on screen)
     * @param height height of new player object (used for drawing on screen)
     * @param tex texture of new player object (used for drawing on screen)
     */
    Player(int xpos, int ypos, int width, int height, SDL_Texture *tex);

    /**
     * @brief updates player's position. runs on every frame
     *
     */
    void update();

    int getDirection() { return this->direction; }
    int getSpeed() { return this->speed; }

    void setDirection(int dir) { this->direction = dir; }
    void setSpeed(int speed) { this->speed = speed; }

  private:
    int direction;
    int speed;
};
