/*
** utils_look.c for utils_vision in /home/leo/Tek2/USP_Networks/PSU_2016_zappy
**
** Made by Leo
** Login   <leo.camberou@epitech.eu>
**
** Started on  Fri Jun 16 14:41:12 2017 Leo
** Last update Tue Jun 20 14:45:17 2017 Leo
*/

#include <string.h>
#include "server.h"

void		look_tile_objects(t_server *server,
				      t_client *client,
				      t_pos *pos, bool first)
{
  size_t	i;
  char		tab[MAXOBJECTTYPE][10];

  strcpy(tab[FOOD], "food");
  strcpy(tab[LINEMATE], "linemate");
  strcpy(tab[DERAUMERE], "deraumere");
  strcpy(tab[SIBUR], "sibur");
  strcpy(tab[MENDIANE], "mendiane");
  strcpy(tab[PHIRAS], "phiras");
  strcpy(tab[THYSTAME], "thystame");
  i = 0;
  while (i < MAXOBJECTTYPE)
    {
      if (server->map[pos->y][pos->x].objects[i] > 0)
	{
	  (!first) ? insert_queue(client->exit_queue, " ")
		   : (first = false);
	  insert_queue(client->exit_queue, tab[i]);
	}
      ++i;
    }
}

void		look_tile(t_server *server, t_client *client, t_pos *pos)
{
  t_item	*current;
  t_client	*clnt;
  bool		first;

  first = true;
  if (server->clients)
    {
      current = server->clients->head;
      while (current)
	{
	  clnt = (t_client*)current->content;
	  if (clnt->logged && clnt->pos.x == pos->x && clnt->pos.y == pos->y)
	    {
	      (!first) ? insert_queue(client->exit_queue, " ")
		       : (first = false);
	      insert_queue(client->exit_queue, "player");
	    }
	  current = current->next;
	}
    }
  look_tile_objects(server, client, pos, first);
}
