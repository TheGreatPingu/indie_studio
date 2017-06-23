//
// Entity.hpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sun Jun 18 12:56:01 2017 Jérémy Perry
// Last update Sun Jun 18 20:26:10 2017 Jérémy Perry
//

#ifndef __ENTITY_HPP__
# define __ENTITY_HPP__

# include "irr/irrlicht.h"

typedef enum		e_entityType
  {
    PLAYER,
    BLOCK,
    BOMB
  }			t_entityType;

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;
using namespace io;

class		Entity
{
private:
  path		_texture;
  int		_posX;
  int		_posY;

public:
  t_entityType	type;

  virtual ~Entity();
  
  path		getTexture() const;
  void		setTexture(const path& path);
  int		getPosX() const;
  void		setPosX(int x);
  int		getPosY() const;
  void		setPosY(int y);
};

#endif /* !__ENTITY_HPP__ */
