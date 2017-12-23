/*
** item.c for irc in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/villen_l/rendu/PSU/PSU_2016_myirc
** 
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
** 
** Started on  Mon May 29 13:21:42 2017 Lucas Villeneuve
** Last update Mon May 29 13:21:43 2017 Lucas Villeneuve
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "item.h"

t_item		*alloc_item()
{
  t_item	*item;

  if (!(item = (t_item*)malloc(1 * sizeof(*item))))
    {
      fprintf(stderr, "Malloc failed\n");
      return (NULL);
    }
  return (item);
}

void	init_item_by_default(t_item *this)
{
  if (this != NULL)
    {
      this->content = NULL;
      this->len = -1;
      this->prev = NULL;
      this->next = NULL;
    }
}

void	init_item_by_param(t_item *this, void *src_content, int src_len)
{
  if (this != NULL)
    {
      init_item_by_default(this);
      if (src_content != NULL && src_len > 0)
	{
	  this->content = malloc(src_len);
	  if (this->content != NULL)
	    {
	      this->content = memcpy(this->content, src_content, src_len);
	      this->len = src_len;
	    }
	}
    }
}

t_item		*new_item_by_param(void * src_content, int src_len)
{
  t_item	*item;

  item = alloc_item();
  if (item != NULL)
    init_item_by_param(item, src_content, src_len);
  return (item);
}

void	delete_item(t_item *this)
{
  if (this != NULL)
    {
      if (this->content != NULL)
	free(this->content);
      free(this);
    }
}