#include "Enemy.hpp"
#include "Constants.hpp"

#include <iostream>

Enemy::Enemy(int xpos, int ypos, int width, int height, SDL_Texture *tex)
    : Entity(xpos, ypos, width, height, tex)
{
    this->speed = 1;
}

void Enemy::update()
{
    this->setYPosition(this->getYPosition() + this->speed);
    if (this->getYPosition() > SCREEN_HEIGHT)
    {
        this->setYPosition(-this->getHeight());
    }
}

void Enemy::die()
{
    int xpos = std::rand() % (SCREEN_WIDTH - 32);
    int ypos = std::rand() % 100 - (500);
    this->setXPosition(xpos);
    this->setYPosition(ypos);
}
