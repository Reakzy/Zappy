/*
** broadcast_parse_move.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
**
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
**
** Started on  Sat Jun 24 12:47:30 2017 Samuel Osborne
** Last update Sat Jun 24 12:47:36 2017 Samuel Osborne
*/

#include "ai.h"

int 		move_c_diagonal_b_left(t_queue *write_queue)
{
  insert_queue(write_queue, "Left\n");
  insert_queue(write_queue, "Forward\n");
  insert_queue(write_queue, "Left\n");
  insert_queue(write_queue, "Forward\n");
  return (0);
}

int 		move_c_behind(t_queue *write_queue)
{
  insert_queue(write_queue, "Right\n");
  insert_queue(write_queue, "Right\n");
  insert_queue(write_queue, "Forward\n");
  return (0);
}

int 		move_c_diagonal_b_right(t_queue *write_queue)
{
  insert_queue(write_queue, "Right\n");
  insert_queue(write_queue, "Forward\n");
  insert_queue(write_queue, "Right\n");
  insert_queue(write_queue, "Forward\n");
  return (0);
}

int 		move_c_right(t_queue *write_queue)
{
  insert_queue(write_queue, "Right\n");
  insert_queue(write_queue, "Forward\n");
  return (0);
}

int 		move_c_diagonal_f_right(t_queue *write_queue)
{
  insert_queue(write_queue, "Forward\n");
  insert_queue(write_queue, "Right\n");
  insert_queue(write_queue, "Forward\n");
  return (0);
}
