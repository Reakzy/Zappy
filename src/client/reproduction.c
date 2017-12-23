/*
** reproduction.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
** 
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
** 
** Started on  Sun Jul  2 21:53:39 2017 Samuel Osborne
** Last update Sun Jul  2 21:53:40 2017 Samuel Osborne
*/

#include "ai.h"

void	reproduction(t_ai *client,
			 t_queue *write_queue)
{
  if (client->nbr_teammates > 0)
    insert_queue(write_queue, "Fork\n");
  client->brain->previous_act = 12;
  insert_queue(write_queue, "Look\n");
  client->brain->choice_ok = 0;
}
