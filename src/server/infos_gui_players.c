/*
** infos_gui_players.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/infos_gui_players.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Sat Jun 24 15:41:26 2017 Lucas Villeneuve
** Last update Sat Jun 24 15:41:26 2017 Lucas Villeneuve
*/

#include <stdio.h>
#include "server.h"

void		write_player(t_server *server, t_client *client)
{
  char 		buf[51];

  if (client->logged)
    {
      snprintf(buf, 50, "pnw %d %d %d %d %hu ",
	       client->fd, client->pos.x, client->pos.y, client->dir,
	       client->level);
      insert_queue(server->gui->exit_queue, buf);
      if (client->team)
	insert_queue(server->gui->exit_queue, client->team->name);
      insert_queue(server->gui->exit_queue, "\n");
    }
}

void		writing_players(t_server *server)
{
  t_item	*current;
  size_t 	j;

  if (server->clients)
    {
      j = 0;
      current = server->clients->head;
      while (current && j < server->w_gui.i_players)
	{
	  ++j;
	  current = current->next;
	}
      while (current)
	{
	  if (is_queue_full(server->gui->exit_queue))
	    return ;
	  write_player(server, (t_client*)current->content);
	  ++server->w_gui.i_players;
	  current = current->next;
	}
    }
  server->w_gui.players = true;
}

void		write_egg(t_server *server, t_egg *egg)
{
  char 		buf[45];

  snprintf(buf, 44, "enw %lu %d %d %d\n", egg->id, egg->player,
	   egg->pos.x, egg->pos.y);
  insert_queue(server->gui->exit_queue, buf);
}

void		writing_eggs(t_server *server)
{
  t_item	*current;
  size_t 	j;

  if (server->eggs)
    {
      j = 0;
      current = server->eggs->head;
      while (current && j < server->w_gui.i_eggs)
	{
	  ++j;
	  current = current->next;
	}
      while (current)
	{
	  if (is_queue_full(server->gui->exit_queue))
	    return ;
	  write_egg(server, (t_egg*)current->content);
	  ++server->w_gui.i_eggs;
	  current = current->next;
	}
    }
  server->w_gui.eggs = true;
}
