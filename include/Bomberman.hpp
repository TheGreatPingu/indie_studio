//
// Bomberman.hpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sun Jun 18 07:21:34 2017 Jérémy Perry
// Last update Wed Jun 21 18:47:51 2017 Jérémy Perry
//

#ifndef __BOMBERMAN_HPP__
# define __BOMBERMAN_HPP__

# include <vector>
# include "irr/irrlicht.h"

# include "Bomb.hpp"
# include "Block.hpp"
# include "Player.hpp"
# include "IrrData.hpp"
# include "indie_studio.hpp"

class					Bomberman
{
private:
  t_square				_grid[MAP_HEIGHT][MAP_WIDTH];
  int					_width;
  int					_height;
  int					_squareWidth;
  int					_squareHeight;
  IrrData				_graphic;
  Player				_player;
  Player				_bot1;
  Player				_bot2;
  Player				_bot3;

  t_squareType				checkBonus(void) const;
  void					checkRange(Bomb &bomb, int x, int y);
  void					bombHandler(void);

  void					checkBomb(Player &player, EKEY_CODE key_code);
  void					checkMove(Player &player, EKEY_CODE key_code, int x, int y);
  void					eventHandler(void);

  void					clearGrid(void);
  
public:
  int					_numberOfPlayer;
  
  Bomberman(int win_width, int win_height);
  ~Bomberman();

  void					init(int number_of_player);
  void					runs(void);
};

#endif /* !__BOMBERMAN_HPP__ */
