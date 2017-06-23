//
// eventReceiver.cpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sun Jun 11 02:50:37 2017 Jérémy Perry
// Last update Fri Jun 16 22:50:03 2017 Jérémy Perry
//

#include "my_graphics.hpp"

MyEventReceiver::MyEventReceiver()
{
  for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
    KeyIsDown[i] = false;
}

bool	MyEventReceiver::OnEvent(const SEvent &event)
{
  if (event.EventType == EET_KEY_INPUT_EVENT)
    KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
  return (false);
}

bool	MyEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
  return (KeyIsDown[keyCode]);
}
