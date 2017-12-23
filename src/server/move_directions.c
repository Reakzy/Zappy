/*
** move_directions.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/move_directions.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Mon Jun 19 17:55:40 2017 Lucas Villeneuve
** Last update Mon Jun 19 17:55:40 2017 Lucas Villeneuve
*/

#include "server.h"

void	move_down(t_server *server, t_client *client)
{
  (client->pos.y > 0) ? (client->pos.y -= 1)
		      : (client->pos.y = (int)server->y - 1);
}

void	move_right(t_server *server, t_client *client)
{
  (client->pos.x < (int)(server->x - 1)) ? (client->pos.x += 1)
				    : (client->pos.x = 0);
}

void	move_up(t_server *server, t_client *client)
{
  (client->pos.y < (int)(server->y - 1)) ? (client->pos.y += 1)
				    : (client->pos.y = 0);
}

void	move_left(t_server *server, t_client *client)
{
  (client->pos.x > 0) ? (client->pos.x -= 1)
		      : (client->pos.x = (int)server->x - 1);
}