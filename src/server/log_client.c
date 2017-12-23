/*
** log_client.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/log_client.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Sat Jun 24 14:22:32 2017 Lucas Villeneuve
** Last update Sat Jun 24 14:22:32 2017 Lucas Villeneuve
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

void	log_client(t_server *server, t_client *client, char *str, t_team *team)
{
  char	buf[35];

  snprintf(buf, 34, "[CLIENT %d] Adding client\n", client->fd);
  write_on_log_file(server, buf);
  client->logged = true;
  client->team = team;
  spawn_client_on_egg(server, client, str);
  insert_uint_queue_nl(client->exit_queue, buf, --team->nbClientsLeft);
  memset(buf, 0, 27);
  snprintf(buf, 26, "%lu %lu\n", server->x, server->y);
  insert_queue(client->exit_queue, buf);
  if (server->gui)
    write_player(server, client);
}

void	log_gui(t_server *server, t_client *client)
{
  char	buf[25];

  if (!server->gui)
    {
      write_on_log_file(server, "[GUI] GUI connected\n");
      server->gui = client;
      server->w_gui.writing = true;
      memset(buf, 0, 25);
      snprintf(buf, 24, "msz %lu %lu\n", server->x, server->y);
      insert_queue(server->gui->exit_queue, buf);
      memset(buf, 0, 25);
      snprintf(buf, 13, "sgt %lu\n", server->freq);
      insert_queue(server->gui->exit_queue, buf);
    }
  else
    fprintf(stderr, "Already a gui client connected\n");
}
