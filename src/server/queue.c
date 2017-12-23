/*
** queue.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/queue.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Tue Jun 13 11:06:28 2017 Lucas Villeneuve
** Last update Tue Jun 13 11:06:28 2017 Lucas Villeneuve
*/

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

t_queue		*init_queue(bool big)
{
  size_t	i;
  t_queue	*this;

  if (!(this = calloc(1, sizeof(t_queue))) ||
      !(this->residue = calloc(CMD_SIZE, sizeof(char))))
    {
      perror("Error calloc");
      return (NULL);
    }
  this->front = -1;
  (big) ? (this->queue_size = BIGQUEUE_SIZE) : (this->queue_size = QUEUE_SIZE);
  if (!(this->str = calloc(this->queue_size, sizeof(char*))))
    {
      perror("Error calloc");
      return (NULL);
    }
  i = 0;
  while (i < this->queue_size)
    if (!(this->str[i++] = calloc(CMD_SIZE, sizeof(char))))
      {
	perror("Error calloc");
	return (NULL);
      }
  return (this);
}

void	insert_queue(t_queue *this, char *str)
{
  char	*ptr;
  int 	len;
  int	i;

  if (check_if_error_queue(this, str))
    {
      ptr = str;
      while ((len = containing_newline(ptr)) != -1)
	{
	  if (this->front + 1 >= (int)this->queue_size)
	    {
	      fprintf(stderr, "Error : queue is full."
	       " Cannot add command : '%s'\n", ptr);
	      return ;
	    }
	  strncat(this->residue, ptr, (size_t)len + 1);
	  this->residue[strlen(this->residue) + 1] = 0;
	  memmove(this->str[++this->front], this->residue, strlen(this->residue));
	  this->str[this->front][strlen(this->residue)] = 0;
	  memset(this->residue, 0, CMD_SIZE);
	  i = 0;
	  while (i++ <= len)
	    ptr++;
	}
    }
}

char		*pop_queue(t_queue *this)
{
  char		*ret;
  size_t	i;

  if (this->front >= 0)
    {
      if (!(ret = strdup(this->str[0])))
	{
	  perror("Erreur malloc");
	  return (NULL);
	}
      --this->front;
      i = 0;
      while (i + 1 < this->queue_size)
	{
	  memmove(this->str[i], this->str[i + 1], strlen(this->str[i + 1]));
	  this->str[i][strlen(this->str[i + 1])] = 0;
	  ++i;
	}
      return (ret);
    }
  else
    {
      fprintf(stderr, "Warning, queue is empty\n");
      return (NULL);
    }
}

void		free_queue(t_queue *this)
{
  size_t	i;

  i = 0;
  while (i < this->queue_size)
    free(this->str[i++]);
  free(this->str);
  free(this->residue);
  free(this);
}