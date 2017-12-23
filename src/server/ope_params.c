/*
** init.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/init.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Fri Jun 09 16:32:52 2017 Lucas Villeneuve
** Last update Fri Jun 09 16:32:52 2017 Lucas Villeneuve
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

void		init_default_teams(t_params *params, int i)
{
  char 		buf[17];

  snprintf(buf, 16, "Team%d", i + 1);
  if (!(params->teams[i] = strdup(buf)))
    {
      perror("Erreur malloc");
      exit(84);
    }
}

void		init_params(t_params *params)
{
  size_t 	i;

  params->port = 4242;
  params->width = 10;
  params->height = 10;
  params->clientsNb = 3;
  params->freq = 100;
  params->nb_teams = 2;
  if (!(params->teams = calloc(3, sizeof(char*))))
    {
      perror("Erreur calloc");
      exit(84);
    }
  i = 0;
  while (i <= 2)
    params->teams[i++] = NULL;
  init_default_teams(params, 0);
  init_default_teams(params, 1);
}

size_t 		init_ptrfnc_params(int (*ptrfnc[6])(int, const char**,
							  t_params*, size_t*),
					 t_params *params)
{
  size_t 	i;

  init_params(params);
  i = 0;
  ptrfnc[i++] = &port_param;
  ptrfnc[i++] = &width_param;
  ptrfnc[i++] = &height_param;
  ptrfnc[i++] = &name_param;
  ptrfnc[i++] = &clients_param;
  ptrfnc[i++] = &freq_param;
  return (i);
}

void		free_params(t_params *params)
{
  size_t 	i;

  i = 0;
  while (i < params->nb_teams)
    {
      if (params->teams[i])
	free(params->teams[i]);
      ++i;
    }
  free(params->teams);
}