/*
** log_file.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/log_file.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Thu Jun 29 10:24:06 2017 Lucas Villeneuve
** Last update Thu Jun 29 10:24:06 2017 Lucas Villeneuve
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

void	write_on_log_file(t_server *server, char *str)
{
  if (server->fd_log != -1)
    if (write(server->fd_log, str, strlen(str)) == -1)
      perror("Write failed");
}

void	write_on_log_file_len(t_server *server, char *str, size_t len)
{
  if (server->fd_log != -1)
    if (write(server->fd_log, str, len) == -1)
      perror("Write failed");
}

void	create_log_file(t_server *server)
{
  if ((server->fd_log = open("./server.log", O_WRONLY | O_CREAT | O_TRUNC,
			     S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
			     S_IROTH | S_IWOTH)) == -1)
    {
      perror("Erreur open");
      server->fd_log = -1;
      return ;
    }
  write_on_log_file(server, "[INFO] Server created\n");
}

void	close_log_file(t_server *server)
{
  if (server->fd_log != -1)
    {
      write_on_log_file(server, "[INFO] Server closed\n");
      close(server->fd_log);
    }
}