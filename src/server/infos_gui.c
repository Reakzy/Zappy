/*
** infos_gui.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/infos_gui.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Sat Jun 24 15:22:34 2017 Lucas Villeneuve
** Last update Sat Jun 24 15:22:34 2017 Lucas Villeneuve
*/

#include <stdio.h>
#include "server.h"

bool	write_tile(t_server *server, char *buf, int x, int y)
{
  snprintf(buf, 94, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
	   server->map[y][x].objects[FOOD] / 126,
	   server->map[y][x].objects[LINEMATE],
	   server->map[y][x].objects[DERAUMERE],
	   server->map[y][x].objects[SIBUR],
	   server->map[y][x].objects[MENDIANE],
	   server->map[y][x].objects[PHIRAS],
	   server->map[y][x].objects[THYSTAME]);
  if (is_queue_full(server->gui->exit_queue))
    return (false);
  insert_queue(server->gui->exit_queue, buf);
  return (true);
}

void		writing_map(t_server *server)
{
  char 		buf[95];

  while (server->w_gui.i_map.y < (int)server->y)
    {
      if (server->w_gui.i_map.x >= (int)server->x)
	server->w_gui.i_map.x = 0;
      while (server->w_gui.i_map.x < (int)server->x)
	{
	  if (!write_tile(server, buf, server->w_gui.i_map.x,
			  server->w_gui.i_map.y))
	    return ;
	  ++server->w_gui.i_map.x;
	}
      ++server->w_gui.i_map.y;
    }
  server->w_gui.map = true;
}

void		write_team(t_server *server, t_team *team)
{
  insert_queue(server->gui->exit_queue, "tna ");
  if (team->name)
    insert_queue(server->gui->exit_queue, team->name);
  insert_queue(server->gui->exit_queue, "\n");
}

void		writing_teams(t_server *server)
{
  t_item	*current;
  size_t 	j;

  if (server->teams)
    {
      j = 0;
      current = server->teams->head;
      while (current && j < server->w_gui.i_teams)
	{
	  ++j;
	  current = current->next;
	}
      while (current)
	{
	  if (is_queue_full(server->gui->exit_queue))
	    return ;
	  write_team(server, (t_team*)current->content);
	  ++server->w_gui.i_teams;
	  current = current->next;
	}
    }
  server->w_gui.teams = true;
}

void		writing_infos_gui(t_server *server)
{
  if (server->gui && server->w_gui.writing)
    {
      if (!server->w_gui.map)
	writing_map(server);
      if (!server->w_gui.teams)
	writing_teams(server);
      if (!server->w_gui.players)
	writing_players(server);
      if (!server->w_gui.eggs)
	writing_eggs(server);
      if (server->w_gui.map && server->w_gui.teams && server->w_gui.eggs &&
	  server->w_gui.players)
	{
	  init_server_w_gui(server);
	  server->w_gui.writing = false;
	}
    }
}