//
// Player.cpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sun Jun 18 12:44:38 2017 Jérémy Perry
// Last update Wed Jun 21 19:38:43 2017 Jérémy Perry
//

#include <iostream>
#include "Player.hpp"

Player::Player(std::string name, int numero, int win_width, int win_height)
{
  this->type = PLAYER;
  this->setTexture("media/axe.jpg");
  this->_moveSpeed = 48.f;
  this->_name = name;
  this->_alive = true;
  this->_fire = 1;
  this->_bombMax = 1;
  this->_bombUsed = 0;
  if (numero == 1)
    {
      this->setPosX(1);
      this->setPosY(MAP_HEIGHT - 2);
      this->setTexture("media/portal5.bmp");
    }
  else if (numero == 2)
    {
      this->setPosX(MAP_WIDTH - 2);
      this->setPosY(MAP_HEIGHT - 2);
      this->setTexture("media/particlered.bmp");
    }
  else if (numero == 3)
    {
      this->setPosX(1);
      this->setPosY(1);
      this->setTexture("media/particlegreen.jpg");
    }
  else if (numero == 4)
    {
      this->setPosX(MAP_WIDTH - 2);
      this->setPosY(1);
      this->setTexture("media/particlewhite.bmp");
    }
  this->_wPosX = this->getPosX() * (win_width / MAP_WIDTH) + (win_width / MAP_WIDTH) / 2;
  this->_wPosY = this->getPosY() * (win_height / MAP_WIDTH) + (win_height / MAP_WIDTH) / 2;
}

Player::~Player()
{
  // Nothing to do here...
}

std::string	Player::getName() const
{
  return (this->_name);
}

float		Player::getWPosX() const
{
  return (this->_wPosX);
}

void		Player::addWPosX(float value)
{
  this->_wPosX += value;
}

void		Player::addPosX(int value)
{
  this->setPosX(this->getPosX() + value);
}

float		Player::getWPosY() const
{
  return (this->_wPosY);
}

void		Player::addWPosY(float value)
{
  this->_wPosY += value;
}

void		Player::addPosY(int value)
{
  this->setPosY(this->getPosY() + value);
}
bool		Player::isAlive() const
{
  return (this->_alive);
}

void		Player::death()
{
  this->_alive = false;
}

int		Player::getFire() const
{
  return (this->_fire);
}

void		Player::addFire()
{
  this->_fire++;
}

int		Player::getBombMax() const
{
  return (this->_bombMax);
}

void		Player::addBombMax()
{
  this->_bombMax++;
}

int		Player::getBombUsed() const
{
  return (this->_bombUsed);
}

void		Player::addBombUsed(int value)
{
  this->_bombUsed += value;
}

float		Player::getMoveSpeed() const
{
  return (this->_moveSpeed);
}

void		Player::addMoveSpeed()
{
  this->_moveSpeed += 15;
}
