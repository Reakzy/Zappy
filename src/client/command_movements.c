/*
** command_movements.c for nom_projet in /home/counil_m/project/nom_projet/command_movements.c
**
** Made By Maxime Counil
** Login <maxime.counil@epitech.eu>
**
** Started on Wed Jun 21 15:17:41:41 ${YEAH} Maxime Counil
** Last update on Wed Jun 21 15:17:41:41 ${YEAH} Maxime Counil
*/

#include <stddef.h>
#include "ai.h"

void	set_client_objects(t_ai *client, char **vision)
{
  client->objects[FOOD] = number_items(vision[0], 5);
  client->objects[LINEMATE] = number_items(vision[1], 9);
  client->objects[DERAUMERE] = number_items(vision[2], 10);
  client->objects[SIBUR] = number_items(vision[3], 6);
  client->objects[MENDIANE] = number_items(vision[4], 9);
  client->objects[PHIRAS] = number_items(vision[5], 7);
  client->objects[THYSTAME] = number_items(vision[6], 9);
  client->brain->previous_act = 10;
  client->brain->choice_ok = 1;
}

void	parse_inventory(t_ai *client, t_queue *write_queue)
{
  char 	**vision;
  int	i;

  i = -1;
  if (client->msg_received == NULL ||
      ((vision = parse_receive(client)) == NULL))
    return ;
  while (++i <  7)
    if (vision[i] == NULL)
      {
	free_tab(vision);
	return ;
      }
  if (vision[0][5] < 48 || vision[0][5] > 57)
    {
      free_tab(vision);
      return ;
    }
  set_client_objects(client, vision);
  if (compare_to_incant(client) == true)
    incant(client, write_queue);
  else
    enough_food(client, write_queue);
  free_tab(vision);
}
