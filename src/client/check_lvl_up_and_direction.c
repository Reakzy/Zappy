/*
** check_lvl_up_and_direction.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
**
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
**
** Started on  Sat Jul  1 18:33:51 2017 Samuel Osborne
** Last update Sat Jul  1 18:33:52 2017 Samuel Osborne
*/

#include <string.h>
#include "ai.h"

int 	check_broadcast(t_ai *client)
{
  char **msg;

  if ((msg = create_string_table((int) strlen(client->msg_received),
				 count_char(client->msg_received, ',') + 1))
      == NULL)
    return (1);
  fill_string_array(client->msg_received, msg, ',');
  if (correct_level(msg, client))
    return (0);
  return (1);
}

int 	check_direction(int direction, t_queue *write_queue, t_ai *client,
			   char **msg)
{
  if (direction == 0)
    {
      client->brain->stop = -1;
      insert_queue(write_queue, "Broadcast on case\n");
    }
  else if (correct_level(msg, client))
    {
      move_to_broadcast(write_queue, direction);
      client->brain->choice_ok = 0;
      client->brain->choice_ok = 0;
    }
  return (0);
}

int 	check_to_move(t_ai *client, t_queue *write_queue)
{
  char	**msg;
  char 	*str;
  int 	direction;
  int 	len;

  if ((str = pop_queue(client->brain->broadcast_msg)) == NULL)
    return (1);
  if (client->brain->stop % 7 == 1)
    {
      if (count_char(str, ',') != 7)
	return (1);
      if ((msg = create_string_table((int) strlen(str),
				     (len = count_char(str, ',') + 1))) == NULL)
	return (1);
      fill_string_array(str, msg, ',');
      direction = get_direction(msg);
      check_direction(direction, write_queue, client, msg);
      free_tab_len(msg, len);
    }
  return (0);
}
