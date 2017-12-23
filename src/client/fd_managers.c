/*
** fd_managers.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
** 
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
** 
** Started on  Tue Jun 20 17:44:20 2017 Samuel Osborne
** Last update Tue Jun 20 17:44:22 2017 Samuel Osborne
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ai.h"
#include "unistd.h"

int 			welcome_manange_fd(fd_set *fd_read,
					      fd_set *fd_write,
					      t_ai *client,
					      t_cargs *args)
{
  bool			welcome;

  welcome = false;
  if (FD_ISSET(client->server_fd, fd_read))
    if ((welcome = welcome_read(client)) == false)
      return (2);
  if (FD_ISSET(client->server_fd, fd_write))
    if (welcome)
      if (write_team(client, args) == 1)
	return (1);
  usleep(1000500);
  return (0);
}

int 			manage_write_fd(t_queue *queue, t_ai *client)
{
  char 			*cmd;

  while (!is_queue_empty(queue))
    {
      if ((cmd = pop_queue(queue)) == NULL)
	return (1);
      if ((write_socket_string(client->server_fd, cmd)) == 1)
	return (1);
      free(cmd);
    }
  return (0);
}

int 			read_on_server(t_ai *client,
					  fd_set *fd_read,
					  t_queue *read_queue)
{
  char 			*str;

  if (FD_ISSET(client->server_fd, fd_read))
    {
      read_socket_queue(client, read_queue);
      if (!is_queue_empty(read_queue))
	{
	  str = pop_queue(read_queue);
	  if (strcmp(str, "dead\n") == 0)
	    {
	      free(str);
	      printf("You have died.\n");
	      return (1);
	    }
	  insert_queue(read_queue, strdup(str));
	  free(str);
	}
    }
  return (0);
}

int 			write_on_server(t_ai *client,
					   fd_set *fd_write,
					   t_queue *write_queue)
{
  if (FD_ISSET(client->server_fd, fd_write))
    {
      if ((manage_write_fd(write_queue, client)) == 1)
	return (1);
    }
  return (0);
}
