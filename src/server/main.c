/*
** main.c for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/main.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Fri Jun 09 14:08:25 2017 Lucas Villeneuve
** Last update Fri Jun 09 14:08:25 2017 Lucas Villeneuve
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

void	print_help(char *bin)
{
  printf("USAGE: %s -p port -x width -y height"
	  " -n name1 name2 ... -c clientsNb -f freq\n"
	  "\tport\tis the port number\n"
	  "\twidth\tis the width of the world\n"
	  "\theight\tis the height of the world\n"
	  "\tnameX\tis the name of the team X\n"
	  "\tclientsNb\tis the number of authorized clients per team\n"
	  "\tfreq\tis the reciprocal of time unit for execution of actions\n",
	 bin);
}


int 		process_params(int nb, const char **tab, t_params *params)
{
  size_t	j;
  int	 	k;
  char 		cmd[6][3];
  int		(*ptrfnc[6])(int, const char**, t_params*, size_t*);

  strcpy(cmd[0], "-p");
  strcpy(cmd[1], "-x");
  strcpy(cmd[2], "-y");
  strcpy(cmd[3], "-n");
  strcpy(cmd[4], "-c");
  strcpy(cmd[5], "-f");
  params->index_max = (int)init_ptrfnc_params(ptrfnc, params);
  j = 0;
  while	(++j < (size_t)nb)
    {
      k = -1;
      while (++k < params->index_max)
	if (strcmp(tab[j], cmd[k]) == 0)
	  {
	    if (ptrfnc[k](nb, tab, params, &j) == 1)
	      return (1);
	    k = params->index_max;
	  }
    }
  return (0);
}

void		print_params(t_params *params)
{
  size_t	i;

  printf("Port : %hd\nFreq : %lu\nWidth : %lu \nHeight : %lu\n"
	  "%lu teams with each %lu clients :\n",
	 params->port, params->freq, params->width, params->height,
	 params->nb_teams, params->clientsNb);
  i = 0;
  while (i < params->nb_teams)
    {
      printf("  Team %lu with name : '%s'\n", i + 1, params->teams[i]);
      ++i;
    }
}

int		main(int argc, char **argv)
{
  t_params	params;
  int 		ret;

  if (argc >= 2 && (strcmp(argv[1], "--help") == 0 ||
		    strcmp(argv[1], "-h") == 0))
    {
      print_help(argv[0]);
      return (0);
    }
  else if (process_params(argc, (const char**)argv, &params) != 0)
    {
      print_help(argv[0]);
      free_params(&params);
      return (1);
    }
  print_params(&params);
  ret = zappy(&params);
  free_params(&params);
  return (ret);
}