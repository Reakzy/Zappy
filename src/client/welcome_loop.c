/*
** welcome_loop.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
** 
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
** 
** Started on  Tue Jun 20 14:32:48 2017 Samuel Osborne
** Last update Tue Jun 20 14:32:49 2017 Samuel Osborne
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ai.h"

int 			write_team(t_ai *client, t_cargs *args)
{
  if ((write_socket_string(client->server_fd, args->team_name)) == 1)
    {
      fprintf(stderr, "Write socket failed\n");
      return (1);
    }
  if ((write_socket_string(client->server_fd, "\n")) == 1)
    {
      fprintf(stderr, "Write socket failed\n");
      return (1);
    }
  return (0);
}

void			set_team_nbr(t_ai *client, char *str)
{
  int 			i;
  char 			*nbr;

  i = 0;
  nbr = strdup(str);
  while (nbr[i] != '\0')
    {
      if (nbr[i] == '\n')
	nbr[i] = '\0';
      i++;
    }
  client->nbr_teammates = atoi(nbr);
  free(nbr);
}

bool			check_for_welcome_or_ko(t_queue *queue, t_ai *client)
{
  char 			*ret;

  printf("Attempting connection to server...\n");
  if (strcmp(ret = pop_queue(queue), "WELCOME\n") == 0 ||
      strcmp(ret, "ko\n") == 0)
    {
      if (strcmp(ret, "ko\n") == 0)
	printf("Wrong team name or no places "
		"currently available on team.\n");
      free(ret);
      return (true);
    }
  else
    {
      printf("Places remaining in your team: %s\n", ret);
      client->nbr_teammates = atoi(ret);
      set_team_nbr(client, ret);
      free(ret);
      return (false);
    }
}

bool 			welcome_read(t_ai *client)
{
  t_queue		*queue;
  bool			ret;

  if ((queue = init_queue(false)) == NULL)
    return (false);
  if ((read_socket_queue(client, queue)) == 1)
    {
      free_queue(queue);
      return (1);
    }
  if (!is_queue_empty(queue))
    {
      ret = check_for_welcome_or_ko(queue, client);
      free_queue(queue);
      return (ret);
    }
  return (false);
}
