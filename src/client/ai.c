/*
** client.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
**
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
**
** Started on  Tue Jun 13 07:43:30 2017 Samuel Osborne
** Last update Sun Jul  2 18:31:49 2017 Samuel Osborne
*/

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "ai.h"

void		init_client_structure(t_cargs *args)
{
  args->port = 4242;
  args->machine_name = strdup("localhost");
  args->team_name = NULL;
}

int		main(int ac, char **av)
{
  t_cargs	args;

  srand((unsigned int)time(NULL));
  if (ac == 2 && strcmp(av[1], "-help") == 0)
    {
      help();
      return (84);
    }
  init_client_structure(&args);
  if ((check_args(ac, av, &args)) == 1)
    {
      help();
      free(args.machine_name);
      free(args.team_name);
      return (84);
    }
  if ((client_loop(&args)) == 1)
    {
      free(args.machine_name);
      free(args.team_name);
      return (84);
    }
  free(args.team_name);
  free(args.machine_name);
  return (0);
}