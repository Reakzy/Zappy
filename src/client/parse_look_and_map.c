/*
** parse_look_and_map.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
**
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
**
** Started on  Sat Jul  1 19:16:55 2017 Samuel Osborne
** Last update Sat Jul  1 19:16:56 2017 Samuel Osborne
*/

#include <string.h>
#include "ai.h"

void	look_or_forward(t_ai *client, t_queue *write_queue)
{
  if (client->brain->previous_act == 11 &&
      strcmp(client->msg_received, "ok\n") == 0)
    look(client, write_queue);
  forward(client, write_queue);
}

void	parse_map(t_ai *client, t_queue *write_queue)
{
  int 	i;
  int 	a;
  int 	virg;
  char	stone[8];

  strcpy(stone, "fldsmpt");
  i = -1;
  while (stone[++i])
    {
      a = 0;
      virg = 1;
      while (client->msg_received[++a])
	{
	  if (client->msg_received[a] == ',')
	    virg++;
	  if (client->msg_received[a] == ',' || client->msg_received[a] == ' ')
	    if (client->msg_received[a + 1] == stone[i] && virg > 1)
	      {
		move_to_stone(virg, client, write_queue);
		client->brain->choice_ok = 3;
		return ;
	      }
	}
    }
  look_or_forward(client, write_queue);
}

void	parse_look(t_ai *client,
		       t_queue *write_queue)
{
  char 	**under_player;
  int 	len;

  under_player = create_string_table((int)strlen(client->msg_received),
				     (len = count_char(client->msg_received, ' ') + 1));
  fill_under_player(under_player, client->msg_received);
  if (under_player[1] != NULL)
    on_case(client, write_queue);
  else
    parse_map(client, write_queue);
  free_tab_len(under_player, len);
}
