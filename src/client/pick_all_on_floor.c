/*
** pick_all_on_floor.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
**
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
**
** Started on  Wed Jun 28 09:48:51 2017 Samuel Osborne
** Last update Wed Jun 28 09:48:55 2017 Samuel Osborne
*/

#include <string.h>
#include "ai.h"

void		get_food(t_ai *client, t_queue *write_queue)
{
  char		**floor;
  int 		i;
  int 		food;
  int		len;

  i = -1;
  food = 0;
  if ((floor = create_string_table((int) strlen(client->msg_received),
				   (len = (count_char(client->msg_received,
						     ' ') + 1)))) == NULL)
    return ;
  fill_under_player(floor, client->msg_received);
  while (floor[++i])
    {
      if (strcmp(floor[i], "food") == 0)
	{
	  food++;
	  insert_queue(write_queue, "Take food\n");
	}
    }
  (food == 0) ? parse_map(client, write_queue) : on_case(client, write_queue);
  free_tab_len(floor, len);
}

void		send_take_obj(int i, char **floor, t_queue *write_queue)
{
  int 		j;
  char 		stones[7][15];

  j = -1;
  strcpy(stones[0], "linemate");
  strcpy(stones[1], "deraumere");
  strcpy(stones[2], "sibur");
  strcpy(stones[3], "mendiane");
  strcpy(stones[4], "phiras");
  strcpy(stones[5], "thystame");
  strcpy(stones[6], "food");
  while (++j <= 6)
    if (strcmp(floor[i], stones[j]) == 0)
      insert_queue(write_queue,
		   concat_strings(concat_strings(strdup("Take "),
						 stones[j]), "\n"));
}

int 		pick_all_on_floor(t_queue *write_queue, t_ai *client)
{
  char 		**floor;
  int 		i;
  int 		len;

  i = -1;
  if ((floor = create_string_table((int) strlen(client->msg_received),
				   (len = count_char(client->msg_received, ' ')
					  + 1))) == NULL)
    return (1);
  fill_under_player(floor, client->msg_received);
  while (floor[++i] != NULL)
    send_take_obj(i, floor, write_queue);
  free_tab_len(floor, len);
  return (0);
}