/*
** broadcast.c for broadcast in /home/leo/Tek2/USP_Networks/PSU_2016_zappy
** 
** Made by Leo
** Login   <leo.camberou@epitech.eu>
** 
** Started on  Thu Jun 22 15:31:21 2017 Leo
** Last update Thu Jun 22 15:31:23 2017 Leo
*/

#include <math.h>
#include <stdio.h>
#include "server.h"

void	write_cmd_broadcast(t_client *client, const char **cmd)
{
  int	i;

  i = 0;
  while (cmd[++i] != NULL)
    {
      insert_queue(client->exit_queue, (char*)cmd[i]);
      if (cmd[i + 1] != NULL)
	insert_queue(client->exit_queue, " ");
    }
}

size_t		get_min(t_server *server,
			      int sender,
			      int receiver,
			      bool *yes)
{
  size_t	tmp1;
  size_t	tmp2;

  tmp1 = (size_t)abs((sender - receiver));
  tmp2 = server->x - tmp1;
  if (tmp1 >= tmp2)
    {
      (receiver < sender) ? (*yes = false) : (*yes = true);
      return (tmp2);
    }
  else
    {
      (receiver < sender) ? (*yes = true) : (*yes = false);
      return (tmp1);
    }
}

void	init_tab(size_t *tab, size_t value1, size_t value2, size_t value3)
{
  tab[0] = value1;
  tab[1] = value2;
  tab[2] = value3;
}

size_t		good_tile_with_dir(t_client *receiver,
					 int partie,
					 bool right,
					 bool up)
{
  size_t	tab_up_right[3];
  size_t	tab_up_left[3];
  size_t	tab_down_left[3];
  size_t	tab_down_right[3];
  size_t	calcul;

  init_tab(tab_up_right, 1, 8, 7);
  init_tab(tab_up_left, 1, 2, 3);
  init_tab(tab_down_left, 5, 4, 3);
  init_tab(tab_down_right, 5, 6, 7);
  if (up && right)
    calcul = tab_up_right[partie - 1];
  else if (up)
    calcul = tab_up_left[partie - 1];
  else if (!right)
    calcul = tab_down_left[partie - 1];
  else
    calcul = tab_down_right[partie - 1];
  calcul = (calcul + (receiver->dir - 1) * 2) % 8;
  if (calcul == 0)
    calcul = 8;
  return (calcul);
}

size_t		broadcast_tile(t_server *server,
				     t_client *sender,
				     t_client *receiver)
{
  double	min_x;
  double	min_y;
  double	angle;
  int		partie;
  bool		right;
  bool		up;

  if (sender->pos.x == receiver->pos.x && sender->pos.y == receiver->pos.y)
    return (0);
  min_x = get_min(server, sender->pos.x, receiver->pos.x, &right);
  min_y = get_min(server, sender->pos.y, receiver->pos.y, &up);
  if (min_x == 0)
    min_x = 0.00001;
  angle = fabs(atan((min_y / min_x)));
  if (angle >= 0 && angle < (M_PI / 8.0))
    partie = 3;
  else if (angle >= (M_PI / 8.0) && angle <= (3.0 * M_PI / 8.0))
    partie = 2;
  else
    partie = 1;
  return (good_tile_with_dir(receiver, partie, right, up));
}
