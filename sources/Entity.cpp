//
// Entity.cpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sun Jun 18 13:00:48 2017 Jérémy Perry
// Last update Sun Jun 18 20:28:41 2017 Jérémy Perry
//

#include "Entity.hpp"

Entity::~Entity()
{
  // Nothing to do here...
}

path		Entity::getTexture() const
{
  return (this->_texture);
}

void		Entity::setTexture(const path& path)
{
  this->_texture = path;
}

int		Entity::getPosX() const
{
  return (this->_posX);
}

void		Entity::setPosX(int x)
{
  this->_posX = x;
}

int		Entity::getPosY() const
{
  return (this->_posY);
}

void		Entity::setPosY(int y)
{
  this->_posY = y;
}
