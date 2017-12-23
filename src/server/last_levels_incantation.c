/*
** last_levels_incantation.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/last_levels_incantation.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Tue Jun 20 10:51:28 2017 Lucas Villeneuve
** Last update Tue Jun 20 10:51:28 2017 Lucas Villeneuve
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

void		level_six_incantation(t_server *server, t_client *client,
					  bool first)
{
  t_tile	*tile;

  tile = &server->map[client->pos.y][client->pos.x];
  if (tile->objects[LINEMATE] == 1 && tile->objects[DERAUMERE] == 2 &&
      tile->objects[SIBUR] == 1 && tile->objects[MENDIANE] == 3 &&
      tile->objects[PHIRAS] == 0 && tile->objects[THYSTAME] == 0 &&
      nb_players_on_tile_with_lvl(&client->pos,
				  server->clients, client->level) == 4)
    increase_level_client(server, client, first);
  else
    incantation_ko(server, client, first);
}

void		level_seven_incantation(t_server *server, t_client *client,
					    bool first)
{
  t_tile	*tile;

  tile = &server->map[client->pos.y][client->pos.x];
  if (tile->objects[LINEMATE] == 1 && tile->objects[DERAUMERE] == 2 &&
      tile->objects[SIBUR] == 3 && tile->objects[MENDIANE] == 0 &&
      tile->objects[PHIRAS] == 1 && tile->objects[THYSTAME] == 0 &&
      nb_players_on_tile_with_lvl(&client->pos,
				  server->clients, client->level) == 6)
    increase_level_client(server, client, first);
  else
    incantation_ko(server, client, first);
}

void		level_eight_incantation(t_server *server, t_client *client,
					    bool first)
{
  t_tile	*tile;

  tile = &server->map[client->pos.y][client->pos.x];
  if (tile->objects[LINEMATE] == 2 && tile->objects[DERAUMERE] == 2 &&
      tile->objects[SIBUR] == 2 && tile->objects[MENDIANE] == 2 &&
      tile->objects[PHIRAS] == 2 && tile->objects[THYSTAME] == 1 &&
      nb_players_on_tile_with_lvl(&client->pos,
				  server->clients, client->level) == 6)
    increase_level_client(server, client, first);
  else
    incantation_ko(server, client, first);
}

void		increase_level_client(t_server *server, t_client *client,
					  bool first)
{
  char		buf[26];

  if (first)
    send_elevation_underway(server, client);
  else
    {
      if (server->gui)
	{
	  snprintf(buf, 25, "pie %d %d 1\n", client->pos.x, client->pos.y);
	  insert_queue(server->gui->exit_queue, buf);
	}
      send_current_level(server, client, buf);
    }
}

size_t		nb_players_on_tile_with_lvl(const t_pos *pos,
						  const t_list *client,
						  size_t level)
{
  t_item	*current;
  t_client	*clnt;
  size_t	count;

  count = 0;
  if (client)
    {
      current = client->head;
      while (current)
	{
	  clnt = (t_client*)current->content;
	  if (clnt->logged && clnt->pos.x == pos->x &&
	      clnt->pos.y == pos->y)
	    {
	      if (level != clnt->level)
		return (0);
	      ++count;
	    }
	  current = current->next;
	}
    }
  return (count);
}