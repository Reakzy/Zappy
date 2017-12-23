/*
** error_queue.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/error_queue.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Thu Jun 15 13:37:14 2017 Lucas Villeneuve
** Last update Thu Jun 15 13:37:14 2017 Lucas Villeneuve
*/

#include <string.h>
#include <stdio.h>
#include "queue.h"

bool	check_if_error_queue(t_queue *this, char *str)
{
  if (!str)
    return (false);
  if (strlen(this->residue) + strlen(str) >= CMD_SIZE)
    {
      fprintf(stderr, "Error, command too long\n");
      memset(this->residue, 0, CMD_SIZE);
    }
  else if (this->front + 1 >= (int)this->queue_size)
    fprintf(stderr, "Error : queue is full. Cannot add command : '%s'\n",
	    str);
  else if (containing_newline(str) == -1)
    strcat(this->residue, str);
  else
    return (true);
  return (false);
};

bool	is_queue_empty(t_queue *this)
{
  if (this->front >= 0)
    return (false);
  return (true);
}

bool	is_queue_full(t_queue *this)
{
  if (this->front + 1 >= (int)this->queue_size)
    return (true);
  return (false);
}

int	containing_newline(char *str)
{
  int	i;

  i = 0;
  if (str)
    while (str[i])
      {
	if (str[i] == '\n')
	  return (i);
	++i;
      }
  return (-1);
}
