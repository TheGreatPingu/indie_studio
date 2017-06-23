//
// bomberman.hpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Mon Jun 12 21:51:44 2017 Jérémy Perry
// Last update Sun Jun 18 05:09:12 2017 Jérémy Perry
//

#ifndef __BOMBERMAN_HPP__
# define __BOMBERMAN_HPP__

# include <string>
# include "irr/irrlicht.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;
using namespace io;

# define SUCCESS	0
# define FAILURE	84
# define LOZERE		48

# define MAP_WIDTH	13
# define MAP_HEIGHT	13

# define WIN_WIDTH	640
# define WIN_HEIGHT	480

// VALEUR DU TYPE DE L'ENTITE
typedef enum	e_entityType
  {
    PLAYER = 0,
    BLOCK,
    BOMB
  }		t_entityType;

// VALEUR DE LA FORME GRAPHIQUE DE L'ENTITE
typedef enum	e_shapeType
  {
    SPHERE = 0,
    CUBE,
    OTHER
  }		t_shapeType;

// VALEUR DU TYPE DE LA CASE
typedef enum	e_squareType
  {
    NOTHING = 'N',
    OBSTACLE = 'O',
    ENTITY = 'E',
    BONUS_BOMB = 0,
    BONUS_FIRE = 1,
    BONUS_SPEED = 2
  }		t_squareType;

// T_POS
typedef struct	s_pos
{
  int		x;
  int		y;
}		t_pos;

// DEFINITION DE LA CLASSE ENTITE
class		Entity
{
public:
  t_entityType	_type;
  t_shapeType	_shape;

  virtual ~Entity() {}
};	

// DEFINITION D'UNE CASE
typedef struct	s_square
{
  t_pos		pos;
  t_squareType	type;
  ISceneNode	*node;
  Entity	*entity;
}		t_square;

// DEFINITION DE LA CLASSE BLOCK (VIDE)
class		Block : public virtual Entity
{
public:
  Block();
  ~Block();
};

// DEFINITION DE LA CLASSE BOMB (VIDE)
class		Bomb : public virtual Entity
{
private:
  int		_blastRange;
  f32		_countDown;
public:
  Bomb(int blastRange);
  ~Bomb();

  int		getBlastRange() const;
  f32		getCountDown() const;
  void		addCountDown(f32 i);
};

// DEFINITION DE LA CLASSE PLAYER
class		Player : public virtual Entity
{
private:
  std::string	_name;
  int		_fire;
  f32		_speed;
  int		_bombMax;
  int		_bombUse;
public:
  Player(const std::string name);
  ~Player();
  Player	&operator=(const Block &model);
  Bomb*		putBomb() const;
  std::string	getName() const;
  int		getFire() const;
  void		addFire();
  int		getSpeed() const;
  void		addSpeed();
  int		getBombMax() const;
  void		addBombMax();
  int		getBombUse() const;
  void		addBombUse(int i);
};

#endif /* !__BOMBERMAN_HPP__ */
