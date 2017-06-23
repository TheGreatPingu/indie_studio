//
// Bomberman.cpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sun Jun 18 07:46:47 2017 Jérémy Perry
// Last update Wed Jun 21 19:00:29 2017 Jérémy Perry
//

#include <chrono>
#include <cstdlib>
#include <iostream>
#include "Bomberman.hpp"

Bomberman::Bomberman(int win_width, int win_height)
  : _graphic (IrrData(win_width, win_height)), _player (Player("Player", 1, win_width, win_height)),
    _bot1 (Player("Atrid1", 2, win_width, win_height)), _bot2 (Player("Atrid2", 3, win_width, win_height)), _bot3 (Player("Atrid3", 4, win_width, win_height))
{
  this->_width = win_width;
  this->_height = win_height;
  this->_squareWidth = win_width / MAP_WIDTH;
  this->_squareHeight = win_height / MAP_HEIGHT;
  this->_numberOfPlayer = 1;
}

Bomberman::~Bomberman()
{
  std::cout << "Merci de votre participation !" << std::endl;
  std::cout << "Pour encore plus de jeux amusants, merci de nous faire passer en Tek 3." << std::endl;
}

t_squareType	Bomberman::checkBonus(void) const
{
  int		bonus = rand() % 9;

  if (bonus < 3)
    return (static_cast<t_squareType>(bonus));
  else
    return (EMPTY);
}

void		Bomberman::checkRange(Bomb &bomb, int x, int y)
{
  for (int i = 1; i <= bomb.getRange(); i++)
    {
      if (this->_grid[bomb.getPosY() + i * y][bomb.getPosX() + i * x].type == WALL)
	break;
      else if (this->_grid[bomb.getPosY() + i * y][bomb.getPosX() + i * x].type == ENTITY)
	{
	  this->_grid[bomb.getPosY() + i * y][bomb.getPosX() + i * y].type = EMPTY;
	  if (this->_grid[bomb.getPosY() + i * y][bomb.getPosX() + i * x].entity->type == BLOCK)
	    this->_grid[bomb.getPosY() + i * y][bomb.getPosX() + i * x].type = checkBonus();
	  //	  delete (this->_grid[bomb.getPosY() + i * y][bomb.getPosX() + i * x].entity);
	  this->_grid[bomb.getPosY() + i * y][bomb.getPosX() + i * x].entity = NULL;
	  this->_grid[bomb.getPosY() + i * y][bomb.getPosX() + i * x].node->remove();
	  this->_grid[bomb.getPosY() + i * y][bomb.getPosX() + i * x].node = NULL;
	  break;
	}
      else if (bomb.getPosY() + i * y == this->_player.getPosY() &&
	       bomb.getPosX() + i * x == this->_player.getPosX())
	this->_player.death();
      else if (bomb.getPosY() + i * y == this->_bot1.getPosY() &&
	       bomb.getPosX() + i * x == this->_bot1.getPosX())
	this->_bot1.death();
      else if (bomb.getPosY() + i * y == this->_bot2.getPosY() &&
	       bomb.getPosX() + i * x == this->_bot2.getPosX())
	this->_bot2.death();
      else if (bomb.getPosY() + i * y == this->_bot3.getPosY() &&
	       bomb.getPosX() + i * x == this->_bot3.getPosX())
	this->_bot3.death();
    }
}

void		Bomberman::bombHandler(void)
{
  for (int y = 0; y < MAP_HEIGHT; y++)
    for (int x = 0; x < MAP_WIDTH; x++)
      if (this->_grid[y][x].type == ENTITY && this->_grid[y][x].entity->type == BOMB)
	{
	  dynamic_cast<Bomb*>(this->_grid[y][x].entity)->addCountDown(static_cast<f32>(-1) * this->_graphic.deltaTime);
	  if (dynamic_cast<Bomb*>(this->_grid[y][x].entity)->getCountDown() < 0)
	    {
	      dynamic_cast<Bomb*>(this->_grid[y][x].entity)->getAuthor().addBombUsed(-1);
	      this->checkRange(*(dynamic_cast<Bomb*>(this->_grid[y][x].entity)), 1, 0);
	      this->checkRange(*(dynamic_cast<Bomb*>(this->_grid[y][x].entity)), 0, 1);
	      this->checkRange(*(dynamic_cast<Bomb*>(this->_grid[y][x].entity)), -1, 0);
	      this->checkRange(*(dynamic_cast<Bomb*>(this->_grid[y][x].entity)), 0, -1);
	      this->checkRange(*(dynamic_cast<Bomb*>(this->_grid[y][x].entity)), 0, 0);
	    }
	}
}

void		Bomberman::checkBomb(Player& player, EKEY_CODE key_code)
{
  if (this->_graphic.receiver.IsKeyDown(key_code) && player.getBombMax() - player.getBombUsed() > 0)
    {
      player.addBombUsed(1);
      this->_grid[player.getPosY()][player.getPosX()].type = ENTITY;
      this->_grid[player.getPosY()][player.getPosX()].entity = new Bomb(player);
      this->_grid[player.getPosY()][player.getPosX()].node = this->_graphic.manager->addSphereSceneNode();
      if (this->_grid[player.getPosY()][player.getPosX()].node)
	{
	  this->_grid[player.getPosY()][player.getPosX()].node
	    ->setPosition(vector3df(static_cast<float>(this->_grid[player.getPosY()][player.getPosX()].posX + this->_squareWidth / 2),
				    static_cast<float>(this->_grid[player.getPosY()][player.getPosX()].posY + this->_squareHeight / 2), static_cast<float>(0)));
      this->_grid[player.getPosY()][player.getPosX()].node
	    ->setMaterialTexture(0, this->_graphic.driver->getTexture(this->_grid[player.getPosY()][player.getPosX()].entity->getTexture()));
	  this->_grid[player.getPosY()][player.getPosX()].node->setMaterialFlag(video::EMF_LIGHTING, false);
	}
    }
}

void		Bomberman::checkMove(Player& player, EKEY_CODE key_code, int x, int y)
{
  if (this->_graphic.receiver.IsKeyDown(key_code))
    {
      int	newSquareX;
      int	newSquareY;

      newSquareX = player.getPosX();
      newSquareY = player.getPosY();
      if (player.getWPosX() + player.getMoveSpeed() * this->_graphic.deltaTime * x > this->_grid[player.getPosY()][player.getPosX() + 1].posX)
	newSquareX++;
      if (player.getWPosX() + player.getMoveSpeed() * this->_graphic.deltaTime * x < this->_grid[player.getPosY()][player.getPosX()].posX)
	newSquareX--;
      if (player.getWPosY() + player.getMoveSpeed() * this->_graphic.deltaTime * y > this->_grid[player.getPosY() + 1][player.getPosX()].posY)
	newSquareY++;
      if (player.getWPosY() + player.getMoveSpeed() * this->_graphic.deltaTime * y < this->_grid[player.getPosY()][player.getPosX()].posY)
	newSquareY--;
      if (player.getPosX() == newSquareX && player.getPosY() == newSquareY)
	{
	  player.addWPosX(player.getMoveSpeed() * this->_graphic.deltaTime * static_cast<float>(x));
	  player.addWPosY(player.getMoveSpeed() * this->_graphic.deltaTime * static_cast<float>(y));
	}
      else if (this->_grid[newSquareY][newSquareX].type != ENTITY && this->_grid[newSquareY][newSquareX].type != WALL)
	{
	  player.addWPosX(player.getMoveSpeed() * this->_graphic.deltaTime * static_cast<float>(x));
	  player.addWPosY(player.getMoveSpeed() * this->_graphic.deltaTime * static_cast<float>(y));
	  player.addPosX(x);
	  player.addPosY(y);
	  if (this->_grid[newSquareY][newSquareX].type == BONUS_BOMB)
	    player.addBombMax();
	  else if (this->_grid[newSquareY][newSquareX].type == BONUS_FIRE)
	    player.addFire();
	  else if (this->_grid[newSquareY][newSquareX].type == BONUS_SPEED)
	    player.addMoveSpeed();
	  if (this->_grid[newSquareY][newSquareX].node)
	    this->_grid[newSquareY][newSquareX].node->remove();
	  this->_grid[newSquareY][newSquareX].node = NULL;
	  this->_grid[newSquareY][newSquareX].type = EMPTY;
	}
    }
}

void		Bomberman::eventHandler(void)
{
  checkBomb(this->_player, KEY_SPACE);
  checkMove(this->_player, KEY_UP, 0, 1);
  checkMove(this->_player, KEY_DOWN, 0, -1);
  checkMove(this->_player, KEY_LEFT, -1, 0);
  checkMove(this->_player, KEY_RIGHT, 1, 0);
  if (this->_numberOfPlayer == 2 && this->_bot1.isAlive())
    {
      checkBomb(this->_bot1, KEY_KEY_E);
      checkMove(this->_bot1, KEY_KEY_Z, 0, 1);
      checkMove(this->_bot1, KEY_KEY_S, 0, -1);
      checkMove(this->_bot1, KEY_KEY_Q, -1, 0);
      checkMove(this->_bot1, KEY_KEY_D, 1, 0);
    }
}

void		Bomberman::clearGrid(void)
{
  for (int y = 0; y < MAP_HEIGHT; y++)
    for (int x = 0; x < MAP_WIDTH; x++)
      {
	if (this->_grid[y][x].node)
	  {
	    this->_grid[y][x].node->remove();
	    this->_grid[y][x].node = NULL;
	  }
	if (this->_grid[y][x].type == ENTITY)
	  delete (this->_grid[y][x].entity);
	this->_grid[y][x].type = EMPTY;
      }
}

void		Bomberman::init(int number_of_player)
{
  this->_numberOfPlayer = number_of_player;

  std::srand(std::time(0));
  for (int y = 0; y < MAP_HEIGHT; y++)
    for (int x = 0; x < MAP_WIDTH; x++)
      {
	this->_grid[y][x].node = NULL;
	this->_grid[y][x].type = EMPTY;
	this->_grid[y][x].entity = NULL;
	this->_grid[y][x].posX = x * this->_squareWidth;
	this->_grid[y][x].posY = y * this->_squareHeight;
	if (!x || !y || x == MAP_WIDTH - 1 || y == MAP_HEIGHT - 1 || (!(x % 2) && !(y % 2)))
	  {
	    this->_grid[y][x].type = WALL;
	    this->_grid[y][x].node = this->_graphic.manager->addCubeSceneNode();
	    if (this->_grid[y][x].node)
	      {
		this->_grid[y][x].node->setPosition(vector3df(this->_grid[y][x].posX + this->_squareWidth / 2, this->_grid[y][x].posY + this->_squareHeight / 2, 0));
		this->_grid[y][x].node->setMaterialTexture(0, this->_graphic.driver->getTexture("media/wall.bmp"));
		this->_grid[y][x].node->setMaterialFlag(video::EMF_LIGHTING, false);
	      }
	  }
	else if ((y != 1 || (x != 1 && x != 2 && x != MAP_WIDTH - 3 && x != MAP_WIDTH - 2))
		 && (y != 2 || (x != 1 && x != MAP_WIDTH - 2))
		 && (y != MAP_HEIGHT - 3 || (x != 1 && x != MAP_WIDTH - 2))
		 && (y != MAP_HEIGHT - 2 || (x != 1 && x != 2 && x != MAP_WIDTH - 3 && x != MAP_WIDTH - 2))
		 && !(rand() % 3))
	  {
	    this->_grid[y][x].type = ENTITY;
	    this->_grid[y][x].entity = new Block(x, y);
	    this->_grid[y][x].node = this->_graphic.manager->addCubeSceneNode();
	    if (this->_grid[y][x].node)
	      {
		this->_grid[y][x].node->setPosition(vector3df(this->_grid[y][x].posX + this->_squareWidth / 2, this->_grid[y][x].posY + this->_squareHeight / 2, 0));
		this->_grid[y][x].node->setMaterialTexture(0, this->_graphic.driver->getTexture(this->_grid[y][x].entity->getTexture()));
		this->_grid[y][x].node->setMaterialFlag(video::EMF_LIGHTING, false);
	      }
	  }
      }
}

void				Bomberman::runs(void)
{
  IAnimatedMesh	*meshPlayer = this->_graphic.manager->getMesh("media/I_Bomberman.3DS");
  ISceneNode	*nodePlayer = this->_graphic.manager->addMeshSceneNode(meshPlayer->getMesh(0));
  if (nodePlayer)
    {
      nodePlayer->setMaterialTexture(0, this->_graphic.driver->getTexture(this->_player.getTexture()));
      nodePlayer->setMaterialFlag(video::EMF_LIGHTING, false);
    }

  IAnimatedMesh	*meshBot = this->_graphic.manager->getMesh("media/I_Bomberman.3DS");
  ISceneNode	*nodeBot1 = this->_graphic.manager->addMeshSceneNode(meshBot->getMesh(0));
  if (nodeBot1)
    {
      nodeBot1->setMaterialTexture(0, this->_graphic.driver->getTexture(this->_bot1.getTexture()));
      nodeBot1->setMaterialFlag(video::EMF_LIGHTING, false);
    }

  ISceneNode	*nodeBot2 = this->_graphic.manager->addMeshSceneNode(meshBot->getMesh(0));
  if (nodeBot2)
    {
      nodeBot2->setMaterialTexture(0, this->_graphic.driver->getTexture(this->_bot2.getTexture()));
      nodeBot2->setMaterialFlag(video::EMF_LIGHTING, false);
    }

  ISceneNode	*nodeBot3 = this->_graphic.manager->addMeshSceneNode(meshBot->getMesh(0));
  if (nodeBot3)
    {
      nodeBot3->setMaterialTexture(0, this->_graphic.driver->getTexture(this->_bot3.getTexture()));
      nodeBot3->setMaterialFlag(video::EMF_LIGHTING, false);
    }
  
  while (this->_graphic.device->run())
    {
      this->_graphic.updateTime();
      
      bombHandler();
      eventHandler();

      nodePlayer->setPosition(vector3df(this->_player.getWPosX(), this->_player.getWPosY(), 0));
      if (this->_bot1.isAlive())
	nodeBot1->setPosition(vector3df(this->_bot1.getWPosX(), this->_bot1.getWPosY(), 0));
      else if (nodeBot1)
	{
	  nodeBot1->remove();
	  nodeBot1 = NULL;
	}
      if (this->_bot2.isAlive())
	nodeBot2->setPosition(vector3df(this->_bot2.getWPosX(), this->_bot2.getWPosY(), 0));
      else if (nodeBot2)
	{
	  
	  nodeBot2->remove();
	  nodeBot2 = NULL;
	}
      if (this->_bot3.isAlive())
	nodeBot3->setPosition(vector3df(this->_bot3.getWPosX(), this->_bot3.getWPosY(), 0));
      else if (nodeBot3)
	{
	  nodeBot3->remove();
	  nodeBot3 = NULL;
	}
      
      this->_graphic.driver->beginScene(true, true, SColor(255, 255, 255, 255));
      this->_graphic.manager->drawAll();
      this->_graphic.driver->endScene();
      this->_graphic.updateWindowCaption();

      if (!(this->_player.isAlive()))
	{
	  std::cout << "YOU LOSE!" << std::endl;
	  break;
	}
      if (!(this->_bot1.isAlive()) && !(this->_bot2.isAlive()) && !(this->_bot3.isAlive()))
	{
	  std::cout << "YOU WIN!" << std::endl;
	  break;
	}
    }
  clearGrid();
  this->_graphic.device->drop();
}
