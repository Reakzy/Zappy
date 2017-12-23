/*
** client.h for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/osborn_s/Tek_2/PSU/PSU_2016_zappy
**
** Made by Samuel Osborne
** Login   <samuel.osborne@epitech.eu>
**
** Started on  Tue Jun 13 07:49:53 2017 Samuel Osborne
** Last update Tue Jun 13 07:50:33 2017 Samuel Osborne
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include <stdbool.h>
# include <netdb.h>
# include "queue.h"
# include "zappy.h"

typedef struct 		s_ai_brain
{
  int 			choice_ko;
  int 			choice_ok;
  int 			previous_act;
  int 			stop;
  t_queue		*broadcast_msg;
}			t_ai_brain;

typedef struct 		 s_ai
{
  int 			level;
  int 			nb_player_incant;
  int 			objects[MAXOBJECTTYPE];
  int 			server_fd;
  int 			nbr_teammates;
  bool			connected;
  char 			*msg_received;
  t_ai_brain		*brain;
  bool			incant;
}			t_ai;

typedef struct		s_cargs
{
  int 			port;
  char 			*team_name;
  char 			*machine_name;
}			t_cargs;

void			take_object(int rock, t_queue *write_queue);
void			choose_obj_to_pick(int i, t_ai *client, int *level,
			       t_queue *write_queue);
void			check_pickup(int pick_up, t_ai *client, t_queue *write_queue);
void			pickup_whats_needed(int *level,
				char **under_player,
				t_ai *client,
				t_queue *write_queue);
int 			check_to_move(t_ai *client, t_queue *write_queue);
int 			check_stone_oncase(t_ai *client, t_queue *write_queue);
void			drop_stones(t_ai *client, t_queue *write_queue);
int 			pick_all_on_floor(t_queue *write_queue, t_ai *client);
void			fill_under_player(char **under_player, char *msg);
int 			*fill_array_on_lvl(int level);
void			free_tab(char **cmd);
void			free_tab_len(char **cmd, int len);
char			*my_epurstr(char *str);
bool			correct_level(char **tab, t_ai *client);
void			level_one(int *stone);
void			level_two(int *stone);
void			level_three(int *stone);
void			level_four(int *stone);
void			level_five(int *stone);
void			level_six(int *stone);
void			level_seven(int *stone);
void			move_to_broadcast(t_queue *write_queue, int direction);
int 			get_direction(char **msg);
int 			move_c_diagonal_b_left(t_queue *write_queue);
int 			move_c_behind(t_queue *write_queue);
int 			move_c_diagonal_b_right(t_queue *write_queue);
int 			move_c_right(t_queue *write_queue);
int 			move_c_diagonal_f_right(t_queue *write_queue);
char 			**create_string_table(int width, int height);
char    		*concat_int(char *a, int b);
char    		*concat_strings(char *a, char *b);
int 			write_team(t_ai *client, t_cargs *args);
bool 			welcome_read(t_ai *client);
int			reset_tv_and_init_fd(struct timeval *tv,
						fd_set *fd_read,
						fd_set *fd_write,
						t_ai *client);
int 			welcome_manange_fd(fd_set *fd_read,
					      fd_set *fd_write,
					      t_ai *client,
					      t_cargs *args);
int 			write_on_server(t_ai *client,
					   fd_set *fd_write,
					   t_queue *write_queue);
int 			read_on_server(t_ai *client,
					  fd_set *fd_read,
					  t_queue *read_queue);
int 			read_socket_queue(t_ai *client, t_queue *queue);
void			help();
int 			write_socket_string(int server_fd, char *str);
int 			port_arg(int ac, char **av,
				    t_cargs *args, int index);
int 			team_name_arg(int ac, char **av,
					 t_cargs *args, int index);
int 			machine_name_arg(int ac, char **av,
					    t_cargs *args, int index);
int 			check_args(int ac, char **av, t_cargs *args);
int			client_loop(t_cargs *args);
int			try_connection(int connected_fd,
					  struct sockaddr_in s_in);
int 			count_char(char *src, char obj);
void			fill_string_array(char *str, char **fill, char sep);
void			init_file_descriptors(fd_set *fd_read,
						  fd_set *fd_write,
						  int serverFd);
int 			connect_to_server(char *hostname, int port);
void			brain_ai(t_ai *client, t_queue *write_queue,
				     t_queue *read_queue);
void 			enough_food(t_ai *client, t_queue *write_queue);
void 			look(t_ai *client, t_queue *write_queue);
void 			parse_look(t_ai *client, t_queue *write_queue);
void 			broadcast_ai(t_ai *client, t_queue *write_queue);
void 			broadcast_ally(t_ai *client, t_queue *write_queue);
void 			turn_right(t_ai *client, t_queue *write_queue);
void 			turn_left(t_ai *client, t_queue *write_queue);
void 			on_case(t_ai *client, t_queue *write_queue);
void 			check_incant(t_ai *client, t_queue *write_queue);
void 			incant(t_ai *client, t_queue *write_queue);
void 			inventory(t_ai *client, t_queue *write_queue);
void 			parse_inventory(t_ai *client, t_queue *write_queue);
void 			forward(t_ai *client, t_queue *write_queue);
void 			reproduction(t_ai *client, t_queue *write_queue);
void    		init_brain_and_client(t_ai *client);
int 			start_select_loop(t_ai *client, t_cargs *args);
char 			**parse_receive(t_ai *client);
int 			number_items(char *str, int items);
void			check_level_up(t_ai *client, t_queue *write_queue);
int 			players_needed(int team, t_ai *client);
int			need_player(t_ai *client);
void			move_to_stone(int cases, t_ai *client, t_queue *write_queue);
void			random_moves(t_queue *write_queue);
bool			compare_to_incant(t_ai *client);
void			get_food(t_ai *client, t_queue *write_queue);
void			parse_map(t_ai *client, t_queue *write_queue);
int 			check_broadcast(t_ai *client);
#endif /* CLIENT_H_ */