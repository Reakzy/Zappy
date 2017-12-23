/*
** move_for_broadcast.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
**
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
**
** Started on  Sat Jun 24 13:27:38 2017 Samuel Osborne
** Last update Sat Jun 24 13:27:39 2017 Samuel Osborne
*/

#include <stdlib.h>
#include "queue.h"
#include "ai.h"

int 	get_direction(char **msg)
{
  int 	i;

  i = -1;
  if (msg && msg[0] != NULL)
    {
      while (msg[0][++i] != '\0')
	if (msg[0][i] >= 48 && msg[0][i] <= 57)
	  return (msg[0][i] - 48);
    }
  return (0);
}

int 		move_c_forward(t_queue *write_queue)
{
  insert_queue(write_queue, "Forward\n");
  return (0);
}

int 		move_c_diagonal_f_left(t_queue *write_queue)
{
  insert_queue(write_queue, "Left\n");
  insert_queue(write_queue, "Forward\n");
  insert_queue(write_queue, "Right\n");
  insert_queue(write_queue, "Forward\n");
  return (0);
}

int 		move_c_left(t_queue *write_queue)
{
  insert_queue(write_queue, "Left\n");
  insert_queue(write_queue, "Forward\n");
  return (0);
}

void		move_to_broadcast(t_queue *write_queue, int direction)
{
  int		(*ptrfnc[8])(t_queue *);

  ptrfnc[0] = &move_c_forward;
  ptrfnc[1] = &move_c_diagonal_f_left;
  ptrfnc[2] = &move_c_left;
  ptrfnc[3] = &move_c_diagonal_b_left;
  ptrfnc[4] = &move_c_behind;
  ptrfnc[5] = &move_c_diagonal_b_right;
  ptrfnc[6] = &move_c_right;
  ptrfnc[7] = &move_c_diagonal_f_right;
  if (direction - 1>= 0)
    ptrfnc[direction - 1](write_queue);
}
