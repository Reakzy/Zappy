/*
** exec_client.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/exec_client.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Mon Jun 12 16:28:53 2017 Lucas Villeneuve
** Last update Mon Jun 12 16:28:53 2017 Lucas Villeneuve
*/

#include <string.h>
#include "server.h"

void		check_if_client_can_log(t_server *server, t_client *client,
					    char *str)
{
  t_item	*current;
  t_team	*team;

  if (strcmp("GRAPHIC", str) == 0)
    return (log_gui(server, client));
  if (server->teams)
    {
      current = server->teams->head;
      while (current)
	{
	  team = (t_team *) current->content;
	  if (strcmp(str, team->name) == 0 && team->nbClientsLeft > 0)
	    return (log_client(server, client, str, team));
	  current = current->next;
	}
    }
  insert_queue(client->exit_queue, "ko\n");
}

void		unknown_cmd(t_client *client)
{
  insert_queue(client->exit_queue, "ko\n");
}

size_t		init_ptrfnc_exec(void (*ptrfnc[])(t_server*,
							t_client*,
							const char**))
{
  size_t	i;

  i = 0;
  ptrfnc[i++] = &forward_cmd;
  ptrfnc[i++] = &right_cmd;
  ptrfnc[i++] = &left_cmd;
  ptrfnc[i++] = &look_cmd;
  ptrfnc[i++] = &inventory_cmd;
  ptrfnc[i++] = &broadcast_cmd;
  ptrfnc[i++] = &connect_nbr_cmd;
  ptrfnc[i++] = &fork_cmd;
  ptrfnc[i++] = &eject_cmd;
  ptrfnc[i++] = &take_cmd;
  ptrfnc[i++] = &set_cmd;
  ptrfnc[i++] = &incantation_cmd;
  return (i);
}

void		interpret_cmd(t_server *server, t_client *client,
				  const char **cmd)
{
  size_t 	i;
  int		j;
  void		(*ptrfnc[12])(t_server*, t_client*, const char**);
  char		tab[12][12];

  strcpy(tab[0], "Forward");
  strcpy(tab[1], "Right");
  strcpy(tab[2], "Left");
  strcpy(tab[3], "Look");
  strcpy(tab[4], "Inventory");
  strcpy(tab[5], "Broadcast");
  strcpy(tab[6], "Connect_nbr");
  strcpy(tab[7], "Fork");
  strcpy(tab[8], "Eject");
  strcpy(tab[9], "Take");
  strcpy(tab[10], "Set");
  strcpy(tab[11], "Incantation");
  client->cooldown = 0;
  i = init_ptrfnc_exec(ptrfnc);
  j = -1;
  while (++j < (int)i)
    if (strcmp(tab[j], cmd[0]) == 0)
      return (ptrfnc[j](server, client, cmd));
  unknown_cmd(client);
}

bool		exec_client(t_server *server,
				t_client *client)
{
  char 		*str;
  const char	**cmd;

  if (client->fd == -1 || check_if_client_dead(client))
    return (true);
  while (client->cooldown == 0 && !is_queue_empty(client->entry_queue) &&
	 (str = pop_queue(client->entry_queue)))
    {
      str[strlen(str) - 1] = 0;
      if (!client->logged)
	check_if_client_can_log(server, client, str);
      else
	{
	  insert_queue(client->exec_queue, str);
	  insert_queue(client->exec_queue, "\n");
	  if ((cmd = my_str_to_wordtab(str, " ")) != NULL &&
	      cmd != NULL && cmd[0] != NULL)
	    {
	      interpret_cmd_cooldown(server, client, cmd);
	      free(cmd);
	    }
	}
      free(str);
    }
  return (true);
}