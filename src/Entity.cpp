#include "Entity.hpp"

Entity::Entity(int xpos, int ypos, int width, int height, SDL_Texture *tex)
    : xpos(xpos), ypos(ypos), width(width), height(height), tex(tex)
{
}

void Entity::setPosition(int xpos, int ypos)
{
    this->xpos = xpos;
    this->ypos = ypos;
}
