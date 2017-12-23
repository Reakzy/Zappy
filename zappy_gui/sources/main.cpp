//
// main.cpp for main in /home/weryp/rendu/zappy_gui/sources
//
// Made by Wéry
// Login   <weryp@epitech.net>
//
// Started on  Mon Jun 12 15:13:13 2017 Wéry
// Last update Mon Jun 12 15:13:17 2017 Wéry
//

# include <iostream>
# include "Socket.hh"
# include "GraphicMonitor.hh"

int			main(int ac, char **av)
{
  Socket		socket;
  GraphicMonitor	graphicMonitor;

  if (ac == 3)
    {
      if (graphicMonitor.connectGraphic(av[1], av[2])
	  && graphicMonitor.startDevice())
	{
	  graphicMonitor.launchGraphic();
	}
      else
	std::cout << "./gui <ip address> <port>" << std::endl;
    }
  else
    std::cout << "./gui <ip address> <port>" << std::endl;
  return (0);
}