/*
** ope_client.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/ope_client.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Mon Jun 12 15:44:54 2017 Lucas Villeneuve
** Last update Mon Jun 12 15:44:54 2017 Lucas Villeneuve
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include "server.h"

int	init_client(t_client *client, int fd, t_server *server)
{
  client->fd = fd;
  client->logged = false;
  client->born_from_egg = false;
  client->pos.x = (int)(random() % server->x);
  client->pos.y = (int)(random() % server->y);
  client->dir = (enum e_directions)random() % (MAXDIR - 1) + 1;
  client->team = NULL;
  client->cooldown = 0;
  client->level = 1;
  client->objects[LINEMATE] = 0;
  client->objects[DERAUMERE] = 0;
  client->objects[SIBUR] = 0;
  client->objects[MENDIANE] = 0;
  client->objects[PHIRAS] = 0;
  client->objects[THYSTAME] = 0;
  client->objects[FOOD] = 1260;
  client->incanting = false;
  if (!(client->entry_queue = init_queue(false)) ||
      !(client->exec_queue = init_queue(false)) ||
      !(client->exit_queue = init_queue(true)))
    return (1);
  return (0);
}

void		send_gui_player_dead(t_server *server, t_client *client)
{
  char		buf[15];

  if (server->gui)
    {
      snprintf(buf, 14, "pdi %d\n", client->fd);
      insert_queue(server->gui->exit_queue, buf);
    }
}

void		delete_infos_client(t_server *server, t_client *client)
{
  char		buf[36];

  if (client->logged)
    {
      if (!client->born_from_egg && client->team)
	++client->team->nbClientsLeft;
      send_gui_player_dead(server, client);
      snprintf(buf, 35, "[CLIENT %d] Closing client\n", client->fd);
      write_on_log_file(server, buf);
      if (client->incanting && server->gui)
	{
	  snprintf(buf, 25, "pie %d %d 0\n", client->pos.x, client->pos.y);
	  insert_queue(server->gui->exit_queue, buf);
	}
    }
}

t_item		*delete_node_client(t_server *server, t_item *current)
{
  t_client	*clnt;
  t_item	*tmp;

  tmp = current->next;
  clnt = (t_client*)current->content;
  (current->prev == NULL) ? (server->clients->head = current->next)
			  : (current->prev->next = current->next);
  (current->next == NULL) ? (server->clients->tail = current->prev)
			  : (current->next->prev = current->prev);
  if (--server->clients->len <= 0)
    server->clients->empty = 1;
  delete_infos_client(server, clnt);
  if (clnt == server->gui)
    {
      write_on_log_file(server, "[GUI] Closing GUI\n");
      server->gui = NULL;
      init_server_w_gui(server);
    }
  close(clnt->fd);
  free_queue(clnt->entry_queue);
  free_queue(clnt->exec_queue);
  free_queue(clnt->exit_queue);
  delete_item(current);
  return (tmp);
}
