//
// Bomb.cpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sun Jun 18 12:17:38 2017 Jérémy Perry
// Last update Wed Jun 21 18:12:34 2017 Jérémy Perry
//

#include "Bomb.hpp"

Bomb::Bomb(Player& author) : _author (author), _range (author.getFire())
{
  this->type = BOMB;
  this->setTexture("media/wall.bmp");
  this->setPosX(author.getPosX());
  this->setPosY(author.getPosY());
  this->_countDown = 3.f;
}

Bomb::~Bomb()
{
  // Nothing to do here...
}

Player&		Bomb::getAuthor() const
{
  return (this->_author);
}

int		Bomb::getRange() const
{
  return (this->_range);
}

f32		Bomb::getCountDown() const
{
  return (this->_countDown);
}

void		Bomb::addCountDown(f32 val)
{
  this->_countDown += val;
}
