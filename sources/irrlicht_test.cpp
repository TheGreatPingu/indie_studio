//
// main.cpp for Indie Studio in /home/jeremy.perry/Downloads/irrlicht-1.8.4/bin/Linux/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sat Jun 10 22:17:01 2017 Jérémy Perry
// Last update Sun Jun 11 04:40:51 2017 Jérémy Perry
//

#include <string>
#include <iostream>
#include "indie_studio.hpp"

int				error(std::string err)
{
  std::cerr << "ERROR: " << err << std::endl;
  return (FAILURE);
}

int				main(void)
{
  MyEventReceiver		receiver;
  
  IrrlichtDevice		*device = irr::createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16, false, false, false, &receiver);
  if (!device)
    return (error("createDevice() failed"));
  device->setWindowCaption(L"Bomberman");
  
  IVideoDriver			*driver = device->getVideoDriver();
  ISceneManager			*smgr = device->getSceneManager();
  IGUIEnvironment		*guienv = device->getGUIEnvironment();

  guienv->addStaticText(L"See You Space Cowboy", rect<s32>(10, 10, 260, 22), true);

  IAnimatedMesh			*mesh = smgr->getMesh("media/sydney.md2");
  if (!mesh)
    {
      device->drop();
      return (error("getMesh() failed"));
    }
  
  IAnimatedMeshSceneNode	*node = smgr->addAnimatedMeshSceneNode(mesh);
  if (node)
    {
      node->setPosition(vector3df(0, 0, 100));
      node->setMaterialFlag(EMF_LIGHTING, false);
      node->setMD2Animation(scene::EMAT_STAND);
      node->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));
    }
  
  smgr->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0));

  int				lastFPS = -1;
  u32				then = device->getTimer()->getTime();
  const f32			MOVEMENT_SPEED = 20.f;
  
  while (device->run())
    {
      const u32			now = device->getTimer()->getTime();
      const f32			frameDeltaTime = (f32)(now - then) / 1000.f;
      then = now;

      vector3df			nodePosition = node->getPosition();
      if (receiver.IsKeyDown(KEY_KEY_Z))
	nodePosition.Y += MOVEMENT_SPEED * frameDeltaTime;
      if (receiver.IsKeyDown(KEY_KEY_S))
	nodePosition.Y -= MOVEMENT_SPEED * frameDeltaTime;
      if (receiver.IsKeyDown(KEY_KEY_Q))
	nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
      if (receiver.IsKeyDown(KEY_KEY_D))
	nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;
      node->setPosition(nodePosition);

      driver->beginScene(true, true, SColor(255, 100, 101, 140));
      smgr->drawAll();
      guienv->drawAll();
      driver->endScene();

      int			fps = driver->getFPS();
      if (lastFPS != fps)
	{
	  stringw		tmp(L"Bomberman (FPS: ");
	  tmp += fps;
	  tmp += ")";

	  device->setWindowCaption(tmp.c_str());
	  lastFPS = fps;
	}
    }
  
  device->drop();
  return (SUCCESS);
}
