/*
** cmd_cooldown.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/scmd_cooldown.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Sat Jun 24 11:09:39 2017 Lucas Villeneuve
** Last update Sat Jun 24 11:09:39 2017 Lucas Villeneuve
*/

#include <stdio.h>
#include "server.h"

void	inventory_cooldown(__attribute__((unused))t_server *server,
			       t_client *client)
{
  client->cooldown = 1;
}

void	connect_nbr_cooldown(__attribute__((unused))t_server *server,
				 t_client *client)
{
  client->cooldown = 0;
}

void	fork_cooldown(t_server *server, t_client *client)
{
  char	buf[15];

  client->cooldown = 42;
  if (server->gui)
    {
      snprintf(buf, 14, "pfk %d\n", client->fd);
      insert_queue(server->gui->exit_queue, buf);
    }
}

void	incantation_cooldown(t_server *server, t_client *client)
{
  char	buf[45];

  client->cooldown = 300;
  snprintf(buf, 44, "[CLIENT %d] Starting incantation\n", client->fd);
  write_on_log_file(server, buf);
  incantation_cmd(server, client, NULL);
  if (server->gui)
    {
      snprintf(buf, 44, "pic %d %d %hu %d\n",
	       client->pos.x, client->pos.y, client->level, client->fd);
      insert_queue(server->gui->exit_queue, buf);
    }
}