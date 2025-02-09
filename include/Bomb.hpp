//
// Bomb.hpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sun Jun 18 12:03:09 2017 Jérémy Perry
// Last update Sun Jun 18 20:12:10 2017 Jérémy Perry
//

#ifndef __BOMB_HPP__
# define __BOMB_HPP__

# include "indie_studio.hpp"
# include "Player.hpp"

class			Bomb : virtual public Entity
{
private:
  Player&		_author;
  const int		_range;
  f32			_countDown;

public:
  Bomb(Player& author);
  ~Bomb();

  Player&		getAuthor() const;
  int			getRange() const;
  f32			getCountDown() const;
  void			addCountDown(f32 val);
};

#endif /* !__BOMB_HPP__ */
