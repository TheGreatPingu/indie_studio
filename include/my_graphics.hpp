//
// indie_studio.hpp for Indie Studio in /home/jeremy.perry/Downloads/irrlicht-1.8.4/bin/Linux/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sat Jun 10 22:13:51 2017 Jérémy Perry
// Last update Sun Jun 18 13:59:45 2017 Jérémy Perry
//

#ifndef __MY_GRAPHICS_HPP__
# define __MY_GRAPHICS_HPP__

# include "irr/irrlicht.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;
using namespace io;

// KEYBOARD HANDLER
class			MyEventReceiver : public IEventReceiver
{
private:
  bool			KeyIsDown[KEY_KEY_CODES_COUNT];
public:
  MyEventReceiver();
  virtual bool		OnEvent(const SEvent &event);
  virtual bool		IsKeyDown(EKEY_CODE keyCode) const;
};

#endif /* !__MY_GRAPHICS_HPP__ */
