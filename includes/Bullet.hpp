/**
 * @file Bullet.hpp
 * @author Seyitahmet Genç
 * @brief Bullet class and its function definitions
 * @date 2021-05-13
 *
 */

#pragma once

#include "Entity.hpp"

/**
 * @brief Our bullet class. It inherites entity because it should be
 * drawable on our screen.
 */
class Bullet : public Entity
{
  public:
    /**
     * @brief Construct a new Bullet object
     *
     * @param xpos x position of new bullet object
     * @param ypos y position of new bullet object
     * @param width width of new bullet object (used for drawing on screen)
     * @param height height of new bullet object (used for drawing on screen)
     * @param tex texture of new bullet object (used for drawing on screen)
     */
    Bullet(int xpos, int ypos, int width, int height, SDL_Texture *tex);

    /**
     * @brief Fira a bullet at given x,y positions
     *
     * @param xpos  x position of fired bullet
     * @param ypos y position of fired bullet
     */
    void fire(int xpos, int ypos);

    /**
     * @brief updates bullet's position. Runs on every frame
     */
    void update();

    bool getIsFired() { return this->isFired; }
    void setIsFired(bool fired) { this->isFired = fired; }

  private:
    int speed;
    bool isFired;
};
