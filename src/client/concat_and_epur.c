/*
** concat_and_epur.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
** 
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
** 
** Started on  Sat Jun 24 13:35:31 2017 Samuel Osborne
** Last update Sat Jun 24 13:35:31 2017 Samuel Osborne
*/

#include <string.h>
#include <stdlib.h>

char	*concat_int(char *a, int b)
{
  char  *res;

  if ((res = malloc(strlen(a) + 2)) == NULL)
    return (NULL);
  memset(res, 0, strlen(a) + 2);
  strcpy(res, a);
  res[strlen(a)] = (char)(b + 48);
  free(a);
  return (res);
}

char	*concat_strings(char *a, char *b)
{
  char  *res;

  if ((res = malloc(strlen(a) + strlen(b) + 2)) == NULL)
    return (NULL);
  memset(res, 0, strlen(a) + strlen(b) + 2);
  strcpy(res, a);
  strcat(res, b);
  free(a);
  return (res);
}

char	*my_epurstr(char *str)
{
  int   i;
  int   j;
  char  *copy;

  i = 0;
  j = 0;
  if ((copy = malloc(sizeof(char) * strlen(str) + 1)) == NULL)
    return (NULL);
  while (str[i] == ' ' || str[i] == '\t')
    i = i + 1;
  while (str[i] != '\0' && str[i] != '\n')
    {
      if (str[i] != ' ' && str[i] != '\t')
	copy[j++] = str[i++];
      else if (str[i] == ' ' || str[i] == '\t')
	{
	  while (str[i] == ' ' || str[i] == '\t')
	    i = i + 1;
	  if (str[i] != '\0')
	    copy[j++] = ' ';
	}
    }
  copy[j] = 0;
  free(str);
  return (copy);
}
