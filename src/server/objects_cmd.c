/*
** objects_cmd.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/objects_cmd.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Tue Jun 13 15:26:18 2017 Lucas Villeneuve
** Last update Tue Jun 13 15:26:18 2017 Lucas Villeneuve
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

void		send_gui_state_tile_player(t_server *server, t_client *client)
{
  char		buf[105];

  if (server->gui)
    {
      snprintf(buf, 104, "pin %d %d %d %lu %lu %lu %lu %lu %lu %lu\n",
	       client->fd, client->pos.x, client->pos.y,
	       client->objects[FOOD] / 126,
	       client->objects[LINEMATE], client->objects[DERAUMERE],
	       client->objects[SIBUR], client->objects[MENDIANE],
	       client->objects[PHIRAS], client->objects[THYSTAME]);
      insert_queue(server->gui->exit_queue, buf);
      write_tile(server, buf, client->pos.x, client->pos.y);
    }
}

void		action_on_map(t_server *server,
				  t_client *client,
				  int obj,
				  bool take)
{
  size_t	value;
  char		buf[25];

  (obj == FOOD) ? (value = 126) : (value = 1);
  if (take)
    {
      server->map[client->pos.y][client->pos.x].objects[obj] -= value;
      client->objects[obj] += value;
      if (server->gui)
	insert_queue(server->gui->exit_queue, "pgt");
    }
  else
    {
      server->map[client->pos.y][client->pos.x].objects[obj] += value;
      client->objects[obj] -= value;
      if (server->gui)
	insert_queue(server->gui->exit_queue, "pdr");
    }
  if (server->gui)
    {
      snprintf(buf, 24, " %d %d\n", client->fd, obj);
      insert_queue(server->gui->exit_queue, buf);
    }
  insert_queue(client->exit_queue, "ok\n");
  send_gui_state_tile_player(server, client);
}

void	take_cmd(t_server *server, t_client *client, const char **cmd)
{
  char 	tab[MAXOBJECTTYPE][10];
  int	i;

  strcpy(tab[FOOD], "food");
  strcpy(tab[LINEMATE], "linemate");
  strcpy(tab[DERAUMERE], "deraumere");
  strcpy(tab[SIBUR], "sibur");
  strcpy(tab[MENDIANE], "mendiane");
  strcpy(tab[PHIRAS], "phiras");
  strcpy(tab[THYSTAME], "thystame");
  if (cmd[1])
    {
      i = -1;
      while (++i < MAXOBJECTTYPE)
	{
	  if (strcmp(tab[i], cmd[1]) == 0 &&
	      server->map[client->pos.y][client->pos.x].objects[i] > 0)
	    return (action_on_map(server, client, i, true));
	}
    }
  insert_queue(client->exit_queue, "ko\n");
}

void	set_cmd(t_server *server, t_client *client, const char **cmd)
{
  char 	tab[MAXOBJECTTYPE][10];
  int	i;

  strcpy(tab[FOOD], "food");
  strcpy(tab[LINEMATE], "linemate");
  strcpy(tab[DERAUMERE], "deraumere");
  strcpy(tab[SIBUR], "sibur");
  strcpy(tab[MENDIANE], "mendiane");
  strcpy(tab[PHIRAS], "phiras");
  strcpy(tab[THYSTAME], "thystame");
  if (cmd[1])
    {
      i = -1;
      while (++i < MAXOBJECTTYPE)
	if (strcmp(tab[i], cmd[1]) == 0 && client->objects[i] > 0)
	  return (action_on_map(server, client, i, false));
    }
  insert_queue(client->exit_queue, "ko\n");
}

void		incantation_cmd(t_server *server, t_client *client,
				    const char **cmd)
{
  void		(*ptr[MAX_LEVEL - 1])(t_server*, t_client*, bool);
  size_t	i;
  bool		first_check;

  if (!cmd)
    first_check = true;
  else
    first_check = false;
  ptr[0] = &level_two_incantation;
  ptr[1] = &level_three_incantation;
  ptr[2] = &level_four_incantation;
  ptr[3] = &level_five_incantation;
  ptr[4] = &level_six_incantation;
  ptr[5] = &level_seven_incantation;
  ptr[6] = &level_eight_incantation;
  i = 0;
  while (i < MAX_LEVEL - 1)
    {
      if ((i + 1) == client->level)
	return (ptr[i](server, client, first_check));
      ++i;
    }
  insert_queue(client->exit_queue, "ko\n");
}