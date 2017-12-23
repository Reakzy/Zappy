/*
** fds_server.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/fds_server.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Mon Jun 12 15:55:10 2017 Lucas Villeneuve
** Last update Mon Jun 12 15:55:10 2017 Lucas Villeneuve
*/

#include "server.h"

int		set_fds(t_server *server,
			   fd_set *fd_read,
			   fd_set *fd_write)
{
  int		max_fd;
  t_item	*current;
  t_client	*client;

  max_fd = server->fd;
  FD_ZERO(fd_read);
  FD_ZERO(fd_write);
  FD_SET(server->fd, fd_read);
  FD_SET(server->fd, fd_write);
  if (server->clients != NULL)
    {
      current = server->clients->head;
      while (current != NULL)
	{
	  client = (t_client*)current->content;
	  FD_SET(client->fd, fd_read);
	  FD_SET(client->fd, fd_write);
	  if (max_fd < client->fd)
	    max_fd = client->fd;
	  current = current->next;
	}
    }
  return (max_fd);
}

void		check_if_fds_set(t_server *server,
				     fd_set *fd_read,
				     fd_set *fd_write)
{
  t_item	*cur;
  t_client	*clnt;
  bool		closed;

  if (FD_ISSET(server->fd, fd_read))
    read_server(server);
  if (server->clients == NULL)
    return ;
  cur = server->clients->head;
  while (cur != NULL)
    {
      clnt = (t_client*)cur->content;
      closed = false;
      if (FD_ISSET(clnt->fd, fd_read) && read_client(clnt) == 1)
	{
	  cur = delete_node_client(server, cur);
	  closed = true;
	}
      else
	exec_client(server, clnt);
      if (!closed)
	(FD_ISSET(clnt->fd, fd_write) &&
	 !write_client(server, clnt)) ? (cur = delete_node_client(server, cur))
				      : (cur = cur->next);
    }
}