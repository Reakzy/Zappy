##
## Makefile for makefile in /home/weryp/rendu/zappy_gui
## 
## Made by Wéry
## Login   <weryp@epitech.net>
## 
## Started on  Mon Jun 19 14:11:34 2017 Wéry
## Last update Sun Jul  2 23:05:11 2017 Wéry
##

NAME		=	zappy_gui

CC		=	g++

RM		=	rm -f

CXXFLAGS	=	-Iincludes -isystem./lib/include
CXXFLAGS 	+= 	-W -Wall -Wextra -std=c++11
CXXFLAGS	+=	-O3

LDFLAGS 	= 	-L./lib
LDFLAGS		+=	-lIrrlicht ./lib/libIrrKlang.so -lX11 -lXxf86vm -lGL

SRC		= 	sources/main.cpp		\
			sources/GraphicMonitor.cpp	\
			sources/InterpretProtocol.cpp	\
			sources/ActionsManager.cpp	\
			sources/ExecuteActions.cpp	\
			sources/MeshLoader.cpp		\
			sources/ParserJson.cpp		\
			sources/Socket.cpp		\
			sources/NodeManipulator.cpp	\
			sources/Players.cpp		\
			sources/SoundLoader.cpp		\
			sources/TimeUnit.cpp		\
			sources/VolumeLight.cpp		\
			sources/Gate.cpp		\
			sources/EventReceiver.cpp	\
			sources/TextPanel.cpp		\

OBJ		=	$(SRC:.cpp=.o)

$(NAME)		:	$(OBJ)
			$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

all		:	$(NAME)

clean		:
			$(RM) $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
