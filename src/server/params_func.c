/*
** params_func.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/params_func.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Fri Jun 09 16:32:06 2017 Lucas Villeneuve
** Last update Fri Jun 09 16:32:06 2017 Lucas Villeneuve
*/

#include <stdio.h>
#include "server.h"

int	port_param(int nb, const char **tab, t_params *params, size_t *index)
{
  if (++(*index) >= (size_t)nb)
    return (1);
  params->port = (uint16_t)atoi(tab[*index]);
  return (0);
}

int 	width_param(int nb, const char **tab, t_params *params, size_t *index)
{
  int 	tmp;

  if (++(*index) >= (size_t)nb)
    return (1);
  if ((tmp = atoi(tab[*index])) < MIN_WIDTH || tmp > MAX_WIDTH)
    {
      fprintf(stderr, "Width is bad, try values between %d and %d \n",
	      MIN_WIDTH, MAX_WIDTH);
      return (1);
    }
  params->width = (size_t)tmp;
  return (0);
}

int 	height_param(int nb, const char **tab, t_params *params, size_t *index)
{
  int 	tmp;

  if (++(*index) >= (size_t)nb)
    return (1);
  if ((tmp = atoi(tab[*index])) < MIN_HEIGHT || tmp > MAX_HEIGHT)
    {
      fprintf(stderr, "Height is bad, try values between %d and %d \n",
	      MIN_HEIGHT, MAX_HEIGHT);
      return (1);
    }
  params->height = (size_t)tmp;
  return (0);
}

int	clients_param(int nb, const char **tab, t_params *params, size_t *index)
{
  int 	tmp;

  if (++(*index) >= (size_t)nb)
    return (1);
  if ((tmp = atoi(tab[*index])) <= 0 || tmp > 6)
    {
      fprintf(stderr, "Nb clients must be between 1 and 6\n");
      return (1);
    }
  params->clientsNb = (size_t)tmp;
  return (0);
}

int 	freq_param(int nb, const char **tab, t_params *params, size_t *index)
{
  int	tmp;

  if (++(*index) >= (size_t)nb)
    return (1);
  if ((tmp = atoi(tab[*index])) <= 0 || tmp > 1000)
    {
      fprintf(stderr, "Frequency must be between 0 and 1000\n");
      return (1);
    }
  params->freq = (size_t)tmp;
  return (0);
}