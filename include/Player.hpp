//
// Player.hpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sun Jun 18 12:31:51 2017 Jérémy Perry
// Last update Sun Jun 18 22:13:59 2017 Jérémy Perry
//

#ifndef __PLAYER_HPP__
# define __PLAYER_HPP__

# include <string>
# include "indie_studio.hpp"

class		Player : virtual public Entity
{
private:
  std::string	_name;
  f32		_wPosX;
  f32		_wPosY;
  bool		_alive;
  int		_fire;
  int		_bombMax;
  int		_bombUsed;
  f32		_moveSpeed;
  
public:
  Player(std::string name, int numero, int win_width, int win_height);
  ~Player();

  std::string	getName() const;
  float		getWPosX() const;
  void		addWPosX(float value);
  void		addPosX(int value);
  float		getWPosY() const;
  void		addWPosY(float value);
  void		addPosY(int value);
  bool		isAlive() const;
  void		death();
  int		getFire() const;
  void		addFire();
  int		getBombMax() const;
  void		addBombMax();
  int		getBombUsed() const;
  void		addBombUsed(int value);
  float		getMoveSpeed() const;
  void		addMoveSpeed();
};

#endif /* !__PLAYER_HPP__ */
