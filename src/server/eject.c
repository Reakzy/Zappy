/*
** eject.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/eject.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Fri Jun 23 11:13:40 2017 Lucas Villeneuve
** Last update Fri Jun 23 11:13:40 2017 Lucas Villeneuve
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

void	send_gui_eject(t_server *server, t_client *client)
{
  char	buf[15];

  if (server->gui)
    {
      snprintf(buf, 14, "pex %d\n", client->fd);
      insert_queue(server->gui->exit_queue, buf);
    }
}

void			write_direction_eject(t_server *server,
						  enum e_directions dir1,
						  enum e_directions dir2,
						  t_client *clnt)
{
  char			buf[45];
  int 			dirs[4];

  dirs[0] = 5;
  dirs[1] = 3;
  dirs[2] = 1;
  dirs[3] = 7;
  snprintf(buf, 17, "eject %d\n", dirs[(dir1 - 1) - (dir2 - 1) % (MAXDIR - 1)]);
  insert_queue(clnt->exit_queue, buf);
  if (server->gui)
    {
      snprintf(buf, 44, "ppo %d %d %d %d\n", clnt->fd,
	       clnt->pos.x, clnt->pos.y, clnt->dir);
      insert_queue(server->gui->exit_queue, buf);
    }
}

void			eject_other_players(t_server *server,
						t_client *client,
						t_client *clnt)
{
  void			(*ptr[MAXDIR - 1])(t_server*, t_client*);
  enum e_directions	dirs;
  size_t		i;

  ptr[NORD - 1] = &move_up;
  ptr[EST - 1] = &move_right;
  ptr[SUD - 1] = &move_down;
  ptr[OUEST - 1] = &move_left;
  dirs = NORD;
  i = 0;
  while (i < MAXDIR - 1)
    {
      if (client->dir == dirs++)
	{
	  ptr[i](server, clnt);
	  return (write_direction_eject(server, client->dir, clnt->dir, clnt));
	}
      ++i;
    }
}