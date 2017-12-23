/*
** case_pickup.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
** 
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
** 
** Started on  Sat Jul  1 19:18:10 2017 Samuel Osborne
** Last update Sat Jul  1 19:18:11 2017 Samuel Osborne
*/

#include <string.h>
#include "ai.h"

void	pickup_whats_needed(int *level,
				char **under_player,
				t_ai *client,
				t_queue *write_queue)
{
  char 	string_rock_to_enum[7][15];
  int 	i;
  int 	j;

  i = -1;
  strcpy(string_rock_to_enum[0], "food");
  strcpy(string_rock_to_enum[1], "linemate");
  strcpy(string_rock_to_enum[2], "deraumere");
  strcpy(string_rock_to_enum[3], "sibur");
  strcpy(string_rock_to_enum[4], "mendiane");
  strcpy(string_rock_to_enum[5], "phiras");
  strcpy(string_rock_to_enum[6], "thystme");
  while (++i <= 6)
    {
      j = -1;
      while (under_player[++j] != NULL)
	{
	  if (strcmp(under_player[j], string_rock_to_enum[i]) == 0)
	    {
	      if (strcmp(under_player[j], "food") == 0)
		take_object(level[i], write_queue);
	      choose_obj_to_pick(i, client, level, write_queue);
	    }
	}
    }
}

void	check_pickup(int pick_up, t_ai *client, t_queue *write_queue)
{
  if (pick_up == 1)
    {
      client->brain->previous_act = 3;
      client->brain->choice_ok = 13;
      client->brain->choice_ko = 13;
      check_level_up(client, write_queue);
    }
  else
    {
      client->brain->previous_act = 3;
      client->brain->choice_ok = 1;
      client->brain->choice_ko = 1;
      look(client, write_queue);
    }
}
