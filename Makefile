
##
## Makefile for zappy in /mnt/1aa9b3b8-3e24-4ea9-9b0d-d57254b2d1b9/villen_l/rendu/PSU/PSU_2016_myirc
## 
## Made by Lucas Villeneuve
## Login   <lucas.villeneuve@epitech.eu>
## 
## Started on  Mon May 22 17:41:25 2017 Lucas Villeneuve
## Last update Sun Jul  2 21:54:10 2017 Samuel Osborne
##

NAME		=	zappy

SERVER		=	zappy_server

CLIENT		=	zappy_ai

SERVER_PATH	=	src/server/

CLIENT_PATH	=	src/client/

LIST_PATH	=	src/list/

SERVER_SRC	=	$(LIST_PATH)list.c				\
			$(LIST_PATH)list_add.c				\
			$(LIST_PATH)item.c				\
			$(LIST_PATH)ope_string.c			\
			$(SERVER_PATH)exec_client.c			\
			$(SERVER_PATH)exec_client_cooldown.c		\
			$(SERVER_PATH)cmd_cooldown.c			\
			$(SERVER_PATH)fds_server.c			\
			$(SERVER_PATH)ope_params.c			\
			$(SERVER_PATH)main.c				\
			$(SERVER_PATH)manage_server_and_client.c	\
			$(SERVER_PATH)ope_client.c			\
			$(SERVER_PATH)params_func.c			\
			$(SERVER_PATH)params_name.c			\
			$(SERVER_PATH)zappy.c				\
			$(SERVER_PATH)set_map.c				\
			$(SERVER_PATH)queue.c				\
			$(SERVER_PATH)error_queue.c			\
			$(SERVER_PATH)actions_cmd.c			\
			$(SERVER_PATH)move_cmd.c			\
			$(SERVER_PATH)informations_cmd.c		\
			$(SERVER_PATH)objects_cmd.c			\
			$(SERVER_PATH)move_directions.c			\
			$(SERVER_PATH)init_server.c			\
			$(SERVER_PATH)cooldown.c			\
			$(SERVER_PATH)look.c              		\
			$(SERVER_PATH)utils_look.c			\
			$(SERVER_PATH)first_levels_incantation.c	\
			$(SERVER_PATH)last_levels_incantation.c     	\
			$(SERVER_PATH)broadcast.c                   	\
			$(SERVER_PATH)eject.c				\
			$(SERVER_PATH)egg.c				\
			$(SERVER_PATH)log_client.c			\
			$(SERVER_PATH)infos_gui.c			\
			$(SERVER_PATH)infos_gui_players.c 		\
			$(SERVER_PATH)set_tiles.c			\
			$(SERVER_PATH)func_incantation.c		\
			$(SERVER_PATH)log_file.c

SERVER_OBJ	=	$(SERVER_SRC:.c=.o)

CLIENT_SRC	=	$(CLIENT_PATH)ai.c				\
			$(CLIENT_PATH)argument_manager.c		\
			$(CLIENT_PATH)client_loop.c			\
			$(CLIENT_PATH)check_incant.c			\
			$(CLIENT_PATH)fd_managers.c			\
			$(SERVER_PATH)queue.c				\
			$(SERVER_PATH)error_queue.c			\
			$(CLIENT_PATH)connection_manager.c		\
			$(CLIENT_PATH)ai_brain.c            		\
			$(CLIENT_PATH)command_ressources.c  		\
			$(CLIENT_PATH)command_actions.c			\
			$(CLIENT_PATH)read_write_sockets.c		\
			$(CLIENT_PATH)welcome_loop.c			\
			$(CLIENT_PATH)command_movements.c		\
			$(CLIENT_PATH)string_functions.c		\
			$(CLIENT_PATH)broadcast_parse_move.c		\
			$(CLIENT_PATH)move_for_broadcast.c		\
			$(CLIENT_PATH)set_array_for_incant_lvls.c	\
			$(CLIENT_PATH)set_invent_for_incant_lvls.c	\
			$(CLIENT_PATH)broadcast_ally.c			\
			$(CLIENT_PATH)egg_and_incant.c			\
			$(CLIENT_PATH)on_case.c				\
			$(CLIENT_PATH)concat_and_epur.c			\
			$(CLIENT_PATH)movements.c			\
			$(CLIENT_PATH)pick_all_on_floor.c		\
			$(CLIENT_PATH)check_lvl_up_and_direction.c	\
			$(CLIENT_PATH)parse_look_and_map.c		\
			$(CLIENT_PATH)case_pickup.c			\
			$(CLIENT_PATH)command_directions.c		\
			$(CLIENT_PATH)reproduction.c

CLIENT_OBJ	=	$(CLIENT_SRC:.c=.o)

CFLAGS		=	-Iinclude
CFLAGS		+=	-W -Wall -Wextra

LDFLAGS		=	-lm

CC		=	gcc

RM		=	rm -f

$(NAME):		$(SERVER) $(CLIENT)

$(SERVER):		$(SERVER_OBJ)
			$(CC) -o $(SERVER) $(SERVER_OBJ) $(LDFLAGS)

$(CLIENT):		$(CLIENT_OBJ)
			$(CC) -o $(CLIENT) $(CLIENT_OBJ)

all:			$(NAME)

clean:
			$(RM) $(SERVER_OBJ) $(CLIENT_OBJ)

fclean:			clean
			$(RM) $(SERVER) $(CLIENT)

re:			fclean all
