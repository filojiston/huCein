#include "Bullet.hpp"

Bullet::Bullet(int xpos, int ypos, int width, int height, SDL_Texture *tex)
    : Entity(xpos, ypos, width, height, tex)
{
    this->speed = 12; // baadırım
    isFired = false;
}

void Bullet::fire(int xpos, int ypos)
{
    this->setXPosition(xpos);
    this->setYPosition(ypos);
    isFired = true;
}

void Bullet::update()
{
    if (isFired)
    {
        this->setYPosition(this->getYPosition() - this->speed);
        if (this->getYPosition() < 0)
            isFired = false;
    }
}
