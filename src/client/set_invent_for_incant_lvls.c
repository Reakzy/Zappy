/*
** set_invent_for_incant_lvls.c for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
** 
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
** 
** Started on  Sat Jun 24 12:37:21 2017 Samuel Osborne
** Last update Sat Jun 24 12:37:21 2017 Samuel Osborne
*/

#include "zappy.h"

void	level_one(int *stone)
{
  stone[LINEMATE] = 1;
  stone[DERAUMERE] = 0;
  stone[SIBUR] = 0;
  stone[MENDIANE] = 0;
  stone[PHIRAS] = 0;
  stone[THYSTAME] = 0;
}

void	level_two(int *stone)
{
  stone[LINEMATE] = 1;
  stone[DERAUMERE] = 1;
  stone[SIBUR] = 1;
  stone[MENDIANE] = 0;
  stone[PHIRAS] = 0;
  stone[THYSTAME] = 0;
}

void	level_three(int *stone)
{
  stone[LINEMATE] = 2;
  stone[DERAUMERE] = 0;
  stone[SIBUR] = 1;
  stone[MENDIANE] = 0;
  stone[PHIRAS] = 2;
  stone[THYSTAME] = 0;
}

void	level_four(int *stone)
{
  stone[LINEMATE] = 1;
  stone[DERAUMERE] = 1;
  stone[SIBUR] = 2;
  stone[MENDIANE] = 0;
  stone[PHIRAS] = 1;
  stone[THYSTAME] = 0;
}

void	level_five(int *stone)
{
  stone[LINEMATE] = 1;
  stone[DERAUMERE] = 2;
  stone[SIBUR] = 1;
  stone[MENDIANE] = 3;
  stone[PHIRAS] = 0;
  stone[THYSTAME] = 0;
}
