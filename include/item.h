/*
** item.h for irc in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/villen_l/rendu/PSU/PSU_2016_myirc
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Mon May 29 13:21:09 2017 Lucas Villeneuve
** Last update Mon May 29 13:21:10 2017 Lucas Villeneuve
*/

#ifndef ITEM_H_
# define ITEM_H_

typedef struct	s_item
{
  void		*content;
  int		len;
  struct s_item *prev;
  struct s_item *next;
}		t_item;

t_item		*new_item_by_default(void);
t_item		*new_item_by_param(void *src_content, int src_len);
void		delete_item(t_item *);

#endif /* !ITEM_H_ */