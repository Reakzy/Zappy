/*
** list.h for irc in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/villen_l/rendu/PSU/PSU_2016_myirc
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Mon May 29 13:21:16 2017 Lucas Villeneuve
** Last update Mon May 29 13:21:16 2017 Lucas Villeneuve
*/

#ifndef LIST_H_
# define LIST_H_

# include "item.h"

typedef struct	s_list
{
    int		len;
    int		empty;
    t_item	*head;
    t_item	*tail;
    void	(*add_front)(struct s_list *this, void *data, int len);
    void	(*add_back)(struct s_list *this, void *data, int len);
    void	(*iter)(struct s_list *this, void (*f)(void*, int));
}		t_list;

t_list		*new_list_by_default(void);
void		delete_list(t_list * this);
void		list_add_front(t_list *this, void *data, int len);
void		list_add_back(t_list *this, void *data, int len);
void		list_iter(t_list *this, void (*f)(void*, int));

#endif /* !LIST_H_ */