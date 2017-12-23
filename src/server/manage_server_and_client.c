/*
** manage_server_and_client.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/manage_server_and_client.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Mon Jun 12 16:11:07 2017 Lucas Villeneuve
** Last update Mon Jun 12 16:11:07 2017 Lucas Villeneuve
*/

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

void			read_server(t_server *server)
{
  int 			fd;
  struct sockaddr_in	sin;
  socklen_t		len;
  t_client		client;

  len = sizeof(sin);
  fd = accept(server->fd, (struct sockaddr*)&sin, &len);
  if (fd == -1)
    perror("Accept failed");
  else
    {
      if (init_client(&client, fd, server) == 1)
	return ;
      insert_queue(client.exit_queue, "WELCOME\n");
      if (server->clients)
	server->clients->add_back(server->clients, &client, sizeof(client));
      else
	fprintf(stderr, "Cannot add client, list is not allocated\n");
    }
}

int		read_client(t_client *client)
{
  ssize_t	r;
  char 		buf[CMD_SIZE];

  memset(buf, 0, CMD_SIZE);
  r = read(client->fd, buf, CMD_SIZE - 1);
  if (r > 0)
    insert_queue(client->entry_queue, buf);
  else
    {
      fprintf(stderr, "%d: Connection closed\n", client->fd);
      return (1);
    }
  return (0);
}

void		write_str_on_client(int fd, char *str)
{
  ssize_t	len;
  ssize_t 	len2;

  len = strlen(str);
  len2 = 0;
  while (len2 < len)
    {
      len -= len2;
      len2 = write(fd, str + len2, (size_t)len);
      if (len == -1)
	{
	  perror("Error write on client");
	  free(str);
	  return ;
	}
    }
  free(str);
}

void		write_str_on_log(t_server *server, t_client *client, char *str)
{
  char		buf[39];

  if ((server->gui && server->gui->fd == client->fd) || client->logged)
    {
      if (client->logged)
	{
	  snprintf(buf, 38, "[CLIENT %d] Sending : \"", client->fd);
	  write_on_log_file(server, buf);
	}
      else
	write_on_log_file(server, "[GUI] Sending : \"");
      write_on_log_file_len(server, str, strlen(str) - 1);
      write_on_log_file(server, "\"\n");
    }
}

bool		write_client(t_server *server, t_client *client)
{
  char		*str;
  bool		ret;

  ret = true;
  while (!is_queue_empty(client->exit_queue) &&
	 (str = pop_queue(client->exit_queue)))
    {
      if (strcmp(str, "dead\n") == 0)
	ret = false;
      write_str_on_log(server, client, str);
      write_str_on_client(client->fd, str);
      if (!ret)
	return (ret);
    }
  return (ret);
}