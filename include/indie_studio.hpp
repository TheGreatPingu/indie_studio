//
// indie_studio.hpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sun Jun 18 11:54:42 2017 Jérémy Perry
// Last update Sun Jun 18 20:42:49 2017 Jérémy Perry
//

#ifndef __INDIE_STUDIO_HPP__
# define __INDIE_STUDIO_HPP__

# include "Entity.hpp"
# include "irr/irrlicht.h"

# define SUCCESS	(0)
# define FAILURE	(84)
# define LOZERE		(48)

# define MAP_WIDTH	(19)
# define MAP_HEIGHT	(19)

typedef enum		e_squareType
  {
    BONUS_BOMB = 0,
    BONUS_FIRE = 1,
    BONUS_SPEED = 2,
    WALL,
    EMPTY,
    ENTITY
  }			t_squareType;

typedef struct		s_square
{
  int			posX;
  int			posY;
  t_squareType		type;
  ISceneNode		*node;
  Entity		*entity;
}			t_square;

#endif /* !__INDIE_STUDIO_HPP__ */
