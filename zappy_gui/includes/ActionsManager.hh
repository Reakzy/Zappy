/*
** ActionsManager.hh for zappy_gui in /home/werp/rendu/zappy_gui/ActionsManager.hh
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Mon Jun 19 14:07:25 2017 Paul Wéry
** Last update Mon Jun 19 14:07:25 2017 Paul Wéry
*/

#ifndef ZAPPY_GUI_ACTIONSMANAGER_HH
# define ZAPPY_GUI_ACTIONSMANAGER_HH

# include <map>
# include <vector>
# include <memory>
# include "irrlicht.h"

class		ActionsManager
{
 public:

  enum class Rotation
  {
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
  };

  struct				Player
  {
    irr::core::vector2d<irr::u32>	position;
    Rotation				rotation;
    unsigned int			level;
    std::vector<unsigned int>		inventory;
  };

 private:

  typedef std::map<std::string, std::shared_ptr<Player>> Players;
  typedef std::map<std::string, irr::core::vector2d<irr::u32>> EggsList;

  irr::core::vector2d<irr::u32>			sizeMap;
  std::vector<std::vector<unsigned int>>	tiles;
  std::map<std::string, Players>		teams;
  std::map<std::string, EggsList>		eggs;
  bool						playerPosChanged;
  bool						moovedAtOpposite;

  unsigned int			posToIndex(irr::core::vector2d<irr::u32> position) const;
  irr::core::vector2d<irr::u32>	indexToPos(unsigned int index) const;

 public:

  void			setSizeMap(unsigned int width, unsigned int height);
  void			setTile(unsigned int x, unsigned int y, const std::vector<unsigned int> content);
  void			newTeam(const std::string &teamName);
  void			newPlayer(const std::vector<std::string> &info);
  void			setPlayerInventory(const std::string &num, const std::vector<unsigned int> content);
  void			setPosPlayer(const std::vector<std::string> &info);
  void			setLevelPlayer(const std::string &num, unsigned int level);
  void			playerThrowsResource(const std::string &num, unsigned int resource);
  void			playerPicksUpResource(const std::string &num, unsigned int resource);
  void			playerDead(const std::string &num);
  void			playerLaysEgg(unsigned int x, unsigned int y, const std::string &eggNum, const std::string &num);
  void			playerJoinEgg(const std::string &eggNum);
  void			eggDead(const std::string &eggNum);

  const irr::core::vector2d<irr::u32>		&getSizeMap() const;
  const std::vector<std::vector<unsigned int>>	&getTiles() const;
  const std::vector<unsigned int>		&getTile(unsigned int x, unsigned int y) const;
  const std::map<std::string, Players>		&getTeams() const;
  const std::map<std::string, EggsList>		&getEggs() const;
  std::shared_ptr<ActionsManager::Player>	findPlayer(const std::string &num);
  std::string					teamPlayer(const std::string &num) const;
  std::string					teamEgg(const std::string &eggNum) const;

  bool			playerMooved() const;
  bool			playerMoovedAtOpposite() const;

  ActionsManager();
  ActionsManager(const ActionsManager &) = delete;
  ~ActionsManager();
  ActionsManager	&operator=(const ActionsManager &) = delete;
};


#endif //ZAPPY_GUI_ACTIONSMANAGER_HH
