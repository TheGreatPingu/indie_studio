//
// IrrData.hpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sun Jun 18 13:05:44 2017 Jérémy Perry
// Last update Sun Jun 18 13:43:44 2017 Jérémy Perry
//

#ifndef __IRRLICHT_DATA_HPP__
# define __IRRLICHT_DATA_HPP__

# include "my_graphics.hpp"
# include "indie_studio.hpp"

class			IrrData
{
private:
  int			_newFPS;
  int			_oldFPS;
  u32			_newTime;
  u32			_oldTime;

public:
  MyEventReceiver	receiver;
  IrrlichtDevice	*device;
  IVideoDriver		*driver;
  ISceneManager		*manager;
  IGUIEnvironment	*guienv;

  f32			deltaTime;
  
  IrrData(int win_width, int win_height);
  ~IrrData();

  void			updateTime();
  void			updateWindowCaption();
};

#endif /* !__IRRLICHT_DATA_HPP__ */
