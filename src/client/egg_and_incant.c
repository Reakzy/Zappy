/*
** egg_and_incant.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
**
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
**
** Started on  Sat Jun 24 13:08:26 2017 Samuel Osborne
** Last update Sat Jun 24 13:08:27 2017 Samuel Osborne
*/

#include <string.h>
#include "ai.h"

int 	check_floor(char **floor, int len, t_ai *client)
{
  if (floor[0] == NULL)
    {
      free_tab_len(floor, len);
      return (1);
    }
  fill_under_player(floor, client->msg_received);
  return (0);
}

int	need_player(t_ai *client)
{
  char 	**floor;
  int 	i;
  int 	nb_player;
  int 	len;

  nb_player = -1;
  i = -1;
  if ((floor = create_string_table((int) strlen(client->msg_received),
				   (len = (count_char(client->msg_received,
						      ' ') + 1)))) == NULL)
    return (0);
  if (check_floor(floor, len, client) == 1)
    return (1);
  while (floor[++i] != NULL)
    {
      if (strcmp(floor[i], "player") == 0)
	nb_player++;
    }
  if (nb_player == players_needed(client->level, client))
    {
      free_tab_len(floor, len);
      return (1);
    }
  free_tab_len(floor, len);
  return (0);
}

int 	check_incant_message(t_ai *client, t_queue *write_queue)
{
  if (strcmp(client->msg_received, "ok\n") == 0)
    {
      client->brain->choice_ok = 8;
      client->brain->previous_act = 8;
      insert_queue(write_queue, "Look\n");
      return (1);
    }
  if (client->brain->previous_act != 8)
    {
      insert_queue(write_queue, "Look\n");
      client->brain->previous_act = 8;
      client->brain->choice_ok = 8;
      client->brain->choice_ko = 8;
      return (1);
    }
  if (strcmp(client->msg_received, "ko\n") == 0)
    {
      look(client, write_queue);
      return (1);
    }
  return (0);
}

int 	check_incant_for_floor(t_ai *client, t_queue *write_queue)
{
  if (client->brain->previous_act == 8
      && check_stone_oncase(client, write_queue) == 1
      && need_player(client) == 1)
    {
      pick_all_on_floor(write_queue, client);
      drop_stones(client, write_queue);
      insert_queue(write_queue, "Incantation\n");
    }
  else if (need_player(client) == 0)
    {
      if (client->objects[FOOD] > 10)
	{
	  broadcast_ai(client, write_queue);
	  client->brain->choice_ok = 4;
	  client->brain->choice_ko = 4;
	  return (1);
	}
      else
	enough_food(client, write_queue);
    }
  else
    forward(client, write_queue);
  return (0);
}

void	incant(t_ai *client, t_queue *write_queue)
{
  if (check_incant_message(client, write_queue) == 1)
    return ;
  if (check_incant_for_floor(client, write_queue) == 1)
    return ;
  client->brain->choice_ok = 14;
  client->brain->choice_ko = 14;
}
