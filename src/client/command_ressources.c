/*
** command_ressources.c for PSU_2016_zappy in /home/counil_m/project/PSU_2016_zappy/command_ressources.c
**
** Made By Maxime Counil
** Login <maxime.counil@epitech.eu>
**
** Started on Mon Jun 19 13:50:27:27 ${YEAH} Maxime Counil
** Last update on Mon Jun 19 13:50:27:27 ${YEAH} Maxime Counil
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ai.h"

void	look(t_ai *client, t_queue *write_queue)
{
  insert_queue(write_queue, "Look\n");
  client->brain->previous_act = 1;
  if (client->objects[FOOD] > 10)
    client->brain->choice_ok = 2;
  else
    client->brain->choice_ok = 15;
}

void		free_tab_len(char **cmd, int len)
{
  int 		i;

  i = 0;
  if (cmd != NULL)
    {
      while (i < len)
	free(cmd[i++]);
      free(cmd);
    }
}

void		free_tab(char **cmd)
{
  size_t 	i;

  i = 0;
  if (cmd != NULL)
    {
      while (cmd[i] != NULL)
	free(cmd[i++]);
      free(cmd);
    }
}

void	enough_food(t_ai *client, t_queue *write_queue)
{
  client->msg_received = NULL;
  client->brain->previous_act = 0;
  look(client, write_queue);
}

