//
// Block.cpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sun Jun 18 12:30:04 2017 Jérémy Perry
// Last update Wed Jun 21 18:12:49 2017 Jérémy Perry
//

#include "Block.hpp"

Block::Block(int x, int y)
{
  this->type = BLOCK;
  this->setTexture("media/stones.jpg");
  this->setPosX(x);
  this->setPosY(y);
}

Block::~Block()
{
  // Nothing to do here...
}
