/*
** read_write_sockets.c for appy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
** 
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
** 
** Started on  Tue Jun 20 14:42:01 2017 Samuel Osborne
** Last update Tue Jun 20 14:42:02 2017 Samuel Osborne
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "ai.h"

int 			read_socket_queue(t_ai *client, t_queue *queue)
{
  ssize_t		r;
  char 			buf[CMD_SIZE];

  memset(buf, 0, CMD_SIZE);
  r = read(client->server_fd, buf, CMD_SIZE - 1);
  if (r > 0)
    insert_queue(queue, buf);
  else
    {
      fprintf(stderr, "%d: Connection closed\n", client->server_fd);
      close(client->server_fd);
      client->connected = false;
      return (1);
    }
  return (0);
}

int 		write_socket_string(int server_fd, char *str)
{
  if ((write(server_fd, str, strlen(str))) == -1)
    return (1);
  return (0);
}