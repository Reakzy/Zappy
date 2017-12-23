/*
** set_tiles.c for set_tiles in /home/leo/Tek2/USP_Networks/PSU_2016_zappy
** 
** Made by Leo
** Login   <leo.camberou@epitech.eu>
** 
** Started on  Tue Jun 27 16:50:25 2017 Leo
** Last update Tue Jun 27 17:10:18 2017 Leo
*/

#include <stdlib.h>
#include <stdio.h>
#include "server.h"

int		place_rock_on_tile(t_server *server, t_pos *pos, int *rocks)
{
  int		obj;
  int           rarity;
  int           i;

  obj = 0;
  i = 0;
  rarity = (int)(random() % 100);
  while (++i <= MAXOBJECTTYPE)
    if (rarity < rocks[i])
      {
	obj = i - 1;
	i = MAXOBJECTTYPE;
      }
  (obj == FOOD) ? (server->map[pos->y][pos->x].objects[obj] += 126)
		: (server->map[pos->y][pos->x].objects[obj] += 1);
  return (obj);
}

void		set_tile(t_server *server, t_pos *pos)
{
  char		buf[95];
  int           intervals[MAXOBJECTTYPE + 1];
  int		obj;

  intervals[FOOD] = 0;
  intervals[LINEMATE] = 60;
  intervals[DERAUMERE] = 73;
  intervals[SIBUR] = 83;
  intervals[MENDIANE] = 89;
  intervals[PHIRAS] = 94;
  intervals[THYSTAME] = 97;
  intervals[MAXOBJECTTYPE] = 100;
  obj = place_rock_on_tile(server, pos, intervals);
  snprintf(buf, 66, "[MAP] Adding stone : %d at x : %d and y : %d\n",
	   obj, pos->x, pos->y);
  write_on_log_file(server, buf);
  if (server->gui)
    write_tile(server, buf, pos->x, pos->y);
}
