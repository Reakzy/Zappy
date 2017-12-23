/*
** on_case.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
**
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
**
** Started on  Sat Jun 24 13:27:54 2017 Samuel Osborne
** Last update Sat Jun 24 13:27:54 2017 Samuel Osborne
*/

#include <string.h>
#include <stdlib.h>
#include "ai.h"

void	fill_under_player(char **under_player, char *msg)
{
  int 	i;
  int 	k;
  int 	l;

  i = 1;
  k = 0;
  l = 0;
  if (msg && msg[1] != 0)
    {
      if (msg[0] == ' ')
	i++;
      while (msg[i] != '\0' && msg[i] != ',')
	{
	  if (msg[i] != ' ')
	    under_player[k][l++] = msg[i];
	  else
	    {
	      k++;
	      l = 0;
	    }
	  i++;
	}
      under_player[k + 1] = NULL;
    }
}

void	take_object(int rock, t_queue *write_queue)
{
  char	object_to_take[7][15];
  char 	*msg;

  if (rock >= 0 && rock <= 6)
    {
      strcpy(object_to_take[0], "food");
      strcpy(object_to_take[1], "linemate");
      strcpy(object_to_take[2], "deraumere");
      strcpy(object_to_take[3], "sibur");
      strcpy(object_to_take[4], "mendiane");
      strcpy(object_to_take[5], "phiras");
      strcpy(object_to_take[6], "thystme");
    }
  msg = concat_strings(strdup("Take "), object_to_take[rock]);
  msg = concat_strings(msg, "\n");
  insert_queue(write_queue, msg);
}

void	choose_obj_to_pick(int i, t_ai *client, int *level,
			       t_queue *write_queue)
{
  if (i > 0 && level[i] >= 1 && client->objects[i] <= level[i])
    take_object(i, write_queue);
}

void	on_case(t_ai *client, t_queue *write_queue)
{
  int 	*level;
  char 	**under_player;
  int 	pick_up;
  int	len;

  pick_up = 0;
  if ((level = fill_array_on_lvl(client->level)) == NULL)
    return ;
  under_player = create_string_table((int)strlen(client->msg_received),
				     (len = count_char(client->msg_received, ' ') + 1));
  fill_under_player(under_player, client->msg_received);
  if (level != NULL)
    {
      pick_up++;
      pickup_whats_needed(level, under_player, client, write_queue);
    }
  if (level)
    free (level);
  free_tab_len(under_player, len);
  check_pickup(pick_up, client, write_queue);
}
