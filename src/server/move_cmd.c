/*
** move_cmd.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/move_cmd.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Tue Jun 13 15:21:38 2017 Lucas Villeneuve
** Last update Tue Jun 13 15:21:38 2017 Lucas Villeneuve
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

void	send_gui_player_move(t_server *server, t_client *client)
{
  char	buf[45];

  if (server->gui)
    {
      snprintf(buf, 44, "ppo %d %d %d %d\n",
	       client->fd, client->pos.x, client->pos.y, client->dir);
      insert_queue(server->gui->exit_queue, buf);
    }
}

void			forward_cmd(t_server *server, t_client *client,
					__attribute__((unused))
					const char **cmd)
{
  void			(*ptr[MAXDIR - 1])(t_server*, t_client*);
  enum e_directions	dirs;
  size_t		j;

  ptr[NORD - 1] = &move_up;
  ptr[EST - 1] = &move_right;
  ptr[SUD - 1] = &move_down;
  ptr[OUEST - 1] = &move_left;
  dirs = NORD;
  j = 0;
  while (j < MAXDIR - 1)
    {
      if (client->dir == dirs++)
	{
	  ptr[j](server, client);
	  j = MAXDIR;
	}
      ++j;
    }
  insert_queue(client->exit_queue, "ok\n");
  send_gui_player_move(server, client);
}

void	right_cmd(t_server *server, t_client *client,
		      __attribute__((unused))const char **cmd)
{
  client->dir++;
  if (client->dir == MAXDIR)
    client->dir = NORD;
  insert_queue(client->exit_queue, "ok\n");
  send_gui_player_move(server, client);
}

void	left_cmd(t_server *server, t_client *client,
		     __attribute__((unused))const char **cmd)
{
  if (client->dir > NORD)
    client->dir--;
  else
    client->dir = MAXDIR - 1;
  insert_queue(client->exit_queue, "ok\n");
  send_gui_player_move(server, client);
}
