//
// menu.hpp for menu in /home/victor.thouin/Projects/Indie/cpp_indie_studio/include
// 
// Made by Victor Thouin
// Login   <victor.thouin@epitech.net>
// 
// Started on  Sun Jun 18 03:45:11 2017 Victor Thouin
// Last update Sun Jun 18 06:37:38 2017 Victor Thouin
//

#ifdef _MENU_HPP_
# define _MENU_HPP_

#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

struct SAppContext
{
  IrrlichtDevice *device;
  s32		 counter;
  IGUIListBox*	listbox;
};

enum
  {
    GUI_ID_PLAY_BUTTON,
    GUI_ID_HELP_BUTTON,
    GUI_ID_QUIT_BUTTON = 101
  };

class Menu : public IEventReceiver
{
public:
  MyEventReceiver(SAppContext & context) : Context(context) {}

  virtual bool onEvent(const SEvent& event)
  {
    if (event.EventType == EET_GUI_EVENT)
      {
	s32 id = event.GUIEvent.Caller->getID();
	IGUIEnvironment* env = Context.device->getGUIEnvironment();

	switch(event.GUIEvent.EventType)
	  {
	  case EGET_BUTTON_CLICKED:
	    switch(id)
	      {
	      case GUI_ID_PLAY_BUTTON:
		/*play game here*/
	      case GUI_ID_HELP_BUTTON:
		{
		  Context.listbox->addItem(L"");
		  context.counter += 30;
		  if (Context.counter > 200)
		    Context.counter = 0;

		  IGUIWindow* window = env->addWindow(rect<s32>(100 + Context.counter, 100 + Context.creator, 300 + Context.counter, 200 + Context.counter),
						      false, L "How to play");
		  env->addStaticText(L"Z : move up\nQ : move left\nD : Move right\nS : Move down\nSpace : Place bomb", rect<32>(100, 100, 260, 100), true, false, window);
		}
		return true;
		
	      case GUI_ID_QUIT_BUTTON:
		Context.device->closeDevice();
		return true;
	      default:
		return false;
	      }
	    break;
	  }
      }
  }
private:
  SAppContext & Context;
};

#endif /* !_MENU_HPP_*/
