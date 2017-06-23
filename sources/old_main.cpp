//
// main.cpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Wed Jun 14 00:38:01 2017 Jérémy Perry
// Last update Sun Jun 18 06:59:39 2017 Jérémy Perry
//

#include <ctime>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <iostream>
#include "bomberman.hpp"
#include "my_graphics.hpp"

static int		error(const std::string what)
{
  std::cerr << "Error: " << what << std::endl;
  return(FAILURE);
}

int			main(void)
{
  MyEventReceiver	receiver;
  t_square		grid[MAP_HEIGHT][MAP_WIDTH];
  t_pos			index;
  Player		player("Joueur 1");
  t_pos			playerMapPos;
  bool			isDead = false;
  io::path		bonusTexture[3] = {"media/portal1.bmp", "media/particlered.bmp", "media/particlewhite.bmp"};
  
  IrrlichtDevice	*device = createDevice(video::EDT_SOFTWARE, dimension2d<u32>(WIN_WIDTH, WIN_HEIGHT), 16, false, false, false, &receiver);
  if (!device)
    return (error("failed to create Irrlicht device"));
  device->setWindowCaption(L"Bomberman");

  IVideoDriver		*driver = device->getVideoDriver();
  ISceneManager		*smgr = device->getSceneManager();
  IGUIEnvironment	*guienv = device->getGUIEnvironment();
  smgr->addCameraSceneNode(0, vector3df(WIN_WIDTH / 2, WIN_HEIGHT / 2, -400), vector3df(WIN_WIDTH / 2, WIN_HEIGHT / 2, 0));


  // INITIALISATION DE LA MAP
  for (index.y = 0; index.y < MAP_HEIGHT; index.y++)
    for (index.x = 0; index.x < MAP_WIDTH; index.x++)
      {
	grid[index.y][index.x].pos.x = (index.x * (WIN_WIDTH / MAP_WIDTH));
	grid[index.y][index.x].pos.y = (index.y * (WIN_HEIGHT / MAP_HEIGHT));
	grid[index.y][index.x].type = NOTHING;
	grid[index.y][index.x].node = NULL;
	grid[index.y][index.x].entity = NULL;
	if (!index.y || !index.x || index.y == MAP_HEIGHT - 1 || index.x == MAP_WIDTH - 1 || (!(index.y % 2) && !(index.x % 2)))
	  {
	    grid[index.y][index.x].type = OBSTACLE;
	    grid[index.y][index.x].node = smgr->addCubeSceneNode();
	  }	    
	else if ((index.x == 1 && index.y == MAP_HEIGHT - 2) || (index.x == MAP_WIDTH - 2 && index.y == 1) || (index.x == MAP_WIDTH - 2 && index.y == MAP_HEIGHT - 2))
	  {
	    grid[index.y][index.x].type = ENTITY;
	    grid[index.y][index.x].entity = new Player("Anonymous");
	    grid[index.y][index.x].node = smgr->addSphereSceneNode();
	  }
	else if ((index.x != 1 || (index.y != 2 && index.y != MAP_HEIGHT - 3)) && (index.x != 2 || (index.y != 1 && index.y != MAP_HEIGHT - 2)) &&
		 (index.x != MAP_WIDTH - 3 || (index.y != 1 && index.y != MAP_HEIGHT - 2)) && (index.x != MAP_WIDTH - 2 || (index.y != 2 && index.y != MAP_HEIGHT - 3)) &&
		 (index.x != 1 || index.y != 1))
	  {
	    grid[index.y][index.x].type = ENTITY;
	    grid[index.y][index.x].entity = new Block();
	    grid[index.y][index.x].node = smgr->addCubeSceneNode();
	  }
	if (grid[index.y][index.x].node)
	  {
	    grid[index.y][index.x].node->setPosition(vector3df(grid[index.y][index.x].pos.x + (WIN_WIDTH / MAP_WIDTH) / 2,
							       grid[index.y][index.x].pos.y + (WIN_WIDTH / MAP_WIDTH) / 2, 0));
	    if (grid[index.y][index.x].type == OBSTACLE || (grid[index.y][index.x].type == ENTITY && grid[index.y][index.x].entity->_type == PLAYER))
		grid[index.y][index.x].node->setMaterialTexture(0, driver->getTexture("media/wall.bmp"));
	    grid[index.y][index.x].node->setMaterialFlag(video::EMF_LIGHTING, false);
	  }
      }

  // INITIALISATION DU JOUEUR
  playerMapPos.x = 1;
  playerMapPos.y = 1;
  ISceneNode	*playerNode = smgr->addSphereSceneNode();
  if (playerNode)
    {
      playerNode->setPosition(vector3df((WIN_WIDTH / MAP_WIDTH) + (WIN_WIDTH / MAP_WIDTH) / 2, (WIN_HEIGHT / MAP_HEIGHT) + (WIN_HEIGHT / MAP_HEIGHT) / 2, 0));
      playerNode->setMaterialTexture(0, driver->getTexture("media/wall.bmp"));
      playerNode->setMaterialFlag(video::EMF_LIGHTING, false);
    }

  std::srand(std::time(0));
  
  // BOUCLE D'EXECUTION
  int			lastFPS = -1;
  u32			then = device->getTimer()->getTime();
  const f32		movementSpeed = 20.f;
  while (device->run())
    { 
      const u32		now = device->getTimer()->getTime();
      const f32		frameDeltaTime = (f32)(now - then) / 1000.f;
      then = now;

      vector3df		playerPosition = playerNode->getPosition();

      // GESTION DES BOMBES
      for (index.y = 0; index.y < MAP_HEIGHT; index.y++)
	for (index.x = 0; index.x < MAP_WIDTH; index.x++)
	  if (grid[index.y][index.x].type == ENTITY && grid[index.y][index.x].entity->_type == BOMB)
	    {
	      dynamic_cast<Bomb*>(grid[index.y][index.x].entity)->addCountDown(-frameDeltaTime);
	      if (dynamic_cast<Bomb*>(grid[index.y][index.x].entity)->getCountDown() < 0)
		{
		  int	i;
		  
		  grid[index.y][index.x].node->remove();
		  grid[index.y][index.x].node = NULL;
		  if (index.y == playerMapPos.y && index.x == playerMapPos.x)
		    isDead = true;

		  // CHECK TOP RANGE
		  for (i = 1; i <= dynamic_cast<Bomb*>(grid[index.y][index.x].entity)->getBlastRange() && grid[index.y + i][index.x].type != OBSTACLE; i++)
		    {
		      if (grid[index.y + i][index.x].type == ENTITY)
			{
			  grid[index.y + i][index.x].type = NOTHING;
			  grid[index.y + i][index.x].node->remove();
			  grid[index.y + i][index.x].node = NULL;
			  if (grid[index.y + i][index.x].entity->_type == BLOCK)
			    {
			      int	isBonus = std::rand() % 9;
			      if (isBonus < 3)
				{
				  grid[index.y + i][index.x].type = static_cast<t_squareType>(isBonus);
				  grid[index.y + i][index.x].node = smgr->addSphereSceneNode();
				  if (grid[index.y + i][index.x].node)
				    {
				      grid[index.y + i][index.x].node->setPosition(vector3df(grid[index.y + i][index.x].pos.x + (WIN_WIDTH / MAP_WIDTH) / 2,
											     grid[index.y + i][index.x].pos.y + (WIN_HEIGHT / MAP_HEIGHT) / 2, 0));
				      grid[index.y + i][index.x].node->setMaterialTexture(0, driver->getTexture(bonusTexture[isBonus]));
				      grid[index.y + i][index.x].node->setMaterialFlag(video::EMF_LIGHTING, false);
				    }
				}
			    }
			  delete (grid[index.y + i][index.x].entity);
			  grid[index.y + i][index.x].entity = NULL;
			  break;
			}
		      if (index.y + i == playerMapPos.y && index.x == playerMapPos.x)
			isDead = true;
		    }

		  // CHECK BOTTOM RANGE
		  for (i = 1; i <= dynamic_cast<Bomb*>(grid[index.y][index.x].entity)->getBlastRange() && grid[index.y - i][index.x].type != OBSTACLE; i++)
		    {
		      if (grid[index.y - i][index.x].type == ENTITY)
			{
			  grid[index.y - i][index.x].node->remove();
			  grid[index.y - i][index.x].node = NULL;
			  grid[index.y - i][index.x].type = NOTHING;
			  if (grid[index.y - i][index.x].entity->_type == BLOCK)
			    {
			      int	isBonus = std::rand() % 9;
			      if (isBonus < 3)
				{
				  grid[index.y - i][index.x].type = static_cast<t_squareType>(isBonus);
				  grid[index.y - i][index.x].node = smgr->addSphereSceneNode();
				  if (grid[index.y - i][index.x].node)
				    {
				      grid[index.y - i][index.x].node->setPosition(vector3df(grid[index.y - i][index.x].pos.x + (WIN_WIDTH / MAP_WIDTH) / 2,
											     grid[index.y - i][index.x].pos.y + (WIN_HEIGHT / MAP_HEIGHT) / 2, 0));
				      grid[index.y - i][index.x].node->setMaterialTexture(0, driver->getTexture(bonusTexture[isBonus]));
				      grid[index.y - i][index.x].node->setMaterialFlag(video::EMF_LIGHTING, false);
				    }
				}
			    }
			  delete (grid[index.y - i][index.x].entity);
			  grid[index.y - i][index.x].entity = NULL;
			  break;
			}
		      if (index.y - i == playerMapPos.y && index.x == playerMapPos.x)
			isDead = true;
		    }

		  // CHECK RIGHT RANGE
		  for (i = 1; i <= dynamic_cast<Bomb*>(grid[index.y][index.x].entity)->getBlastRange() && grid[index.y][index.x + i].type != OBSTACLE; i++)
		    {
		      if (grid[index.y][index.x + i].type == ENTITY)
			{
			  grid[index.y][index.x + i].node->remove();
			  grid[index.y][index.x + i].node = NULL;
			  grid[index.y][index.x + i].type = NOTHING;
			  if (grid[index.y][index.x + i].entity->_type == BLOCK)
			    {
			      int	isBonus = std::rand() % 9;
			      if (isBonus >= 0 && isBonus < 3)
				{
				  grid[index.y][index.x + i].type = static_cast<t_squareType>(isBonus);
				  grid[index.y][index.x + i].node = smgr->addSphereSceneNode();
				  if (grid[index.y][index.x + i].node)
				    {
				      grid[index.y][index.x + i].node->setPosition(vector3df(grid[index.y][index.x + i].pos.x + (WIN_WIDTH / MAP_WIDTH) / 2,
											     grid[index.y][index.x + i].pos.y + (WIN_HEIGHT / MAP_HEIGHT) / 2, 0));
				      grid[index.y][index.x + i].node->setMaterialTexture(0, driver->getTexture(bonusTexture[isBonus]));
				      grid[index.y][index.x + i].node->setMaterialFlag(video::EMF_LIGHTING, false);
				    }
				}
			    }			  
			  delete (grid[index.y][index.x + i].entity);
			  grid[index.y][index.x + i].entity = NULL;
			  break;
			}
		      if (index.y == playerMapPos.y && index.x + i == playerMapPos.x)
			isDead = true;
		    }

		  // CHECK LEFT RANGE
		  for (i = 1; i <= dynamic_cast<Bomb*>(grid[index.y][index.x].entity)->getBlastRange() && grid[index.y][index.x - i].type != OBSTACLE; i++)
		    {
		      if (grid[index.y][index.x - i].type == ENTITY)
			{
			  grid[index.y][index.x - i].node->remove();
			  grid[index.y][index.x - i].node = NULL;
			  grid[index.y][index.x - i].type = NOTHING;
			  if (grid[index.y][index.x - i].entity->_type == BLOCK)
			    {
			      int	isBonus = std::rand() % 9;
			      if (isBonus < 3)
				{
				  grid[index.y][index.x - i].type = static_cast<t_squareType>(isBonus);
				  grid[index.y][index.x - i].node = smgr->addSphereSceneNode();
				  if (grid[index.y][index.x - i].node)
				    {
				      grid[index.y][index.x - i].node->setPosition(vector3df(grid[index.y][index.x - i].pos.x + (WIN_WIDTH / MAP_WIDTH) / 2,
											     grid[index.y][index.x - i].pos.y + (WIN_HEIGHT / MAP_HEIGHT) / 2, 0));
				      grid[index.y][index.x - i].node->setMaterialTexture(0, driver->getTexture(bonusTexture[isBonus]));
				      grid[index.y][index.x - i].node->setMaterialFlag(video::EMF_LIGHTING, false);
				    }
				}
			    }			  
			  delete (grid[index.y][index.x - i].entity);
			  grid[index.y][index.x - i].entity = NULL;
			  break;
			}
		      if (index.y == playerMapPos.y && index.x - i == playerMapPos.x)
			isDead = true;
		    }
		  delete (grid[index.y][index.x].entity);
		  grid[index.y][index.x].entity = NULL;
		  grid[index.y][index.x].type = NOTHING;
		  player.addBombUse(-1);
		}
	    }
	
      // EVENT RECEIVER - DOWN
      if (receiver.IsKeyDown(KEY_DOWN))
	{
	  if (playerPosition.Y - player.getSpeed() * frameDeltaTime > grid[playerMapPos.y][playerMapPos.x].pos.y)
	    playerPosition.Y -= player.getSpeed() * frameDeltaTime;
	  else if (playerPosition.Y - player.getSpeed() * frameDeltaTime < grid[playerMapPos.y][playerMapPos.x].pos.y
		   && grid[playerMapPos.y - 1][playerMapPos.x].type == NOTHING)
	    {
	      playerPosition.Y -= player.getSpeed() * frameDeltaTime;
	      playerMapPos.y--;
	    }
	  else if (playerPosition.Y - player.getSpeed() * frameDeltaTime < grid[playerMapPos.y][playerMapPos.x].pos.y
		   && grid[playerMapPos.y - 1][playerMapPos.x].type == BONUS_BOMB)
	    {
	      player.addBombMax();
	      playerPosition.Y -= player.getSpeed() * frameDeltaTime;
	      playerMapPos.y--;
	      grid[playerMapPos.y][playerMapPos.x].type = NOTHING;
	      grid[playerMapPos.y][playerMapPos.x].node->remove();
	      grid[playerMapPos.y][playerMapPos.x].node = NULL;
	    }
	  else if (playerPosition.Y - player.getSpeed() * frameDeltaTime < grid[playerMapPos.y][playerMapPos.x].pos.y
		   && grid[playerMapPos.y - 1][playerMapPos.x].type == BONUS_FIRE)
	    {
	      player.addFire();
	      playerPosition.Y -= player.getSpeed() * frameDeltaTime;
	      playerMapPos.y--;
	      grid[playerMapPos.y][playerMapPos.x].type = NOTHING;
	      grid[playerMapPos.y][playerMapPos.x].node->remove();
	      grid[playerMapPos.y][playerMapPos.x].node = NULL;
	    }
	  else if (playerPosition.Y - player.getSpeed() * frameDeltaTime < grid[playerMapPos.y][playerMapPos.x].pos.y
		   && grid[playerMapPos.y - 1][playerMapPos.x].type == BONUS_SPEED)
	    {
	      player.addSpeed();
	      playerPosition.Y -= player.getSpeed() * frameDeltaTime;
	      playerMapPos.y--;
	      grid[playerMapPos.y][playerMapPos.x].type = NOTHING;
	      grid[playerMapPos.y][playerMapPos.x].node->remove();
	      grid[playerMapPos.y][playerMapPos.x].node = NULL;	      
	    }	  
	}
      // EVENT RECEIVER - UP
      if (receiver.IsKeyDown(KEY_UP))
	{
	  if (playerPosition.Y + player.getSpeed() * frameDeltaTime < grid[playerMapPos.y + 1][playerMapPos.x].pos.y)
	    playerPosition.Y += player.getSpeed() * frameDeltaTime;
	  else if (playerPosition.Y + player.getSpeed() * frameDeltaTime > grid[playerMapPos.y + 1][playerMapPos.x].pos.y
		   && grid[playerMapPos.y + 1][playerMapPos.x].type == NOTHING)
	    {
	      playerPosition.Y += player.getSpeed() * frameDeltaTime;
	      playerMapPos.y++;
	    }
	  else if (playerPosition.Y + player.getSpeed() * frameDeltaTime > grid[playerMapPos.y + 1][playerMapPos.x].pos.y
		   && grid[playerMapPos.y + 1][playerMapPos.x].type == BONUS_BOMB)
	    {
	      player.addBombMax();
	      playerPosition.Y += player.getSpeed() * frameDeltaTime;
	      playerMapPos.y++;
	      grid[playerMapPos.y][playerMapPos.x].type = NOTHING;
	      grid[playerMapPos.y][playerMapPos.x].node->remove();
	      grid[playerMapPos.y][playerMapPos.x].node = NULL;
	    }
	  else if (playerPosition.Y + player.getSpeed() * frameDeltaTime > grid[playerMapPos.y + 1][playerMapPos.x].pos.y
		   && grid[playerMapPos.y + 1][playerMapPos.x].type == BONUS_FIRE)
	    {
	      player.addFire();
	      playerPosition.Y += player.getSpeed() * frameDeltaTime;
	      playerMapPos.y++;
	      grid[playerMapPos.y][playerMapPos.x].type = NOTHING;
	      grid[playerMapPos.y][playerMapPos.x].node->remove();
	      grid[playerMapPos.y][playerMapPos.x].node = NULL;
	    }
	  else if (playerPosition.Y + player.getSpeed() * frameDeltaTime > grid[playerMapPos.y + 1][playerMapPos.x].pos.y
		   && grid[playerMapPos.y + 1][playerMapPos.x].type == BONUS_SPEED)
	    {
	      player.addSpeed();
	      playerPosition.Y += player.getSpeed() * frameDeltaTime;
	      playerMapPos.y++;
	      grid[playerMapPos.y][playerMapPos.x].type = NOTHING;
	      grid[playerMapPos.y][playerMapPos.x].node->remove();
	      grid[playerMapPos.y][playerMapPos.x].node = NULL;	      
	    }
	}
      // EVENT RECEIVER - LEFT
      if (receiver.IsKeyDown(KEY_LEFT))
	{
	  if (playerPosition.X - player.getSpeed() * frameDeltaTime > grid[playerMapPos.y][playerMapPos.x].pos.x)
	    playerPosition.X -= player.getSpeed() * frameDeltaTime;
	  else if (playerPosition.X - player.getSpeed() * frameDeltaTime < grid[playerMapPos.y][playerMapPos.x].pos.x
		   && grid[playerMapPos.y][playerMapPos.x - 1].type == NOTHING)
	    {
	      playerPosition.X -= player.getSpeed() * frameDeltaTime;
	      playerMapPos.x--;
	    }
	  else if (playerPosition.X - player.getSpeed() * frameDeltaTime > grid[playerMapPos.y][playerMapPos.x].pos.x
		   && grid[playerMapPos.y][playerMapPos.x - 1].type == BONUS_BOMB)
	    {
	      player.addBombMax();
	      playerPosition.X -= player.getSpeed() * frameDeltaTime;
	      playerMapPos.x--;
	      grid[playerMapPos.y][playerMapPos.x].type = NOTHING;
	      grid[playerMapPos.y][playerMapPos.x].node->remove();
	      grid[playerMapPos.y][playerMapPos.x].node = NULL;
	    }
	  else if (playerPosition.X - player.getSpeed() * frameDeltaTime > grid[playerMapPos.y][playerMapPos.x].pos.x
		   && grid[playerMapPos.y][playerMapPos.x - 1].type == BONUS_FIRE)
	    {
	      player.addFire();
	      playerPosition.X -= player.getSpeed() * frameDeltaTime;
	      playerMapPos.x--;
	      grid[playerMapPos.y][playerMapPos.x].type = NOTHING;
	      grid[playerMapPos.y][playerMapPos.x].node->remove();
	      grid[playerMapPos.y][playerMapPos.x].node = NULL;
	    }
	  else if (playerPosition.X - player.getSpeed() * frameDeltaTime > grid[playerMapPos.y][playerMapPos.x].pos.x
		   && grid[playerMapPos.y][playerMapPos.x - 1].type == BONUS_SPEED)
	    {
	      player.addSpeed();
	      playerPosition.X -= player.getSpeed() * frameDeltaTime;
	      playerMapPos.x--;
	      grid[playerMapPos.y][playerMapPos.x].type = NOTHING;
	      grid[playerMapPos.y][playerMapPos.x].node->remove();
	      grid[playerMapPos.y][playerMapPos.x].node = NULL;	      
	    }
	}
      // EVENT RECEIVER - RIGHT
      if (receiver.IsKeyDown(KEY_RIGHT))
	{
	  if (playerPosition.X + player.getSpeed() * frameDeltaTime < grid[playerMapPos.y][playerMapPos.x + 1].pos.x)
	    playerPosition.X += player.getSpeed() * frameDeltaTime;
	  else if (playerPosition.X + player.getSpeed() * frameDeltaTime > grid[playerMapPos.y][playerMapPos.x + 1].pos.x
		   && grid[playerMapPos.y][playerMapPos.x + 1].type == NOTHING)
	    {
	      playerPosition.X += player.getSpeed() * frameDeltaTime;
	      playerMapPos.x++;
	    }
	  else if (playerPosition.X + player.getSpeed() * frameDeltaTime > grid[playerMapPos.y][playerMapPos.x + 1].pos.x
		   && grid[playerMapPos.y][playerMapPos.x + 1].type == BONUS_BOMB)
	    {
	      player.addBombMax();
	      playerPosition.X += player.getSpeed() * frameDeltaTime;
	      playerMapPos.x++;
	      grid[playerMapPos.y][playerMapPos.x].type = NOTHING;
	      grid[playerMapPos.y][playerMapPos.x].node->remove();
	      grid[playerMapPos.y][playerMapPos.x].node = NULL;
	    }
	  else if (playerPosition.X + player.getSpeed() * frameDeltaTime > grid[playerMapPos.y][playerMapPos.x + 1].pos.x
		   && grid[playerMapPos.y][playerMapPos.x + 1].type == BONUS_FIRE)
	    {
	      player.addFire();
	      playerPosition.X += player.getSpeed() * frameDeltaTime;
	      playerMapPos.x++;
	      grid[playerMapPos.y][playerMapPos.x].type = NOTHING;
	      grid[playerMapPos.y][playerMapPos.x].node->remove();
	      grid[playerMapPos.y][playerMapPos.x].node = NULL;
	    }
	  else if (playerPosition.X + player.getSpeed() * frameDeltaTime > grid[playerMapPos.y][playerMapPos.x + 1].pos.x
		   && grid[playerMapPos.y][playerMapPos.x + 1].type == BONUS_SPEED)
	    {
	      player.addSpeed();
	      playerPosition.X += player.getSpeed() * frameDeltaTime;
	      playerMapPos.x++;
	      grid[playerMapPos.y][playerMapPos.x].type = NOTHING;
	      grid[playerMapPos.y][playerMapPos.x].node->remove();
	      grid[playerMapPos.y][playerMapPos.x].node = NULL;
	    }
	}
      // EVENT RECEIVER - SPACE (BOMB)
      if (receiver.IsKeyDown(KEY_SPACE) && player.getBombMax() - player.getBombUse() > 0)
	{
	  player.addBombUse(1);
	  grid[playerMapPos.y][playerMapPos.x].type = ENTITY;
	  grid[playerMapPos.y][playerMapPos.x].entity = new Bomb(player.getFire());
	  grid[playerMapPos.y][playerMapPos.x].node = smgr->addSphereSceneNode();
	  if (grid[playerMapPos.y][playerMapPos.x].node)
	    {
	      grid[playerMapPos.y][playerMapPos.x].node->setPosition(vector3df(grid[playerMapPos.y][playerMapPos.x].pos.x + (WIN_WIDTH / MAP_WIDTH) / 2, grid[playerMapPos.y][playerMapPos.x].pos.y + (WIN_HEIGHT / MAP_HEIGHT) / 2, 0));
	      grid[playerMapPos.y][playerMapPos.x].node->setMaterialFlag(video::EMF_LIGHTING, true);
	    }
	}
      playerNode->setPosition(playerPosition);
      
      // AFFICHAGE
      driver->beginScene(true, true, SColor(255, 100, 101, 140));
      smgr->drawAll();
      driver->endScene();

      // TITRE DE LA FENETRE & FPS
      int fps = driver->getFPS();
      if (lastFPS != fps)
	{
	  stringw	tmp(L"Bomberman (FPS: ");
	  tmp += fps;
	  tmp += ")";
	  device->setWindowCaption(tmp.c_str());
	  lastFPS = fps;
	}
      if (isDead)
	{
	  std::cout << "YOU LOSE!" << std::endl;
	  break ;
	}
    }

  // CLEAR & END
  for (index.y = 0; index.y < MAP_HEIGHT; index.y++)
    for (index.x = 0; index.x < MAP_WIDTH; index.x++)
      if (grid[index.y][index.x].type == ENTITY)
	delete grid[index.y][index.x].entity;
  device->drop();
  return (SUCCESS);
}
