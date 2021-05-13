#include "Player.hpp"
#include "Constants.hpp"

Player::Player(int xpos, int ypos, int width, int height, SDL_Texture *tex)
    : Entity(xpos, ypos, width, height, tex)
{
    this->direction = 0;
    this->speed = 15;
}

void Player::update()
{
    this->setXPosition(this->getXPosition() + this->speed * this->direction);
    if (this->getXPosition() < 0)
    {
        this->setXPosition(0);
        return;
    }

    if (this->getXPosition() > SCREEN_WIDTH - this->getWidth())
    {
        this->setXPosition(SCREEN_WIDTH - this->getWidth());
    }

    this->direction = 0;
}
