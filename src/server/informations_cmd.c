/*
** informations_cmd.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/informations_cmd.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Tue Jun 13 15:32:01 2017 Lucas Villeneuve
** Last update Tue Jun 13 15:32:01 2017 Lucas Villeneuve
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

void	insert_uint_queue(t_queue *queue, char *buf, size_t nb)
{
  memset(buf, 0, 10);
  snprintf(buf, 9, "%lu", nb);
  insert_queue(queue, buf);
}

void	insert_uint_queue_nl(t_queue *queue, char *buf, size_t nb)
{
  memset(buf, 0, 11);
  snprintf(buf, 10, "%lu\n", nb);
  insert_queue(queue, buf);
}

void		look_cmd(t_server *server, t_client *client,
			     __attribute__((unused))const char **cmd)
{
  size_t	i;
  void		(*look_func[MAXDIR - 1])(t_server*, t_client*);

  insert_queue(client->exit_queue, "[");
  look_func[NORD - 1] = &look_up;
  look_func[EST - 1] = &look_right;
  look_func[SUD - 1] = &look_down;
  look_func[OUEST - 1] = &look_left;
  i = 0;
  while (i < MAXDIR - 1)
    {
      if (client->dir - 1 == i)
	{
	  look_func[i](server, client);
	  return (insert_queue(client->exit_queue, "]\n"));
	}
      ++i;
    }
}

void	inventory_cmd(__attribute__((unused))t_server *server,
			  t_client *client,
			  __attribute__((unused))const char **cmd)
{
  char	buf[12];

  insert_queue(client->exit_queue, "[food ");
  insert_uint_queue(client->exit_queue, buf, client->objects[FOOD] / 126);
  insert_queue(client->exit_queue, ", linemate ");
  insert_uint_queue(client->exit_queue, buf, client->objects[LINEMATE]);
  insert_queue(client->exit_queue, ", deraumere ");
  insert_uint_queue(client->exit_queue, buf, client->objects[DERAUMERE]);
  insert_queue(client->exit_queue, ", sibur ");
  insert_uint_queue(client->exit_queue, buf, client->objects[SIBUR]);
  insert_queue(client->exit_queue, ", mendiane ");
  insert_uint_queue(client->exit_queue, buf, client->objects[MENDIANE]);
  insert_queue(client->exit_queue, ", phiras ");
  insert_uint_queue(client->exit_queue, buf, client->objects[PHIRAS]);
  insert_queue(client->exit_queue, ", thystame ");
  insert_uint_queue(client->exit_queue, buf, client->objects[THYSTAME]);
  insert_queue(client->exit_queue, "]\n");
}

void	connect_nbr_cmd(__attribute__((unused))t_server *server,
			    t_client *client,
			    __attribute__((unused))const char **cmd)
{
  char	buf[12];

  if (client->team)
    insert_uint_queue(client->exit_queue, buf, client->team->nbClientsLeft);
  else
    {
      fprintf(stderr, "Client doesn't have a team\n");
      insert_uint_queue(client->exit_queue, buf, 0);
      return ;
    }
  insert_queue(client->exit_queue, "\n");
}