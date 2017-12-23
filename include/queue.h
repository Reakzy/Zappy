/*
** queue.h for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/queue.h
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Tue Jun 13 11:06:41 2017 Lucas Villeneuve
** Last update Tue Jun 13 11:06:41 2017 Lucas Villeneuve
*/

#ifndef QUEUE_H_
# define QUEUE_H_

# include <stdbool.h>

# define QUEUE_SIZE 10
# define BIGQUEUE_SIZE 20
# define CMD_SIZE 1024

typedef struct	s_queue
{
  int 		front;
  char 		**str;
  char 		*residue;
  size_t	queue_size;
}		t_queue;

int		containing_newline(char*);
void		free_queue(t_queue*);
void		insert_queue(t_queue*, char*);
bool		is_queue_full(t_queue*);
bool		is_queue_empty(t_queue*);
bool		check_if_error_queue(t_queue*, char*);
char		*pop_queue(t_queue*);
t_queue		*init_queue(bool big);

#endif /* !QUEUE_H_ */