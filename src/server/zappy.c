/*
** zappy.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/zappy.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Mon Jun 12 14:49:56 2017 Lucas Villeneuve
** Last update Mon Jun 12 14:49:56 2017 Lucas Villeneuve
*/

#include <signal.h>
#include <stdio.h>
#include <time.h>
#include "server.h"

bool	running = true;

void	signal_handler(__attribute__((unused))int signal)
{
  running = false;
}

bool	select_server(t_server *server, struct timeval tv,
			  fd_set *fd_read, fd_set *fd_write)
{
  if (select(set_fds(server, fd_read, fd_write) + 1,
	     fd_read, fd_write, NULL, &tv) == -1)
    {
      perror("Select failed");
      return (false);
    }
  else
    {
      writing_infos_gui(server);
      check_if_fds_set(server, fd_read, fd_write);
    }
  return (true);
}

void			server_zappy(t_server *server)
{
  struct timeval	tv;
  fd_set		fd_read;
  fd_set		fd_write;
  clock_t		start;

  print_log_map(server);
  start = clock();
  while (running || server->end)
    {
      tv.tv_sec = 0;
      tv.tv_usec = 0;
      if (!select_server(server, tv, &fd_read, &fd_write))
	running = false;
      if ((clock() - start) * 1000 / CLOCKS_PER_SEC
	  >= (long int)(1000 / server->freq))
	{
	  start = clock();
	  cooldown_on_clients(server);
	  timer_eggs(server, server->eggs);
	  place_rocks_map(server);
	}
    }
}

int		zappy(t_params *params)
{
  t_server	server;
  t_item	*current;

  signal(SIGINT, signal_handler);
  signal(SIGPIPE, SIG_IGN);
  if (init_server(&server, params) == 1)
    return (84);
  if (add_server(&server) == 0)
    server_zappy(&server);
  if (server.clients)
    {
      current = server.clients->head;
      while (current)
	current = delete_node_client(&server, current);
    }
  free_map(&server);
  close_log_file(&server);
  delete_list(server.clients);
  delete_list(server.teams);
  delete_list(server.eggs);
  return (0);
}