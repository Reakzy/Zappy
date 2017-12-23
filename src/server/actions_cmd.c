/*
** actions_cmd.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/actions_cmd.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Tue Jun 13 15:33:34 2017 Lucas Villeneuve
** Last update Tue Jun 13 15:33:34 2017 Lucas Villeneuve
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

size_t		nb_players_on_tile(const t_pos *pos, const t_list *clients)
{
  t_item	*current;
  t_client	*clnt;
  size_t	count;

  count = 0;
  if (clients)
    {
      current = clients->head;
      while (current)
	{
	  clnt = (t_client*)current->content;
	  if (clnt->logged && clnt->pos.x == pos->x && clnt->pos.y == pos->y)
	    ++count;
	  current = current->next;
	}
    }
  return (count);
}

void	send_gui_broadcast(t_server *server, t_client *client,
			       const char **msg)
{
  char	buf[15];
  int	i;

  if (server->gui)
    {
      snprintf(buf, 14, "pbc %d ", client->fd);
      insert_queue(server->gui->exit_queue, buf);
      i = 0;
      while (msg[++i] != NULL)
	{
	  insert_queue(server->gui->exit_queue, (char*)msg[i]);
	  if (msg[i + 1] != NULL)
	    insert_queue(server->gui->exit_queue, " ");
	}
      insert_queue(server->gui->exit_queue, "\n");
    }
}

void		broadcast_cmd(t_server *server, t_client *client,
				  const char **cmd)
{
  t_item	*current;
  t_client	*clnt;
  char          tile[10];

  if (server->clients && nb_players_on_tile(&client->pos, server->clients) > 0)
    {
      current = server->clients->head;
      while (current)
	{
	  clnt = (t_client *) current->content;
	  if (clnt != client && clnt->logged)
	    {
	      insert_queue(clnt->exit_queue, "message ");
	      insert_uint_queue(clnt->exit_queue, tile,
				broadcast_tile(server, client, clnt));
	      insert_queue(clnt->exit_queue, ", ");
	      write_cmd_broadcast(clnt, cmd);
	      insert_queue(clnt->exit_queue, "\n");
	    }
	  current = current->next;
	}
    }
  insert_queue(client->exit_queue, "ok\n");
  send_gui_broadcast(server, client, cmd);
}

void		eject_cmd(t_server *server, t_client *client,
			      __attribute__((unused))const char **cmd)
{
  t_item	*current;
  t_client	*clnt;

  if (nb_players_on_tile(&client->pos, server->clients) > 0)
    {
      if (server->clients)
	{
	  current = server->clients->head;
	  while (current)
	    {
	      clnt = (t_client*)current->content;
	      if (clnt != client && clnt->logged)
		eject_other_players(server, client, clnt);
	      current = current->next;
	    }
	}
      send_gui_eject(server, client);
      insert_queue(client->exit_queue, "ok\n");
    }
  else
    insert_queue(client->exit_queue, "ko\n");
}

void	fork_cmd(t_server *server, t_client *client,
		     __attribute__((unused))const char **cmd)
{
  char	buf[45];
  t_egg	egg;

  egg.team = client->team;
  egg.hatch_timer = 600;
  egg.hatched = false;
  egg.pos = client->pos;
  egg.player = client->fd;
  egg.id = server->id_eggs++;
  server->eggs->add_back(server->eggs, &egg, sizeof(egg));
  insert_queue(client->exit_queue, "ok\n");
  if (server->gui)
    {
      snprintf(buf, 44, "enw %lu %d %d %d\n",
	       egg.id, egg.player, egg.pos.x, egg.pos.y);
      insert_queue(server->gui->exit_queue, buf);
    }
}