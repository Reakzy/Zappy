/*
** init_server.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/init_server.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Mon Jun 19 22:37:03 2017 Lucas Villeneuve
** Last update Mon Jun 19 22:37:03 2017 Lucas Villeneuve
*/

#include <netinet/in.h>
#include <stdio.h>
#include "server.h"

void 		init_team_and_push(t_server *server, t_params *params,
				       size_t i)
{
  t_team	tmp;

  tmp.name = params->teams[i];
  tmp.nbClientsLeft = params->clientsNb;
  server->teams->add_back(server->teams, &tmp, sizeof(t_team));
}

int			add_server(t_server *server)
{
  struct sockaddr_in    s_in;

  server->fd = socket(PF_INET, SOCK_STREAM, 0);
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons((uint16_t)server->port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  if (server->fd == -1 ||
      bind(server->fd, (struct sockaddr*)&s_in, sizeof(s_in)) == -1 ||
      listen(server->fd, 42) == -1)
    {
      perror("Error while creating server");
      return (1);
    }
  return (0);
}

int		init_server(t_server *server, t_params *params)
{
  size_t	i;

  server->port = params->port;
  server->x = params->width;
  server->y = params->height;
  server->freq = params->freq;
  server->gui = NULL;
  server->end = false;
  server->id_eggs = 0;
  server->rocks = 0;
  server->w_gui.writing = false;
  create_log_file(server);
  init_server_w_gui(server);
  if (!set_map(server, params) || !(server->teams = new_list_by_default()) ||
      !(server->clients = new_list_by_default()) ||
      !(server->eggs = new_list_by_default()))
    {
      perror("Error malloc");
      return (1);
    }
  i = 0;
  while (i < params->nb_teams)
    init_team_and_push(server, params, i++);
  return (0);
}

void	init_server_w_gui(t_server *server)
{
  server->w_gui.map = false;
  server->w_gui.eggs = false;
  server->w_gui.teams = false;
  server->w_gui.players = false;
  server->w_gui.i_map.x = 0;
  server->w_gui.i_map.y = 0;
  server->w_gui.i_teams = 0;
  server->w_gui.i_eggs = 0;
  server->w_gui.i_players = 0;
}