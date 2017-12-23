/*
** list_add.c for PSU_2016_myirc in /home/villen_l/rendu/PSU_2016_myirc/list_add.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Mon May 29 13:19:26 2017 Lucas Villeneuve
** Last update Mon May 29 13:19:26 2017 Lucas Villeneuve
*/

#include <stddef.h>
#include "list.h"

void	list_add_front_real(t_list *this, t_item *item)
{
  if (this != NULL)
    {
      if (item != NULL)
	{
	  item->prev = NULL;
	  item->next = this->head;
	  if (this->head != NULL)
	    this->head->prev = item;
	  if (this->tail == NULL)
	    this->tail = item;
	  this->head = item;
	  this->len += 1;
	  this->empty = 0;
	}
    }
}

void	list_add_back_real(t_list * this, t_item * item)
{
  if (this != NULL)
    {
      if (item != NULL)
	{
	  item->prev = this->tail;
	  item->next = NULL;
	  if (this->tail != NULL)
	    this->tail->next = item;
	  if (this->head == NULL)
	    this->head = item;
	  this->tail = item;
	  this->len += 1;
	  this->empty = 0;
	}
    }
}

void	list_add_front(t_list *this, void *data, int len)
{
  list_add_front_real(this, new_item_by_param(data, len));
}

void	list_add_back(t_list *this, void *data, int len)
{
  list_add_back_real(this, new_item_by_param(data, len));
}

void		list_iter(t_list * this, void (*f)(void*, int))
{
  t_item	*current;

  if (this != NULL && f != NULL)
    {
      current = this->head;
      while (current != NULL)
	{
	  f(current->content, current->len);
	  current = current->next;
	}
    }
  return ;
}