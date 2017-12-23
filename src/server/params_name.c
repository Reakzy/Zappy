/*
** params_name.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/params_name.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Fri Jun 09 16:31:30 2017 Lucas Villeneuve
** Last update Fri Jun 09 16:31:30 2017 Lucas Villeneuve
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

size_t		nb_param_names(int argc, const char **tab, size_t index)
{
  size_t	count;

  count = 0;
  while (index < (size_t)argc)
    {
      if (tab[index][0] == '-')
	return (count);
      ++index;
      ++count;
    }
  return (count);
}

bool		name_already_exist(char **teams, size_t max, const char *name)
{
  size_t	i;

  if (strcmp("GRAPHIC", name) == 0)
    return (true);
  i = 0;
  while (i < max)
    {
      if (strcmp(name, teams[i]) == 0)
	return (true);
      ++i;
    }
  return (false);
}

int 		fill_teams(t_params *params,
			      const char **tab,
			      size_t *index,
			      size_t nb)
{
  size_t 	count;
  size_t 	i;

  count = 0;
  i = 0;
  while (i++ < nb)
    {
      if (!name_already_exist(params->teams, count, tab[(*index)]))
	if (!(params->teams[count++] = strdup(tab[(*index)])))
	  {
	    perror("Erreur strdup");
	    return (1);
	  }
      ++(*index);
    }
  params->nb_teams = count;
  return (0);
}

int		name_param(int argc,
			      const char **tab,
			      t_params *params,
			      size_t *index)
{
  size_t	nb;

  if ((nb = nb_param_names(argc, tab, ++(*index))) < 2)
    return (1);
  if (params->teams[0])
    free(params->teams[0]);
  if (params->teams[1])
    free(params->teams[1]);
  if (!(params->teams = realloc(params->teams, (nb + 1) * sizeof(char*))))
    {
      perror("Erreur realloc");
      return (1);
    }
  if (fill_teams(params, tab, index, nb) == 1)
    return (1);
  if (params->nb_teams < 2)
    {
      fprintf(stderr, "Add more teams\n");
      return (1);
    }
  --(*index);
  return (0);
}