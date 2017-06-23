//
// main2.cpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sun Jun 18 07:00:20 2017 Jérémy Perry
// Last update Wed Jun 21 18:45:25 2017 Jérémy Perry
//

#include <string>
#include <iostream>
#include "Bomberman.hpp"

static int		error(const std::string &what)
{
  std::cerr << "Error: " << what << std::endl;
  return (FAILURE);
}

int			main(void)
{
  Bomberman		myGame(640, 480);

  myGame.init(2);
  myGame.runs();
  return (SUCCESS);
}
