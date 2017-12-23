/*
** look.c for vision in /home/leo/Tek2/USP_Networks/PSU_2016_zappy/src/server
** 
** Made by Leo
** Login   <leo.camberou@epitech.eu>
** 
** Started on  Tue Jun 13 13:32:19 2017 Leo
** Last update Thu Jun 15 17:17:23 2017 Leo
*/

#include <string.h>
#include <stdbool.h>
#include "server.h"

void		look_down(t_server *server, t_client *client)
{
  t_pos		pos;
  size_t	i;
  size_t	j;
  size_t	tiles_to_print;
  bool		first;

  first = true;
  tiles_to_print = 1;
  pos.x = client->pos.x;
  pos.y = client->pos.y;
  i = 0;
  while (i++ <= client->level)
    {
      j = 0;
      while (j++ < tiles_to_print)
	{
	  (!first) ? insert_queue(client->exit_queue, ",") : (first = false);
	  look_tile(server, client, &pos);
	  pos.x = MODULO(pos.x - 1, (int)server->x);
	}
      tiles_to_print += 2;
      pos.x = MODULO(client->pos.x + (int)i, (int)server->x);
      pos.y = MODULO(pos.y - 1, (int)server->y);
    }
}

void		look_right(t_server *server, t_client *client)
{
  t_pos		pos;
  size_t	i;
  size_t	j;
  size_t	tiles_to_print;
  bool		first;

  first = true;
  tiles_to_print = 1;
  pos.x = client->pos.x;
  pos.y = client->pos.y;
  i = 0;
  while (i++ <= client->level)
    {
      j = 0;
      while (j++ < tiles_to_print)
	{
	  (!first) ? insert_queue(client->exit_queue, ",") : (first = false);
	  look_tile(server, client, &pos);
	  pos.y = MODULO(pos.y - 1, (int)server->y);
	}
      tiles_to_print += 2;
      pos.y = MODULO(client->pos.y + (int)i, (int)server->y);
      pos.x = MODULO(pos.x + 1, (int)server->x);
    }
}

void		look_up(t_server *server, t_client *client)
{
  t_pos		pos;
  size_t	i;
  size_t	j;
  size_t	tiles_to_print;
  bool		first;

  first = true;
  tiles_to_print = 1;
  pos.x = client->pos.x;
  pos.y = client->pos.y;
  i = 0;
  while (i++ <= client->level)
    {
      j = 0;
      while (j++ < tiles_to_print)
	{
	  (!first) ? insert_queue(client->exit_queue, ",") : (first = false);
	  look_tile(server, client, &pos);
	  pos.x = MODULO(pos.x + 1, (int)server->x);
	}
      tiles_to_print += 2;
      pos.x = MODULO(client->pos.x - (int)i, (int)server->x);
      pos.y = MODULO(pos.y + 1, (int)server->y);
    }
}

void		look_left(t_server *server, t_client *client)
{
  t_pos		pos;
  size_t	i;
  size_t	j;
  size_t	tiles_to_print;
  bool		first;

  first = true;
  tiles_to_print = 1;
  pos.x = client->pos.x;
  pos.y = client->pos.y;
  i = 0;
  while (i++ <= client->level)
    {
      j = 0;
      while (j++ < tiles_to_print)
	{
	  (!first) ? insert_queue(client->exit_queue, ",") : (first = false);
	  look_tile(server, client, &pos);
	  pos.y = MODULO(pos.y + 1, (int)server->y);
	}
      tiles_to_print += 2;
      pos.y = MODULO(client->pos.y - (int)i, (int)server->y);
      pos.x = MODULO(pos.x - 1, (int)server->x);
    }
}