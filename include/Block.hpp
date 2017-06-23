//
// Block.hpp for Indie Studio in /home/jeremy.perry/Rendu/B4-C++/cpp_indie_studio
// 
// Made by Jérémy Perry
// Login   <jeremy.perry@epitech.net>
// 
// Started on  Sun Jun 18 12:23:00 2017 Jérémy Perry
// Last update Sun Jun 18 12:33:41 2017 Jérémy Perry
//

#ifndef __BLOCK_HPP__
# define __BLOCK_HPP__

# include "indie_studio.hpp"

class		Block : virtual public Entity
{
public:
  Block(int x, int y);
  ~Block();
};

#endif /* !__BLOCK_HPP */
