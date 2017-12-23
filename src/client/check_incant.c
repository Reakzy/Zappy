/*
** check_incant.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
**
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
**
** Started on  Sat Jul  1 18:17:01 2017 Samuel Osborne
** Last update Sat Jul  1 18:17:02 2017 Samuel Osborne
*/

#include <string.h>
#include <stdlib.h>
#include "ai.h"

int 	check_incant_for_ko(t_ai *client, t_queue *write_queue)
{
  if (strcmp(client->msg_received, "Elevation underway\n") == 0)
    {
      client->incant = true;
      client->msg_received = NULL;
      return (1);
    }
  if (strncmp(client->msg_received, "ko", strlen("ko")) == 0 &&
      client->incant == false)
    {
      client->brain->previous_act = 14;
      client->brain->choice_ok = 0;
      enough_food(client, write_queue);
      return (1);
    }
  if (client->msg_received == NULL)
    {
      client->brain->previous_act = 14;
      client->brain->choice_ok = 0;
      enough_food(client, write_queue);
      return (1);
    }
  return (0);
}

void	check_incant(t_ai *client, t_queue *write_queue)
{
  if ((check_incant_for_ko(client, write_queue)) == 1)
    return ;
  if (strncmp(client->msg_received, "ko", strlen("ko")) == 0)
    {
      client->incant = false;
      client->brain->previous_act = 14;
      client->brain->choice_ok = 0;
      enough_food(client, write_queue);
    }
  else if (strncmp(client->msg_received, "Current", 7) == 0)
    {
      client->brain->stop = 0;
      client->level++;
      client->incant = false;
      client->brain->previous_act = 14;
      client->brain->choice_ok = 0;
      enough_food(client, write_queue);
    }
  else if (strncmp(client->msg_received, "ko", strlen("ko")) == 0)
    {
      client->brain->previous_act = 14;
      client->brain->choice_ok = 0;
      enough_food(client, write_queue);
    }
}

void 	set_objects_incant(int *level, int i, t_queue *write_queue)
{
  int 	a;
  char 	stone[7][15];

  strcpy(stone[0], "food");
  strcpy(stone[1], "linemate");
  strcpy(stone[2], "deraumere");
  strcpy(stone[3], "sibur");
  strcpy(stone[4], "mendiane");
  strcpy(stone[5], "phiras");
  strcpy(stone[6], "thystame");
  a = -1;
  while (++a != level[i])
    {
      insert_queue(write_queue,
		   concat_strings(concat_strings(strdup("Set "),
						 stone[i]), "\n"));
    }
}

void	drop_stones(t_ai *client, t_queue *write_queue)
{
  int 	*level;
  int 	i;
  int 	cnt;

  cnt = 0;
  i = 0;
  if ((level = fill_array_on_lvl(client->level)) == NULL)
    return ;
  while (++i != MAXOBJECTTYPE)
    {
      if (client->objects[i] >= level[i])
	{
	  cnt++;
	  set_objects_incant(level, i, write_queue);
	}
    }
  free(level);
}

int 	check_stone_oncase(t_ai *client, t_queue *write_queue)
{
  char 	**under_player;
  int 	ret;
  int 	len;

  ret = 1;
  under_player = create_string_table((int)strlen(client->msg_received),
				     (len =
				      count_char(client->msg_received, ' ')
				      + 1));
  fill_under_player(under_player, client->msg_received);
  if (strlen(under_player[0]) > strlen("player"))
    {
      ret--;
      forward(client, write_queue);
    }
  free_tab_len(under_player, len);
  return (ret);
}
