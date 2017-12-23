/*
** ope_string.c for PSU_2016_myirc in /home/villen_l/rendu/PSU_2016_myirc/ope_string.c
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Tue May 30 12:46:06 2017 Lucas Villeneuve
** Last update Tue May 30 12:46:06 2017 Lucas Villeneuve
*/

#include <stdlib.h>
#include <string.h>

const char	**my_str_to_wordtab(char *str, const char *delimiters)
{
  const char **tab;
  size_t i;

  i = 0;
  if (!(tab = calloc((i + 1), sizeof(char *))))
    return (NULL);
  tab[i] = strtok(str, delimiters);
  while (tab[i++] != NULL)
    {
      tab = realloc(tab, sizeof(char *) * (i + 1));
      tab[i] = strtok(NULL, delimiters);
    }
  return (tab);
}