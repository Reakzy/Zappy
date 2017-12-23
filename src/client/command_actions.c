/*
** command_actions.c for PSU_2016_zappy in /home/counil_m/project/PSU_2016_zappy/command_actions.c
**
** Made By Maxime Counil
** Login <maxime.counil@epitech.eu>
**
** Started on Mon Jun 19 13:56:49:49 ${YEAH} Maxime Counil
** Last update on Mon Jun 19 13:56:49:49 ${YEAH} Maxime Counil
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ai.h"

int 	*fill_array_on_lvl(int level)
{
  int 	*stones;
  void	(*ptrfnc[7])(int *);

  if ((stones = malloc(sizeof(int) * MAXOBJECTTYPE)) == NULL)
    return (NULL);
  memset(stones, 0, MAXOBJECTTYPE);
  level--;
  ptrfnc[0] = &level_one;
  ptrfnc[1] = &level_two;
  ptrfnc[2] = &level_three;
  ptrfnc[3] = &level_four;
  ptrfnc[4] = &level_five;
  ptrfnc[5] = &level_six;
  ptrfnc[6] = &level_seven;
  if (level >= 0 && level <= 6)
    ptrfnc[level](stones);
  else
    return (NULL);
  return (stones);
}

int 	players_needed(int team, t_ai *client)
{
  int 	players_needed[8];

  players_needed[0] = 0;
  players_needed[1] = 0;
  players_needed[2] = 1;
  players_needed[3] = 1;
  players_needed[4] = 3;
  players_needed[5] = 5;
  players_needed[6] = 5;
  players_needed[7] = 5;
  return (players_needed[team] - client->nb_player_incant);
}

void	print_missing_stones(t_ai *client,
				 int *missing,
				 t_queue *write_queue)
{
  char	*message;
  int 	i;

  i = 1;
  if ((message = malloc(sizeof(char) * strlen("Broadcast "))) == NULL)
    return ;
  memset(message, 0, strlen("Broadcast "));
  message = concat_strings(message, "Broadcast ");
  message = concat_int(message, client->level);
  message = concat_strings(message, " ");
  message = concat_int(message, players_needed(client->level, client));
  while (i < MAXOBJECTTYPE)
    {
      message = concat_strings(message, ",");
      message = concat_strings(message, " ");
      message = concat_int(message, i);
      message = concat_strings(message, " ");
      message = concat_int(message, missing[i]);
      i++;
    }
  message = concat_strings(message, "\n");
  insert_queue(write_queue, message);
  free(message);
}

void	broadcast_ai(t_ai *client, t_queue *write_queue)
{
  int 	missing[MAXOBJECTTYPE];
  int 	*level;
  int 	i;

  i = 0;
  if (client->level == 0)
    return ;
  while (i != MAXOBJECTTYPE)
    missing[i++] = 0;
  level = fill_array_on_lvl(client->level);
  i = 1;
  while (i < MAXOBJECTTYPE)
    {
      missing[i] = (level[i] - client->objects[i]);
      if (missing[i] < 0)
	missing[i] = 0;
      i++;
    }
  print_missing_stones(client, missing, write_queue);
  free(level);
}