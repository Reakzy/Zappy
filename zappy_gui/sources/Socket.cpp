/*
** Socket.cpp for zappy_gui in /home/werp/rendu/zappy_gui/Socket.cpp
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Fri Jun 23 10:36:52 2017 Paul Wéry
** Last update Fri Jun 23 10:36:52 2017 Paul Wéry
*/

# include "Socket.hh"

Socket::Socket()
{
  this->fd = 0;
  this->readSocket();
}

Socket::~Socket()
{

}

bool Socket::openConnection(const std::string &ip, const std::string &port)
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  socklen_t		s_size;

  if ((pe = this->getProtoByName("TCP")) == nullptr ||
   !this->createSocket(AF_INET, SOCK_STREAM, pe->p_proto))
    return (false);
  s_in.sin_family = AF_INET;
  s_in.sin_port = this->hostToNetwork(static_cast<uint16_t>(std::atoi(port.c_str())));
  s_in.sin_addr.s_addr = this->inetAddr(ip.c_str());
  s_size = sizeof(s_in);
  return (this->tryConnect(this->fd, &s_in, s_size));
}

bool Socket::createSocket(int domain, int type, int protocol)
{
  return ((this->fd = socket(domain, type, protocol)) != -1);
}

struct protoent *Socket::getProtoByName(const std::string &name) const
{
  return (getprotobyname(name.c_str()));
}

uint16_t Socket::hostToNetwork(uint16_t hostshort) const
{
  return (htons(hostshort));
}

in_addr_t Socket::inetAddr(const std::string &cp) const
{
  return (inet_addr(cp.c_str()));
}

bool Socket::tryConnect(int sockfd, struct sockaddr_in *servAddr,
			socklen_t addrlen) const
{
  return (connect(sockfd, reinterpret_cast<const struct sockaddr*>(servAddr), addrlen) == 0);
}

bool Socket::monitorFds()
{
  FD_ZERO(&this->readfds);
  FD_ZERO(&this->writefds);
  FD_ZERO(&this->exceptfds);
  FD_SET(this->fd, &this->readfds);
  FD_SET(this->fd, &this->writefds);
  FD_SET(this->fd, &this->exceptfds);
  return (select(this->fd + 1, &this->readfds, &this->writefds,
		 &this->exceptfds, nullptr) != -1);
}
#include <iostream>
bool Socket::readSocket()
{
  this->resetBuffer();
  if (this->fd > 0 && FD_ISSET(this->fd, &this->readfds))
    {
      return (read(this->fd, const_cast<char*>(this->buffer.c_str()),
	       this->buffer.size()) != -1);
    }
  return (true);
}

bool Socket::writeSocket(const std::string &buffer)
{
  this->buffer = buffer + "\n";
  if (this->fd > 0 && FD_ISSET(this->fd, &this->writefds))
    {
      return (write(this->fd, const_cast<char*>(this->buffer.c_str()),
		    this->buffer.size()) != -1);
    }
  this->resetBuffer();
  return (FD_ISSET(this->fd, &this->writefds));
}

void Socket::resetBuffer()
{
  this->buffer = "";
  for (unsigned int index = 0; index < 1024; index++)
    this->buffer += '\0';
}

std::string Socket::pullCommand()
{
  std::string	tmp;
  unsigned int	index = 0;

  while (index < this->buffer.size() && this->buffer.at(index) != '\0')
    received.push(static_cast<char>(this->buffer.at(index++)));
  if (command.size() > 0 && command.back() == '\n')
    command = "";
  while (received.size() > 0 && received.front() != '\n')
    {
      command += received.front();
      received.pop();
    }
  if (received.size() > 0 && received.front() == '\n')
    {
      command += received.front();
      received.pop();
    }
  return (command);
}
