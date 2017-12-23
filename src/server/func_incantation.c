/*
** func_incantation.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/func_incantation.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Thu Jun 29 16:22:45 2017 Lucas Villeneuve
** Last update Thu Jun 29 16:22:45 2017 Lucas Villeneuve
*/

#include <stdio.h>
#include "server.h"

void		send_elevation_underway(t_server *server, t_client *client)
{
  t_item	*current;
  t_client	*clnt;

  if (server->clients)
    {
      current = server->clients->head;
      while (current)
	{
	  clnt = (t_client*)current->content;
	  if (clnt->logged && clnt->level == client->level &&
	      clnt->pos.x == client->pos.x && clnt->pos.y == client->pos.y)
	    {
	      insert_queue(clnt->exit_queue, "Elevation underway\n");
	      clnt->incanting = true;
	    }
	  current = current->next;
	}
    }
}

void		send_current_level(t_server *server,
				       t_client *client,
				       char *buf)
{
  t_item	*current;
  t_client	*clnt;

  if (server->clients)
    {
      current = server->clients->head;
      while (current)
	{
	  clnt = (t_client*)current->content;
	  if (clnt->logged && clnt->pos.x == client->pos.x &&
	      clnt->pos.y == client->pos.y)
	    {
	      ++clnt->level;
	      clnt->incanting = false;
	      snprintf(buf, 22, "Current level: %hd\n", clnt->level);
	      insert_queue(clnt->exit_queue, buf);
	      if (server->gui)
		{
		  snprintf(buf, 20, "plv %d %hu\n", clnt->fd, clnt->level);
		  insert_queue(server->gui->exit_queue, buf);
		}
	    }
	  current = current->next;
	}
    }
}