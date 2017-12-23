/*
** broadcast_ally.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
**
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
**
** Started on  Sat Jun 24 13:08:14 2017 Samuel Osborne
** Last update Sat Jun 24 13:08:15 2017 Samuel Osborne
*/

#include <stdlib.h>
#include <string.h>
#include "ai.h"

bool	compare_to_incant(t_ai *client)
{
  int	*level;
  int 	i;

  i = 0;
  if ((level = fill_array_on_lvl(client->level)) == NULL)
    return (false);
  while (i != MAXOBJECTTYPE)
    {
      if (client->objects[i] < level[i])
	{
	  free(level);
	  return (false);
	}
      i++;
    }
  free(level);
  return (true);
}

void	check_level_up(t_ai *client, t_queue *write_queue)
{
  if (compare_to_incant(client))
    {
      if (client->nb_player_incant
	  == players_needed(client->level
			    + client->nb_player_incant, client))
	{
	  client->brain->previous_act = 13;
	  client->brain->choice_ok = 8;
	  incant(client, write_queue);

	}
      else
	broadcast_ai(client, write_queue);
    }
  else
    {
      client->brain->previous_act = 0;
      client->brain->choice_ok = 1;
      random_moves(write_queue);
    }
}

void	broadcast_ally(t_ai *client,
			   t_queue *write_queue)
{
  client->brain->previous_act = 5;
  client->brain->stop++;
  if (!is_queue_empty(client->brain->broadcast_msg))
    {
      if (check_to_move(client, write_queue) == 1)
	return ;
    }
  else
    {
      if (client->brain->stop % 7 != 1)
	return ;
      if (compare_to_incant(client) == false)
	look(client, write_queue);
    }

}

bool	correct_level(char **tab, t_ai *client)
{
  if (tab && tab[1] != NULL)
    {
      if (strlen(tab[1]) == 3)
	if (((tab[1][0] - 48) == client->level) && (tab[1][2] - 48) > 0)
	  return (true);
    }
  return (false);
}