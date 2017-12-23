/*
** movements.c for nom_projet in /home/counil_m/project/nom_projet/movements.c
**
** Made By Maxime Counil
** Login <maxime.counil@epitech.eu>
**
** Started on Sun Jun 25 17:06:13:13 ${YEAH} Maxime Counil
** Last update on Sun Jun 25 17:06:13:13 ${YEAH} Maxime Counil
*/

#include <stdlib.h>
#include "ai.h"

void	random_moves(t_queue *write_queue)
{
  int 	random;

  random = rand() % 3;
  if (random == 1)
    insert_queue(write_queue, "Forward\n");
  else if (random == 2)
    insert_queue(write_queue, "Left\n");
  else
    insert_queue(write_queue, "Right\n");
}

void	move_to_stone(int cases, t_ai *client, t_queue *write_queue)
{
  cases--;
  if (cases >= 1 && cases <= 3)
    {
      insert_queue(write_queue, "Forward\n");
      if (cases - 2 > 0)
	insert_queue(write_queue, "Right\n");
      else
	insert_queue(write_queue, "Left\n");
    }
  else if (cases >= 4 && cases <= 8)
    {
      insert_queue(write_queue, "Forward\n");
      insert_queue(write_queue, "Forward\n");
      while (cases-- > 0)
	insert_queue(write_queue, "Right\n");
      while (cases++ < 0)
	insert_queue(write_queue, "Left\n");
    }
  client->brain->choice_ok = 0;
  client->brain->choice_ko = 0;
}

