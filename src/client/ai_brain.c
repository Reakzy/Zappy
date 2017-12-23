/*
** IAbasic.c for zappy in /home/counil_m/projet/PSU_2016_zappy/src/client
**
** Made by counil_m
** Login   <maxime.counil@epitech.eu>
**
** Started on  Thu Jun 15 11:08:53 2017 counil_m
** Last update Thu Jun 15 11:09:07 2017 counil_m
*/

#include <string.h>
#include <stdlib.h>
#include "zappy.h"
#include "ai.h"

int	parse_command(int i, t_ai *client, t_queue *write_queue)
{
  void (*command[16])(t_ai *, t_queue *);

  command[0] = &enough_food;
  command[1] = &look;
  command[2] = &parse_look;
  command[3] = &on_case;
  command[4] = &broadcast_ai;
  command[5] = &broadcast_ally;
  command[6] = &turn_right;
  command[7] = &turn_left;
  command[8] = &incant;
  command[9] = &inventory;
  command[10] = &parse_inventory;
  command[11] = &forward;
  command[12] = &reproduction;
  command[13] = &check_level_up;
  command[14] = &check_incant;
  command[15] = &get_food;
  if (client->incant != true && client->brain->stop == 0)
    command[i](client, write_queue);
  else
    check_incant(client, write_queue);
  return (0);
}

void	init_brain_and_client(t_ai *client)
{
  int 	i;

  i = 0;
  while (i != MAXOBJECTTYPE)
    client->objects[i++] = 0;
  client->level = 1;
  client->server_fd = 0;
  client->nbr_teammates = 0;
  client->connected = false;
  client->incant = false;
  client->msg_received = NULL;
  client->nb_player_incant = 0;
  client->brain->previous_act = -1;
  client->brain->choice_ok = -1;
  client->brain->choice_ko = -1;
  client->brain->stop = 0;
  if (!(client->brain->broadcast_msg = init_queue(false)))
    return ;
}

int 	compare_on_case(t_ai *client, t_queue *write_queue)
{
  if (strncmp(client->msg_received, "message 0, on case",
	      strlen("message 0, on case")) == 0)
    {
      client->brain->previous_act = 0;
      incant(client, write_queue);
      return (1);
    }
  return (0);
}


int 	compare_message(t_ai *client, t_queue *write_queue, char *str)
{
  if (compare_on_case(client, write_queue) == 1)
    return (0);
  if (strncmp(client->msg_received, "message", 7) == 0
      && client->brain->stop != -1)
    {
      insert_queue(client->brain->broadcast_msg, str);
      if (check_broadcast(client) == 0)
	broadcast_ally(client, write_queue);
      else
	{
	  if (!is_queue_empty(client->brain->broadcast_msg))
	    pop_queue(client->brain->broadcast_msg);
	  insert_queue(write_queue, "Look\n");
	  client->brain->choice_ok = 2;
	  return (0);
	}
    }
  strncmp(str, "ko", strlen("ko")) == 0 ?
  parse_command(client->brain->choice_ko, client, write_queue) :
  parse_command(client->brain->choice_ok, client, write_queue);
  return (0);
}

void	brain_ai(t_ai *client, t_queue *write_queue, t_queue *read_queue)
{
  char 	*str;

  if (client->brain->choice_ok == -1 && client->brain->previous_act == -1)
    parse_command(12, client, write_queue);
  if (!is_queue_empty(read_queue))
    {
      if ((str = pop_queue(read_queue)) == NULL)
	return ;
      client->msg_received = str;
      if (client->brain->stop == -1)
	{
	  if (strncmp(client->msg_received, "Current", 7) == 0)
	    {
	      client->level++;
	      client->brain->stop = 0;
	      client->brain->previous_act = 14;
	      client->brain->choice_ok = 0;
	      enough_food(client, write_queue);
	    }
	  return ;
	}
      compare_message(client, write_queue, str);
      free(str);
    }
}
