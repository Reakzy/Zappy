/*
** exec_client_cooldown.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/exec_client_cooldown.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Sat Jun 24 10:28:55 2017 Lucas Villeneuve
** Last update Sat Jun 24 10:28:55 2017 Lucas Villeneuve
*/

#include <string.h>
#include "server.h"

void	seven_cooldown(__attribute__((unused))t_server *server,
			   t_client *client)
{
  client->cooldown = 7;
}

size_t		init_ptrfnc_cooldown(void (*ptrfnc[])(t_server*, t_client*))
{
  size_t	i;

  i = 0;
  ptrfnc[i++] = &seven_cooldown;
  ptrfnc[i++] = &seven_cooldown;
  ptrfnc[i++] = &seven_cooldown;
  ptrfnc[i++] = &seven_cooldown;
  ptrfnc[i++] = &inventory_cooldown;
  ptrfnc[i++] = &seven_cooldown;
  ptrfnc[i++] = &connect_nbr_cooldown;
  ptrfnc[i++] = &fork_cooldown;
  ptrfnc[i++] = &seven_cooldown;
  ptrfnc[i++] = &seven_cooldown;
  ptrfnc[i++] = &seven_cooldown;
  ptrfnc[i++] = &incantation_cooldown;
  return (i);
}

void		interpret_cmd_cooldown(t_server *server,
					   t_client *client,
					   const char **cmd)
{
  int	 	i;
  size_t	j;
  void		(*ptrfnc[12])(t_server*, t_client*);
  char		tab[12][12];

  j = init_ptrfnc_cooldown(ptrfnc);
  strcpy(tab[0], "Forward");
  strcpy(tab[1], "Right");
  strcpy(tab[2], "Left");
  strcpy(tab[3], "Look");
  strcpy(tab[4], "Inventory");
  strcpy(tab[5], "Broadcast");
  strcpy(tab[6], "Connect_nbr");
  strcpy(tab[7], "Fork");
  strcpy(tab[8], "Eject");
  strcpy(tab[9], "Take");
  strcpy(tab[10], "Set");
  strcpy(tab[11], "Incantation");
  client->cooldown = 0;
  i = -1;
  while (++i < (int)j)
    if (strcmp(tab[i], cmd[0]) == 0)
      return (ptrfnc[i](server, client));
}
