/*
** connection_manager.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
** 
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
** 
** Started on  Tue Jun 13 12:58:02 2017 Samuel Osborne
** Last update Tue Jun 13 12:58:03 2017 Samuel Osborne
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "ai.h"

int 				connect_to_server(char *hostname,
						     int port)
{
  struct protoent		*pe;
  struct sockaddr_in		s_in;
  struct hostent		*host;
  int				connected_fd;

  if (!(pe = getprotobyname("TCP")))
    return (1);
  if ((connected_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    {
      fprintf(stderr, "Could not create socket.\n");
      return (1);
    }
  if ((host = gethostbyname(hostname)) == NULL)
    {
      fprintf(stderr, "Incorrect hostname.\n");
      return (1);
    }
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons((uint16_t)port);
  if ((memcpy(&s_in.sin_addr, host->h_addr_list[0], (size_t)host->h_length))
      == NULL)
    return (1);
  if (try_connection(connected_fd, s_in) == 1)
    return (1);
  return (connected_fd);
}

void			init_file_descriptors(fd_set *fd_read,
						  fd_set *fd_write,
						  int serverFd)
{
  FD_ZERO(fd_read);
  FD_ZERO(fd_write);
  FD_SET(serverFd, fd_read);
  FD_SET(serverFd, fd_write);
}

int				try_connection(int connected_fd,
						  struct sockaddr_in s_in)
{
  if ((connect(connected_fd, (const struct sockaddr *) &s_in,
	       sizeof(s_in))) == -1)
    {
      fprintf(stderr, "Can't connect to server socket.\n");
      return (1);
    }
  return (0);
}
