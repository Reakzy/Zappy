/*
** server.h for PSU_2016_zappy in /home/villen_l/rendu/PSU_2016_zappy/server.h
**
** Made by Lucas Villeneuve
** Login   <lucas.villeneuve@epitech.eu>
**
** Started on  Fri Jun 30 16:37:41 2017 Lucas Villeneuve
** Last update Fri Jun 30 16:37:41 2017 Lucas Villeneuve
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include "zappy.h"
# include "queue.h"
# include "list.h"

# define MIN_WIDTH 10
# define MIN_HEIGHT 10
# define MAX_WIDTH 50
# define MAX_HEIGHT 50
# define MAX_LEVEL 8
# define TICKS_SPAWN_ROCKS 30

typedef struct	s_params
{
  uint16_t 	port;
  size_t 	width;
  size_t 	height;
  size_t 	nb_teams;
  char 		**teams;
  size_t 	clientsNb;
  size_t 	freq;
  int	 	index_max;
}		t_params;

typedef struct	s_team
{
  char 		*name;
  size_t 	nbClientsLeft;
}		t_team;

typedef struct	s_egg
{
  size_t	id;
  uint16_t 	hatch_timer;
  bool		hatched;
  t_team	*team;
  t_pos		pos;
  int 		player;
}		t_egg;

typedef struct		s_tile
{
  int			objects[MAXOBJECTTYPE];
}			t_tile;

typedef struct		s_client
{
  int 			fd;
  t_queue		*entry_queue;
  t_queue 		*exec_queue;
  t_queue		*exit_queue;
  bool			logged;
  bool			born_from_egg;
  bool			incanting;
  t_team		*team;
  t_pos			pos;
  enum e_directions	dir;
  uint16_t		cooldown;
  uint16_t 		level;
  size_t		objects[MAXOBJECTTYPE];
}			t_client;

typedef struct		s_writing_gui
{
  bool			writing;
  bool			map;
  bool			eggs;
  bool			teams;
  bool			players;
  t_pos			i_map;
  size_t		i_eggs;
  size_t		i_teams;
  size_t		i_players;
}			t_writing_gui;

typedef struct	s_server
{
  int 		fd;
  int		fd_log;
  short		port;
  size_t	x;
  size_t 	y;
  size_t	freq;
  t_tile	**map;
  t_list	*teams;
  t_list	*clients;
  t_list	*eggs;
  t_client	*gui;
  t_writing_gui	w_gui;
  size_t	id_eggs;
  uint16_t	rocks;
  bool		end;
}		t_server;

int		zappy(t_params*);
int		read_client(t_client*);
int		add_server(t_server *server);
int		init_server(t_server*, t_params*);
int		set_fds(t_server*, fd_set*, fd_set*);
int		init_client(t_client*, int, t_server*);
int		port_param(int, const char**, t_params*, size_t*);
int		name_param(int, const char**, t_params*, size_t*);
int		freq_param(int, const char**, t_params*, size_t*);
int		width_param(int, const char**, t_params*, size_t*);
int		height_param(int, const char**, t_params*, size_t*);
int		clients_param(int, const char**, t_params*, size_t*);
void		free_map(t_server*);
void		init_params(t_params*);
void		free_params(t_params*);
void		writing_eggs(t_server*);
void		print_log_map(t_server*);
void		close_log_file(t_server*);
void		writing_players(t_server*);
void		place_rocks_map(t_server*);
void		create_log_file(t_server*);
void		set_tile(t_server*, t_pos*);
void		write_egg(t_server*, t_egg*);
void		init_server_w_gui(t_server*);
void		writing_infos_gui(t_server*);
void		read_server(t_server *server);
void		log_gui(t_server*, t_client*);
void		move_up(t_server*, t_client*);
void		timer_eggs(t_server*, t_list*);
void		cooldown_on_clients(t_server*);
void		move_left(t_server*, t_client*);
void		move_down(t_server*, t_client*);
void		move_right(t_server*, t_client*);
void		write_player(t_server*, t_client*);
void		fork_cooldown(t_server*, t_client*);
void		write_on_log_file(t_server*, char*);
void		send_gui_eject(t_server*, t_client*);
void		look_tile(t_server*, t_client*, t_pos*);
void		inventory_cooldown(t_server*, t_client*);
void		incantation_ko(t_server*, t_client*, bool);
void		incantation_cooldown(t_server*, t_client*);
void		connect_nbr_cooldown(t_server*, t_client*);
void		insert_uint_queue(t_queue*, char*, size_t);
void		set_cmd(t_server*, t_client*, const char**);
void		look_up(t_server *server, t_client *client);
void		look_cmd(t_server*, t_client*, const char**);
void		left_cmd(t_server*, t_client*, const char**);
void		fork_cmd(t_server*, t_client*, const char**);
void		take_cmd(t_server*, t_client*, const char**);
void		right_cmd(t_server*, t_client*, const char**);
void		eject_cmd(t_server*, t_client*, const char**);
void		send_elevation_underway(t_server*, t_client*);
void		insert_uint_queue_nl(t_queue*, char*, size_t);
void		check_if_fds_set(t_server*, fd_set*, fd_set*);
void		look_left(t_server *server, t_client *client);
void		look_down(t_server *server, t_client *client);
void		look_right(t_server *server, t_client *client);
void		write_on_log_file_len(t_server*, char*, size_t);
void		send_current_level(t_server*, t_client*, char*);
void		forward_cmd(t_server*, t_client*, const char**);
void		log_client(t_server*, t_client*, char*, t_team*);
void		broadcast_cmd(t_server*, t_client*, const char**);
void		inventory_cmd(t_server*, t_client*, const char**);
void		interpret_cmd(t_server*, t_client*, const char**);
void		increase_level_client(t_server*, t_client*, bool);
void		level_two_incantation(t_server*, t_client*, bool);
void		level_six_incantation(t_server*, t_client*, bool);
void		level_four_incantation(t_server*, t_client*, bool);
void		level_five_incantation(t_server*, t_client*, bool);
void		level_three_incantation(t_server*, t_client*, bool);
void		level_seven_incantation(t_server*, t_client*, bool);
void		level_eight_incantation(t_server*, t_client*, bool);
void		incantation_cmd(t_server*, t_client*, const char**);
void		connect_nbr_cmd(t_server*, t_client*, const char**);
void		eject_other_players(t_server*, t_client*, t_client*);
void		spawn_client_on_egg(t_server*, t_client*, const char*);
void		interpret_cmd_cooldown(t_server*, t_client*, const char**);
const char	**my_str_to_wordtab(char *str, const char *delimiters);
bool		write_client(t_server*, t_client*);
bool		check_if_client_dead(t_client*);
bool		exec_client(t_server*, t_client*);
bool		write_tile(t_server*, char*, int, int);
t_tile		**set_map(t_server*, t_params*);
t_item		*delete_node_client(t_server*, t_item*);
size_t 		broadcast_tile(t_server*, t_client*, t_client*);
void            write_cmd_broadcast(t_client *client, const char **cmd);
size_t		nb_players_on_tile(const t_pos*, const t_list*);
size_t		nb_players_on_tile_with_lvl(const t_pos*,
						  const t_list*,
						  size_t);
size_t 		init_ptrfnc_params(int (**)(int, const char**,
						  t_params*, size_t*),
					 t_params*);

#endif /* !SERVER_H_ */