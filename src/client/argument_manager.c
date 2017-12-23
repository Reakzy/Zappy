/*
** argument_manager.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
** 
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
** 
** Started on  Tue Jun 13 08:56:10 2017 Samuel Osborne
** Last update Sun Jul  2 18:34:48 2017 Samuel Osborne
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ai.h"

void	help()
{
  printf("USAGE: ./client -p port -n name -h machine\n"
	  "port is the port number\n"
	  "name is the name of the team\n"
	  "machine is the name of the machine; localhost by default\n");
}

int 		port_arg(int ac,
			    char **av,
			    t_cargs *args,
			    int index)
{
  if (index + 1 >= ac)
    return (1);
  args->port = atoi(av[index + 1]);
  return (0);
}

int 		team_name_arg(int ac,
				 char **av,
				 t_cargs *args,
				 int index)
{
  if (index + 1 >= ac)
    return (1);
  args->team_name = strdup(av[index + 1]);
  return (0);
}

int 		machine_name_arg(int ac,
				    char **av,
				    t_cargs *args,
				    int index)
{
  if (index + 1 >= ac)
    return (1);
  args->machine_name = strdup(av[index + 1]);
  return (0);
}

int 		check_args(int ac,
			      char **av,
			      t_cargs *args)
{
  int 		i;
  int 		k;
  char 		cmd[3][3] = {"-p", "-n", "-h"};
  int		(*ptrfnc[3])(int, char**, t_cargs*, int);

  i = 0;
  ptrfnc[0] = &port_arg;
  ptrfnc[1] = &team_name_arg;
  ptrfnc[2] = &machine_name_arg;
  while (i <= 2)
    {
      k = 1;
      while (k < ac)
	{
	  if (strcmp(cmd[i], av[k]) == 0)
	    if ((ptrfnc[i](ac, av, args, k)) == 1)
	      return (1);
	  k++;
	}
      i++;
    }
  return (0);
}
