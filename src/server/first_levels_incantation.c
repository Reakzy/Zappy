/*
** first_levels_incantation.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/first_levels_incantation.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Tue Jun 20 10:48:52 2017 Lucas Villeneuve
** Last update Tue Jun 20 10:48:52 2017 Lucas Villeneuve
*/

#include <stdio.h>
#include "server.h"

void		level_two_incantation(t_server *server, t_client *client,
					  bool first)
{
  t_tile	*tile;

  tile = &server->map[client->pos.y][client->pos.x];
  if (tile->objects[LINEMATE] == 1 && tile->objects[DERAUMERE] == 0 &&
      tile->objects[SIBUR] == 0 && tile->objects[MENDIANE] == 0 &&
      tile->objects[PHIRAS] == 0 && tile->objects[THYSTAME] == 0 &&
      nb_players_on_tile_with_lvl(&client->pos,
				  server->clients, client->level) == 1)
    increase_level_client(server, client, first);
  else
    incantation_ko(server, client, first);
}

void		level_three_incantation(t_server *server, t_client *client,
					    bool first)
{
  t_tile	*tile;

  tile = &server->map[client->pos.y][client->pos.x];
  if (tile->objects[LINEMATE] == 1 && tile->objects[DERAUMERE] == 1 &&
      tile->objects[SIBUR] == 1 && tile->objects[MENDIANE] == 0 &&
      tile->objects[PHIRAS] == 0 && tile->objects[THYSTAME] == 0 &&
      nb_players_on_tile_with_lvl(&client->pos,
				  server->clients, client->level) == 2)
    increase_level_client(server, client, first);
  else
    incantation_ko(server, client, first);
}

void		level_four_incantation(t_server *server, t_client *client,
					   bool first)
{
  t_tile	*tile;

  tile = &server->map[client->pos.y][client->pos.x];
  if (tile->objects[LINEMATE] == 2 && tile->objects[DERAUMERE] == 0 &&
      tile->objects[SIBUR] == 1 && tile->objects[MENDIANE] == 0 &&
      tile->objects[PHIRAS] == 2 && tile->objects[THYSTAME] == 0 &&
      nb_players_on_tile_with_lvl(&client->pos,
				  server->clients, client->level) == 2)
    increase_level_client(server, client, first);
  else
    incantation_ko(server, client, first);
}

void		level_five_incantation(t_server *server, t_client *client,
					   bool first)
{
  t_tile	*tile;

  tile = &server->map[client->pos.y][client->pos.x];
  if (tile->objects[LINEMATE] == 1 && tile->objects[DERAUMERE] == 1 &&
      tile->objects[SIBUR] == 2 && tile->objects[MENDIANE] == 0 &&
      tile->objects[PHIRAS] == 1 && tile->objects[THYSTAME] == 0 &&
      nb_players_on_tile_with_lvl(&client->pos,
				  server->clients, client->level) == 4)
    increase_level_client(server, client, first);
  else
    incantation_ko(server, client, first);
}

void		incantation_ko(t_server *server, t_client *client, bool first)
{
  char		buf[26];
  t_item	*current;

  if (server->clients)
    {
      current = server->clients->head;
      while (current)
	{
	  ((t_client*)current->content)->incanting = first;
	  current = current->next;
	}
    }
  insert_queue(client->exit_queue, "ko\n");
  if (!first)
    {
      if (server->gui)
	{
	  snprintf(buf, 25, "pie %d %d 0\n", client->pos.x, client->pos.y);
	  insert_queue(server->gui->exit_queue, buf);
	}
    }
}