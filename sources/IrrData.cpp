//
// IrrData.cpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sun Jun 18 13:23:29 2017 Jérémy Perry
// Last update Sun Jun 18 19:23:30 2017 Jérémy Perry
//

#include "IrrData.hpp"

IrrData::IrrData(int win_width, int win_height)
{
  this->device = createDevice(video::EDT_SOFTWARE, dimension2d<u32>(win_width, win_height), 16, false, false, false, &this->receiver);
  this->driver = this->device->getVideoDriver();
  this->manager = this->device->getSceneManager();
  this->guienv = this->device->getGUIEnvironment();

  this->manager->addCameraSceneNode(0, vector3df(win_width / 2, win_height / 2, -400), vector3df(win_width / 2, win_height / 2, 0));
  
  this->_newFPS = -1;
  this->_oldFPS = -1;
  this->_newTime = this->device->getTimer()->getTime();
  this->_oldTime = this->device->getTimer()->getTime();
  this->deltaTime = 0;
}

IrrData::~IrrData()
{
  // Nothing to do here...
}

void		IrrData::updateTime()
{
  this->_newTime = this->device->getTimer()->getTime();
  this->deltaTime = (f32)(this->_newTime - this->_oldTime) / 1000.f;
  this->_oldTime = this->_newTime;
}

void		IrrData::updateWindowCaption()
{
  this->_newFPS = this->driver->getFPS();
  if (this->_oldFPS != this->_newFPS)
    {
      stringw	title(L"Bomberman (FPS: ");
      title += this->_newFPS;
      title += ")";

      this->device->setWindowCaption(title.c_str());

      this->_oldFPS = this->_newFPS; 
    }
}
