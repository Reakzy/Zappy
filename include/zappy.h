/*
** zappy.h for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/zappy.h
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Fri Jun 09 14:22:35 2017 Lucas Villeneuve
** Last update Fri Jun 09 14:22:35 2017 Lucas Villeneuve
*/

#ifndef ZAPPY_H_
# define ZAPPY_H_

# define MODULO(X, Y) ((X % Y + Y) % Y)

typedef struct	s_pos
{
  int 		x;
  int 		y;
}		t_pos;

enum		e_directions
{
  NORD		= 1,
  EST		= 2,
  SUD		= 3,
  OUEST		= 4,
  MAXDIR	= 5
};

enum		e_objectType
{
  FOOD		= 0,
  LINEMATE	= 1,
  DERAUMERE	= 2,
  SIBUR		= 3,
  MENDIANE	= 4,
  PHIRAS	= 5,
  THYSTAME	= 6,
  MAXOBJECTTYPE	= 7
};

#endif /* !ZAPPY_H_ */