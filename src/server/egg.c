/*
** egg.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/egg.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Thu Jun 22 16:10:12 2017 Lucas Villeneuve
** Last update Thu Jun 22 16:10:12 2017 Lucas Villeneuve
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

void	delete_egg(t_item *current, t_list *eggs)
{
  (current->prev == NULL) ? (eggs->head = current->next)
			  : (current->prev->next = current->next);
  (current->next == NULL) ? (eggs->tail = current->prev)
			  : (current->next->prev = current->prev);
  if (--eggs->len <= 0)
    eggs->empty = 1;
  delete_item(current);
}

void	send_gui_egg_hatched(t_server *server, t_egg *egg)
{
  char	buf[15];

  if (server->gui)
    {
      snprintf(buf, 14, "eht %lu\n", egg->id);
      insert_queue(server->gui->exit_queue, buf);
    }
}

void		timer_eggs(t_server *server, t_list *eggs)
{
  t_item	*current;
  t_egg		*egg;

  if (eggs)
    {
      current = eggs->head;
      while (current)
	{
	  egg = (t_egg*)current->content;
	  if (!egg->hatched)
	    {
	      if (egg->hatch_timer > 0)
		--egg->hatch_timer;
	      else
		{
		  ++egg->team->nbClientsLeft;
		  egg->hatched = true;
		  send_gui_egg_hatched(server, egg);
		}
	    }
	  current = current->next;
	}
    }
}

t_item		*get_first_hatched_egg(t_list *eggs, const char *str)
{
  t_item	*current;
  t_egg		*egg;

  int i = 0;

  if (eggs)
    {
      current = eggs->head;
      while (current)
	{
	  egg = (t_egg*)current->content;
	  if (egg->hatched && strcmp(str, egg->team->name) == 0)
	    return (current);
	  current = current->next;
	  i++;
	}
    }
  return (NULL);
}

void		spawn_client_on_egg(t_server *server,
					t_client *client,
					const char *str)
{
  t_item	*current;
  t_egg		*egg;
  char 		buf[15];

  if ((current = get_first_hatched_egg(server->eggs, str)))
    {
      egg = (t_egg*)current->content;
      client->pos = egg->pos;
      client->born_from_egg = true;
      if (server->gui)
	{
	  snprintf(buf, 14, "ebo %lu\n", egg->id);
	  insert_queue(server->gui->exit_queue, buf);
	}
      delete_egg(current, server->eggs);
    }
}