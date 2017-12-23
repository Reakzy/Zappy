/*
** set_map.c for set_map in /home/leo/Tek2/USP_Networks/PSU_2016_zappy/src
**
** Made by Leo
** Login   <leo.camberou@epitech.eu>
**
** Started on  Mon Jun 12 14:16:23 2017 Leo
** Last update Tue Jun 13 13:06:00 2017 Leo
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "server.h"

t_tile		**init_map(t_params *params)
{
  t_tile       	**map;
  size_t       	y;
  size_t	x;
  size_t 	i;

  if ((map = calloc(params->height, sizeof(t_tile*))) == NULL)
    return (NULL);
  y = 0;
  while (y < params->height)
    {
      x = 0;
      if ((map[y] = calloc(params->width, sizeof(t_tile))) == NULL)
	return (NULL);
      while (x < params->width)
	{
	  i = 0;
	  while (i < MAXOBJECTTYPE)
	    map[y][x].objects[i++] = 0;
	  x++;
	}
      y++;
    }
  return (map);
}

void		print_log_map(t_server *server)
{
  t_pos		pos;
  int		i;
  char		buf[67];

  pos.y = 0;
  while (pos.y < (int)server->y)
    {
      pos.x = 0;
      while (pos.x < (int)server->x)
	{
	  i = -1;
	  while (++i < MAXOBJECTTYPE)
	    if (server->map[pos.y][pos.x].objects[i] != 0)
	      {
		snprintf(buf, 66,
			 "[MAP] Adding stone : %d at x : %d and y : %d\n",
			 i, pos.x, pos.y);
		write_on_log_file(server, buf);
	      }
	  ++pos.x;
	}
      ++pos.y;
    }
}

t_tile		**set_map(t_server *server, t_params *params)
{
  t_tile	**map;
  size_t	count;
  size_t	count_max;
  t_pos		pos;

  if (!(map = init_map(params)))
    return (NULL);
  srandom((unsigned int)time(NULL));
  count = 0;
  count_max = params->width * params->height;
  server->map = map;
  while (count++ < count_max)
    {
      pos.x = (int)(random() % params->width);
      pos.y = (int)(random() % params->height);
      set_tile(server, &pos);
    }
  return (map);
}

void		free_map(t_server *server)
{
  size_t	i;

  i = 0;
  while (i < server->y)
    {
      if (server->map[i])
	free(server->map[i]);
      ++i;
    }
  free(server->map);
}

void	place_rocks_map(t_server *server)
{
  t_pos	pos;

  if (++server->rocks > TICKS_SPAWN_ROCKS)
    {
      pos.x = (int)(random() % server->x);
      pos.y = (int)(random() % server->y);
      while (nb_players_on_tile(&pos, server->clients) != 0)
	{
	  pos.x = (int)(random() % server->x);
	  pos.y = (int)(random() % server->y);
	}
      set_tile(server, &pos);
      server->rocks = 0;
    }
}