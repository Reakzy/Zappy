/*
** buffer.h for PSU_2016_myirc in /home/villen_l/rendu/PSU_2016_myirc/buffer.h
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Fri May 26 13:53:58 2017 Lucas Villeneuve
** Last update Fri May 26 13:53:58 2017 Lucas Villeneuve
*/

#ifndef BUFFER_H_
# define BUFFER_H_

# define CMD_SIZE 512

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>

typedef struct	s_cbuff
{
  char		buff[CMD_SIZE];
  size_t	start;
  size_t	end;
  size_t	size;
  int		count;
}		t_cbuff;

void		cbuff_init(t_cbuff *cb);
void		cbuff_add(t_cbuff *cb, const char *str);
char		*cbuff_remove(t_cbuff *cb);
bool		cbuff_is_there_cmd(t_cbuff *cb);
void		error_and_clean_buffer(t_cbuff *cb);

#endif /* !BUFFER_H_ */