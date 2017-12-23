/*
** list.c for irc in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/villen_l/rendu/PSU/PSU_2016_myirc
** 
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
** 
** Started on  Mon May 29 13:21:34 2017 Lucas Villeneuve
** Last update Mon May 29 13:21:35 2017 Lucas Villeneuve
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

t_list		*alloc_list()
{
  t_list	*list;

  if (!(list = (t_list*)malloc(1 * sizeof(*list))))
    {
      fprintf(stderr, "Malloc failed\n");
      return (NULL);
    }
  return (list);
}

void	init_list_by_default(t_list * this)
{
  if (this != NULL)
    {
      this->len = 0;
      this->empty = 1;
      this->head = NULL;
      this->tail = NULL;
      this->add_front = &list_add_front;
      this->add_back = &list_add_back;
      this->iter = &list_iter;
    }
}

t_list		*new_list_by_default()
{
  t_list	*list;

  list = alloc_list();
  if (list != NULL)
    init_list_by_default(list);
  return (list);
}

void	delete_list_items(t_item *the_item)
{
  if (the_item != NULL)
    {
      if (the_item->next != NULL)
	delete_list_items(the_item->next);
      delete_item(the_item);
    }
}

void	delete_list(t_list * this)
{
  if (this != NULL)
    {
      if (this->empty == 0)
	{
	  delete_list_items(this->head);
	  this->len = 0;
	  this->empty = 1;
	  this->head = NULL;
	  this->tail = NULL;
	}
      free(this);
    }
}