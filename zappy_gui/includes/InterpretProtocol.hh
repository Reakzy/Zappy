/*
** InterpretProtocol.hh for zappy_gui in /home/werp/rendu/zappy_gui/InterpretProtocol.hh
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Mon Jun 12 16:47:50 2017 Paul Wéry
** Last update Mon Jun 12 16:47:50 2017 Paul Wéry
*/

#ifndef ZAPPY_GUI_INTERPRETPROTOCOL_HH
# define ZAPPY_GUI_INTERPRETPROTOCOL_HH

# include "ActionsManager.hh"
# include "ExecuteActions.hh"

class	InterpretProtocol
{
  typedef bool (InterpretProtocol::*command)(const std::vector<std::string> &cmds) const;

  std::map<std::string, command>	commands;
  ActionsManager			&actionsManager;
  ExecuteActions			&executeActions;

  bool					charInString(char c, const std::string &string) const;
  std::vector<std::string>		splitCmd(const std::string &command, const std::string &splitChars) const;

 public:

  bool			interpretCommand(const std::string &cmdLine) const;

  bool			setSizeMap(const std::vector<std::string> &cmds) const;
  bool			setTile(const std::vector<std::string> &cmds) const;
  bool			newTeam(const std::vector<std::string> &cmds) const;
  bool			newPlayer(const std::vector<std::string> &cmds) const;
  bool			setPlayerInventory(const std::vector<std::string> &cmds) const;
  bool			setPosPlayer(const std::vector<std::string> &cmds) const;
  bool			setLevelPlayer(const std::vector<std::string> &cmds) const;
  bool			playerExpels(const std::vector<std::string> &cmds) const;
  bool			playerBroadcasts(const std::vector<std::string> &cmds) const;
  bool			playerCastsSpell(const std::vector<std::string> &cmds) const;
  bool			endOfSpell(const std::vector<std::string> &cmds) const;
  bool			playerThrowsResource(const std::vector<std::string> &cmds) const;
  bool			playerPicksUpResource(const std::vector<std::string> &cmds) const;
  bool			playerDead(const std::vector<std::string> &cmds) const;
  bool			playerLays(const std::vector<std::string> &cmds) const;
  bool			playerLaysEgg(const std::vector<std::string> &cmds) const;
  bool			eggHatch(const std::vector<std::string> &cmds) const;
  bool			playerJoinEgg(const std::vector<std::string> &cmds) const;
  bool			eggDead(const std::vector<std::string> &cmds) const;
  bool			setTimeUnit(const std::vector<std::string> &cmds) const;
  bool			endGame(const std::vector<std::string> &cmds) const;

  InterpretProtocol(ActionsManager &_actionManager, ExecuteActions &_executeActions);
  InterpretProtocol(const InterpretProtocol &obj) = delete;
  ~InterpretProtocol();
  InterpretProtocol	&operator=(const InterpretProtocol &obj) = delete;
};


#endif //ZAPPY_GUI_INTERPRETPROTOCOL_HH
