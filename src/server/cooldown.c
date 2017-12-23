/*
** cooldown.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/cooldown.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Mon Jun 19 13:37:50 2017 Lucas Villeneuve
** Last update Mon Jun 19 13:37:50 2017 Lucas Villeneuve
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

void	check_level_client(t_server *server, t_client *client)
{
  if (!server->end && client->level == 8)
    {
      server->end = true;
      if (server->gui)
	{
	  insert_queue(server->gui->exit_queue, "seg ");
	  if (client->team && client->team->name)
	    insert_queue(server->gui->exit_queue, client->team->name);
	  insert_queue(server->gui->exit_queue, "\n");
	}
    }
}

void		write_cmd_log(t_server *server, t_client *client, char *str)
{
  char		buf[21];

  if (client->logged)
    {
      snprintf(buf, 20, "[CLIENT %d] ", client->fd);
      write_on_log_file(server, buf);
      write_on_log_file(server, str);
    }
}

void		reduce_cooldown(t_server *server, t_client *client)
{
  const char	**cmd;
  char		*str;

  if (client->logged)
    {
      if (client->cooldown > 0)
	--client->cooldown;
      if (!client->incanting)
	client->objects[FOOD] -= 1;
      while (client->cooldown <= 0 && !is_queue_empty(client->exec_queue)
	     && (str = pop_queue(client->exec_queue)))
	{
	  write_cmd_log(server, client, str);
	  str[strlen(str) - 1] = 0;
	  if (client->logged &&
	      (cmd = my_str_to_wordtab(str, " ")) != NULL &&
	      cmd != NULL && cmd[0] != NULL)
	    interpret_cmd(server, client, cmd);
	  free(cmd);
	  free(str);
	}
      check_level_client(server, client);
    }
}

void		cooldown_on_clients(t_server *server)
{
  t_item	*current;
  t_client	*clnt;

  if (server->clients)
    {
      current = server->clients->head;
      while (current)
	{
	  clnt = (t_client*)current->content;
	  reduce_cooldown(server, clnt);
	  current = current->next;
	}
    }
}

bool	check_if_client_dead(t_client *client)
{
  if (client->objects[FOOD] <= 0)
    {
      insert_queue(client->exit_queue, "dead\n");
      return (true);
    }
  return (false);
}