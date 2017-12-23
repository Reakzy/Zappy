/*
** string_functions.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
** 
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
** 
** Started on  Tue Jun 13 13:59:54 2017 Samuel Osborne
** Last update Tue Jun 13 14:00:01 2017 Samuel Osborne
*/

#include <stdlib.h>
#include <string.h>
#include "ai.h"

char 	**create_string_table(int width, int height)
{
  char 	**tab;
  int 	i;

  i = 0;
  if ((tab = malloc(sizeof(char *) * (height + 1))) == NULL)
    return (NULL);
  while (i < height)
    {
      if ((tab[i] = malloc(sizeof(char) * width)) == NULL)
	return (NULL);
      memset(tab[i], 0, (size_t)width);
      i++;
    }
  tab[i] = NULL;
  return (tab);
}

int 	count_char(char *src, char obj)
{
  int 	i;
  int 	cnt;

  i = 0;
  cnt = 0;
  while (src[i])
    {
      if (src[i] == obj)
	cnt++;
      i++;
    }
  return (cnt);
}

int 		number_items(char *str, int i)
{
  char	*food;
  int 	a;
  int 	nb_food;

  a = 0;
  if ((food = malloc(strlen(str) + 1)) == NULL)
    return (-1);
  memset(food, 0, strlen(str) + 1);
  while (str[i])
    {
      food[a] = str[i];
      a++;
      i++;
    }
  nb_food = atoi(food);
  free (food);
  return (nb_food);
}

void		fill_string_array(char *str, char **fill, char sep)
{
  int 		i;
  int 		l;
  int 		k;
  int 		j;

  i = -1;
  k = 0;
  j = 0;
  while (str[++i] != '\0' && fill[k] != NULL)
    {
      l = 0;
      while (str[j] != '\0' && str[j] != sep)
	{
	  fill[k][l] = str[j];
	  j++;
	  l++;
	}
      fill[k] = my_epurstr(fill[k]);
      if (str[j] != 0)
	j++;
      k++;
    }
}

char	**parse_receive(t_ai *client)
{
  int i;
  int j;
  int k;
  int l;
  int count;
  char **vision;

  i = 0;
  k = 0;
  j = 1;
  if ((count = count_char(client->msg_received, ',')) == -1)
    return (NULL);
  vision = create_string_table((int)strlen(client->msg_received), count + 1);
  while (client->msg_received[++i] != '\0' && k <= count)
    {
      l = 0;
      while (client->msg_received[j] != ',' &&
	     client->msg_received[j] != '\0' && client->msg_received[j] != ']')
	vision[k][l++] = client->msg_received[j++];
      vision[k] = my_epurstr(vision[k]);
      j++;
      k++;
    }
  return (vision);
}