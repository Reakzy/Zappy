/*
** command_directions.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
** 
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
** 
** Started on  Sun Jul  2 21:51:39 2017 Samuel Osborne
** Last update Sun Jul  2 21:51:40 2017 Samuel Osborne
*/

#include "ai.h"

void	turn_left(t_ai *client, t_queue *write_queue)
{
  insert_queue(write_queue, "Left\n");
  client->brain->previous_act = 7;
  client->brain->choice_ok = 9;
}

void	turn_right(t_ai *client, t_queue *write_queue)
{
  insert_queue(write_queue, "Right\n");
  client->brain->previous_act = 6;
  client->brain->choice_ok = 9;
}

void	forward(t_ai *client, t_queue *write_queue)
{
  insert_queue(write_queue, "Forward\n");
  client->brain->previous_act = 11;
  client->brain->choice_ok = 9;
}

void	inventory(t_ai *client, t_queue *write_queue)
{
  insert_queue(write_queue, "Inventory\n");
  client->brain->previous_act = 9;
  client->brain->choice_ok = 10;
}
