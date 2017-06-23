//
// Bomberman.cpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Tue Jun 13 21:54:11 2017 Jérémy Perry
// Last update Sun Jun 18 06:31:54 2017 Jérémy Perry
//

#include <iostream>
#include "bomberman.hpp"

// BLOCK CLASS

Block::Block()
{
  this->_type = BLOCK;
  this->_shape = CUBE;
}
Block::~Block() {}

// BOMB CLASS

Bomb::Bomb(int blastRange)
{
  this->_type = BOMB;
  this->_shape = SPHERE;
  this->_countDown = 3;
  this->_blastRange = blastRange;
}
Bomb::~Bomb()
{
  std::cout << "BOOM!!!" << std::endl;
}

int		Bomb::getBlastRange() const
{
  return (this->_blastRange);
}

f32		Bomb::getCountDown() const
{
  return (this->_countDown);
}

void		Bomb::addCountDown(f32 i)
{
  this->_countDown += i;
}

// PLAYER CLASS

Player::Player(const std::string name)
{
  this->_type = PLAYER;
  this->_shape = SPHERE;
  this->_name = name;
  this->_fire = 1;
  this->_speed = 50.f;
  this->_bombMax = 1;
  this->_bombUse = 0;
}
Player::~Player() {}

Bomb*		Player::putBomb() const
{ 
  return (new Bomb(this->_fire));
}

std::string	Player::getName() const
{
  return (this->_name);
}

int		Player::getFire() const
{
  return (this->_fire);
}

void		Player::addFire()
{
  this->_fire += 1;
}

int		Player::getSpeed() const
{
  return (this->_speed);
}

void		Player::addSpeed()
{
  this->_speed += 20.f;
}

int		Player::getBombMax() const
{
  return (this->_bombMax);
}

void		Player::addBombMax()
{
  this->_bombMax += 1;
}

int		Player::getBombUse() const
{
  return (this->_bombUse);
}

void		Player::addBombUse(int i)
{
  this->_bombUse += i;
}
