/*
** InterpretProtocol.cpp for zappy_gui in /home/werp/rendu/zappy_gui/InterpretProtocol.cpp
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Mon Jun 12 16:47:49 2017 Paul Wéry
** Last update Mon Jun 12 16:47:49 2017 Paul Wéry
*/

# include "InterpretProtocol.hh"

InterpretProtocol::InterpretProtocol(ActionsManager &_actionsManager, ExecuteActions &_executeActions)
 : actionsManager(_actionsManager), executeActions(_executeActions)
{
  commands["msz"] = &InterpretProtocol::setSizeMap;
  commands["bct"] = &InterpretProtocol::setTile;
  commands["tna"] = &InterpretProtocol::newTeam;
  commands["pnw"] = &InterpretProtocol::newPlayer;
  commands["pin"] = &InterpretProtocol::setPlayerInventory;
  commands["ppo"] = &InterpretProtocol::setPosPlayer;
  commands["plv"] = &InterpretProtocol::setLevelPlayer;
  commands["pex"] = &InterpretProtocol::playerExpels;
  commands["pbc"] = &InterpretProtocol::playerBroadcasts;
  commands["pic"] = &InterpretProtocol::playerCastsSpell;
  commands["pie"] = &InterpretProtocol::endOfSpell;
  commands["pdr"] = &InterpretProtocol::playerThrowsResource;
  commands["pgt"] = &InterpretProtocol::playerPicksUpResource;
  commands["pdi"] = &InterpretProtocol::playerDead;
  commands["pfk"] = &InterpretProtocol::playerLays;
  commands["enw"] = &InterpretProtocol::playerLaysEgg;
  commands["eht"] = &InterpretProtocol::eggHatch;
  commands["ebo"] = &InterpretProtocol::playerJoinEgg;
  commands["edi"] = &InterpretProtocol::eggDead;
  commands["sgt"] = &InterpretProtocol::setTimeUnit;
  commands["seg"] = &InterpretProtocol::endGame;
}

InterpretProtocol::~InterpretProtocol()
{

}

std::vector<std::string> InterpretProtocol::splitCmd(const std::string &command,
						     const std::string &splitChars) const
{
  std::vector<std::string>	list;
  std::string			string;

  for (unsigned int index = 0; index < command.size(); index++)
    {
      string = "";
      while (index < command.size() && charInString(command.at(index), splitChars))
	index++;
      while (index < command.size() && !charInString(command.at(index), splitChars))
	string += command.at(index++);
      if (string != "")
	list.push_back(string);
    }
  return (list);
}

bool InterpretProtocol::charInString(char c, const std::string &string) const
{
  for (unsigned int index = 0; index < string.size(); index++)
    {
      if (c == string.at(index))
	return (true);
    }
  return (false);
}

bool InterpretProtocol::interpretCommand(const std::string &cmdLine) const
{
  std::vector<std::string>	cmds = splitCmd(cmdLine, " \t\n\r");

  if (cmds.size() == 0 || commands.find(cmds.front()) == commands.end())
    return (false);
  return ((this->*commands.at(cmds.front()))(cmds));
}

bool InterpretProtocol::setSizeMap(const std::vector<std::string> &cmds) const
{
  if (cmds.size() != 3)
    return (false);
  actionsManager.setSizeMap(static_cast<unsigned int>(std::atoi(cmds.at(1).c_str())),
			    static_cast<unsigned int>(std::atoi(cmds.at(2).c_str())));
  executeActions.setSizeMap();
  return (true);
}

bool InterpretProtocol::setTile(const std::vector<std::string> &cmds) const
{
  unsigned int			x;
  unsigned int			y;
  std::vector<unsigned int>	content;

  if (cmds.size() != 10)
    return (false);
  x = static_cast<unsigned int>(std::atoi(cmds.at(1).c_str()));
  y = static_cast<unsigned int>(std::atoi(cmds.at(2).c_str()));
  for (unsigned int i = 3; i < cmds.size(); i++)
    content.push_back(static_cast<unsigned int>(std::atoi(cmds.at(i).c_str())));
  actionsManager.setTile(x, y, content);
  executeActions.setTile(x, y);
  return (true);
}

bool InterpretProtocol::newTeam(const std::vector<std::string> &cmds) const
{
  if (cmds.size() != 2)
    return (false);
  actionsManager.newTeam(cmds.at(1));
  executeActions.newTeam(cmds.at(1));
  return (true);
}

bool InterpretProtocol::newPlayer(const std::vector<std::string> &cmds) const
{
  std::vector<std::string>	info;

  if (cmds.size() != 7)
    return (false);
  for (unsigned int i = 1; i < cmds.size(); i++)
    info.push_back(cmds.at(i));
  actionsManager.newPlayer(info);
  executeActions.newPlayer(cmds.at(1), cmds.back());
  return (true);
}

bool InterpretProtocol::setPlayerInventory(const std::vector<std::string> &cmds) const
{
  std::vector<unsigned int>	content;

  if (cmds.size() != 11)
    return (false);
  for (unsigned int i = 4; i < cmds.size(); i++)
    content.push_back(static_cast<unsigned int>(std::atoi(cmds.at(i).c_str())));
  actionsManager.setPlayerInventory(cmds.at(1), content);
  return (true);
}

bool InterpretProtocol::setPosPlayer(const std::vector<std::string> &cmds) const
{
  std::vector<std::string>	info;

  if (cmds.size() != 5)
    return (false);
  for (unsigned int i = 1; i < cmds.size(); i++)
    info.push_back(cmds.at(i));
  actionsManager.setPosPlayer(info);
  executeActions.setPosPlayer(cmds.at(1));
  return (true);
}

bool InterpretProtocol::setLevelPlayer(const std::vector<std::string> &cmds) const
{
  if (cmds.size() != 3)
    return (false);
  actionsManager.setLevelPlayer(cmds.at(1), static_cast<unsigned int>(std::atoi(cmds.at(2).c_str())));
  executeActions.setLevelPlayer(cmds.at(1));
  return (true);
}

bool InterpretProtocol::playerExpels(const std::vector<std::string> &cmds) const
{
  if (cmds.size() != 2)
    return (false);
  executeActions.playerExpels(cmds.at(1));
  return (true);
}

bool InterpretProtocol::playerBroadcasts(const std::vector<std::string> &cmds) const
{
  std::string	message;

  if (cmds.size() < 2)
    return (false);
  for (unsigned int index = 2; index < cmds.size(); index++)
    message += cmds.at(index) + " ";
  executeActions.playerBroadcasts(cmds.at(1), message);
  return (true);
}

bool InterpretProtocol::playerCastsSpell(const std::vector<std::string> &cmds) const
{
  if (cmds.size() < 5)
    return (false);
  executeActions.playerCastsSpell(cmds.at(1) + " " + cmds.at(2));
  return (true);
}

bool InterpretProtocol::endOfSpell(const std::vector<std::string> &cmds) const
{
  if (cmds.size() != 4)
    return (false);
  executeActions.endOfSpell(cmds.at(1) + " " + cmds.at(2),
			    static_cast<bool>(std::atoi(cmds.at(3).c_str())));
  return (true);
}

bool InterpretProtocol::playerThrowsResource(const std::vector<std::string> &cmds) const
{
  if (cmds.size() != 3)
    return (false);
  actionsManager.playerThrowsResource(cmds.at(1), static_cast<unsigned int>(std::atoi(cmds.at(2).c_str())));
  executeActions.playerThrowsResource();
  return (true);
}

bool InterpretProtocol::playerPicksUpResource(const std::vector<std::string> &cmds) const
{
  if (cmds.size() != 3)
    return (false);
  actionsManager.playerPicksUpResource(cmds.at(1), static_cast<unsigned int>(std::atoi(cmds.at(2).c_str())));
  return (true);
}

bool InterpretProtocol::playerDead(const std::vector<std::string> &cmds) const
{
  if (cmds.size() != 2)
    return (false);
  executeActions.playerDead(cmds.at(1));
  actionsManager.playerDead(cmds.at(1));
  return (true);
}

bool InterpretProtocol::playerLays(const std::vector<std::string> &cmds) const
{
  if (cmds.size() != 2)
    return (false);
  executeActions.playerLays(cmds.at(1));
  return (true);
}

bool InterpretProtocol::playerLaysEgg(const std::vector<std::string> &cmds) const
{
  if (cmds.size() != 5)
    return (false);
  actionsManager.playerLaysEgg(static_cast<unsigned int>(std::atoi(cmds.at(3).c_str())),
			       static_cast<unsigned int>(std::atoi(cmds.at(4).c_str())), cmds.at(1), cmds.at(2));
  executeActions.playerLaysEgg(cmds.at(2), cmds.at(1), cmds.at(3) + " " + cmds.at(4));
  return (true);
}

bool InterpretProtocol::eggHatch(const std::vector<std::string> &cmds) const
{
  return (cmds.size() != 2);
}

bool InterpretProtocol::playerJoinEgg(const std::vector<std::string> &cmds) const
{
  if (cmds.size() != 2)
    return (false);
  actionsManager.playerJoinEgg(cmds.at(1));
  executeActions.playerJoinEgg(cmds.at(1));
  return (true);
}

bool InterpretProtocol::eggDead(const std::vector<std::string> &cmds) const
{
  if (cmds.size() != 2)
    return (false);
  actionsManager.eggDead(cmds.at(1));
  executeActions.eggDead(cmds.at(1));
  return (true);
}

bool InterpretProtocol::setTimeUnit(const std::vector<std::string> &cmds) const
{
  if (cmds.size() != 2)
    return (false);
  executeActions.changeTimeUnit(static_cast<unsigned int>(std::atoi(cmds.at(1).c_str())));
  return (true);
}

bool InterpretProtocol::endGame(const std::vector<std::string> &cmds) const
{
  if (cmds.size() != 2)
    return (false);
  executeActions.endGame(cmds.at(1));
  return (true);
}
