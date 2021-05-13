/**
 * @file Enemy.hpp
 * @author Seyitahmet Genç
 * @brief Enemy class and its function definitions
 * @date 2021-05-13
 *
 */

#pragma once

#include "Entity.hpp"

/**
 * @brief Our enemy class. It inherites entity because it should be
 * drawable on our screen.
 */
class Enemy : public Entity
{
  public:
    /**
     * @brief Construct a new Enemy object
     *
     * @param xpos x position of new enemy object
     * @param ypos y position of new enemy object
     * @param width width of new enemy object (used for drawing on screen)
     * @param height height of new enemy object (used for drawing on screen)
     * @param tex texture of new enemy object (used for drawing on screen)
     */
    Enemy(int xpos, int ypos, int width, int height, SDL_Texture *tex);

    /**
     * @brief updates enemy's position. Runs on every frame
     *
     */
    void update();

    /**
     * @brief reset enemy's location off screen. this function is called when
     * an enemy gets shot or hits the player
     *
     */
    void die();

    void setSpeed(int speed) { this->speed = speed; }
    int getSpeed() { return this->speed; }

  private:
    int speed;
};
