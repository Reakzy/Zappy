/*
** Socket.hh for zappy_gui in /home/werp/rendu/zappy_gui/Socket.hh
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Fri Jun 23 10:36:52 2017 Paul Wéry
// Last update Fri Jun 23 11:27:07 2017 Wéry
*/

#ifndef ZAPPY_GUI_SOCKET_HH
#define ZAPPY_GUI_SOCKET_HH

# include <string>
# include <netdb.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <unistd.h>
# include <queue>


class Socket
{
  int			fd;
  fd_set		readfds;
  fd_set		writefds;
  fd_set		exceptfds;
  std::string		buffer;
  std::queue<char>	received;
  std::string		command;

  void			resetBuffer();
  struct protoent	*getProtoByName(const std::string &name) const;
  bool			createSocket(int domain, int type, int protocol);
  uint16_t		hostToNetwork(uint16_t hostshort) const;
  in_addr_t		inetAddr(const std::string &cp) const;
  bool			tryConnect(int sockfd, struct sockaddr_in *servAddr,
				   socklen_t addrlen) const;

 public:

  bool		openConnection(const std::string &ip, const std::string &port);
  bool		monitorFds();
  bool		readSocket();
  bool		writeSocket(const std::string &buffer);
  std::string	pullCommand();

  Socket();
  Socket(const Socket &) = delete;
  ~Socket();
  Socket	&operator=(const Socket &) = delete;
};


#endif //ZAPPY_GUI_SOCKET_HH
