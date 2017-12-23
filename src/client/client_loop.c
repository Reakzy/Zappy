/*
** client_loop.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU
** 
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
** 
** Started on  Tue Jun 13 09:37:37 2017 Samuel Osborne
** Last update Tue Jun 13 09:37:38 2017 Samuel Osborne
*/

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "ai.h"

int 			check_if_args_compl(t_cargs *args)
{
  if (args->team_name == NULL)
    {
      fprintf(stderr, "Please enter a team name.\n");
      return (1);
    }
  if (args->machine_name == NULL)
    {
      fprintf(stderr, "Please enter a machine name.\n");
      return (1);
    }
  return (0);
}

int			reset_tv_and_init_fd(struct timeval *tv,
						fd_set *fd_read,
						fd_set *fd_write,
						t_ai *client)
{
  tv->tv_sec = 0;
  tv->tv_usec = 0;
  init_file_descriptors(fd_read, fd_write, client->server_fd);
  if (select(client->server_fd + 1, fd_read, fd_write,
	     NULL, tv) == -1)
    return (1);
  return (0);
}

int			free_queue_and_return(t_queue *write_queue,
						 t_queue *read_queue,
						 int value)
{
  free_queue(write_queue);
  free_queue(read_queue);
  return (value);
}

int 			start_select_loop(t_ai *client, t_cargs *args)
{
  bool			welcome;
  t_queue		*write_queue;
  t_queue		*read_queue;
  fd_set		fd_read;
  fd_set		fd_write;
  struct timeval	tv;

  if (!(write_queue = init_queue(false)) || !(read_queue = init_queue(false)))
    return (1);
  welcome = false;
  while (client->connected)
    {
      if ((reset_tv_and_init_fd(&tv, &fd_read, &fd_write, client)) == 1)
	return (free_queue_and_return(write_queue, read_queue, 1));
      if (welcome)
	{
	  if ((read_on_server(client, &fd_read, read_queue)) == 1 ||
	      write_on_server(client, &fd_write, write_queue) == 1)
	    client->connected = false;
	  brain_ai(client, write_queue, read_queue);
	}
      else if (welcome_manange_fd(&fd_read, &fd_write, client, args) == 2)
	welcome = true;
    }
  return (free_queue_and_return(write_queue, read_queue, 0));
}

int			client_loop(t_cargs *args)
{
  t_ai			client;
  int 			tok;

  tok = 0;
  client.connected = false;
  if ((client.brain = malloc(sizeof(t_ai_brain))) == NULL)
    tok = 1;
  init_brain_and_client(&client);
  if (tok != 1 && check_if_args_compl(args) == 1)
    tok = 1;
  if (tok != 1 && (client.server_fd =
   connect_to_server(args->machine_name, args->port)) == 1)
    tok = 1;
  client.connected = true;
  if (tok != 1 && (start_select_loop(&client, args)) == 1)
    tok = 1;
  if (tok == 1)
    {
      free_queue(client.brain->broadcast_msg);
      free(client.brain);
      return (1);
    }
  free_queue(client.brain->broadcast_msg);
  free(client.brain);
  return (0);
}
