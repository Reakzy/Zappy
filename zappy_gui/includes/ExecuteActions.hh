/*
** ExecuteActions.hh for zappy_gui in /home/werp/rendu/zappy_gui/ExecuteActions.hh
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Tue Jun 20 11:33:02 2017 Paul Wéry
// Last update Sat Jul  1 17:21:01 2017 Wéry
*/

#ifndef ZAPPY_GUI_EXECUTEACTIONS_HH
# define ZAPPY_GUI_EXECUTEACTIONS_HH

# include "irrlicht.h"
# include "MeshLoader.hh"
# include "NodeManipulator.hh"
# include "Players.hh"
# include "VolumeLight.hh"

class GraphicMonitor;
class ActionsManager;

class ExecuteActions
{
  GraphicMonitor				&graphicMonitor;
  ActionsManager				&actionsManager;
  std::shared_ptr<MeshLoader>			meshLoader;
  std::vector<std::string>			objects;
  NodeManipulator				nodeManipulator;
  std::map<std::string, irr::video::SColor>	teamsColor;
  ParserJson					parserJson;
  std::vector<std::shared_ptr<VolumeLight>>	volumeLights;
  unsigned int					frequency;

  void			addObjects(irr::scene::IAnimatedMeshSceneNode *parent, const std::string &key);
  void			addGates();
  void			addGate(irr::scene::IAnimatedMeshSceneNode *parentBlue,
				std::queue<irr::scene::IAnimatedMeshSceneNode*> parentsOrange,
				unsigned int x, unsigned int y);
  void			openTheGate(std::vector<irr::core::vector3df> &positions,
				    std::vector<irr::core::vector3df> &endPositions,
				    irr::core::vector2d<irr::u32> currentPos, irr::core::vector2d<irr::u32> newPos);


  irr::core::vector2d<irr::u32>				getPosInMap(irr::scene::IAnimatedMeshSceneNode *node,
								    irr::scene::IAnimatedMeshSceneNode *ref) const;
  std::queue<irr::scene::IAnimatedMeshSceneNode*>	getOpposites(unsigned int x, unsigned int y) const;

 public:

  void			setSizeMap();
  void			setTile(unsigned int x, unsigned int y);
  void			newTeam(const std::string &team);
  void			newPlayer(const std::string &num, const std::string &team);
  void			setPosPlayer(const std::string &num);
  void			setLevelPlayer(const std::string &num);
  void			playerExpels(const std::string &num);
  void			playerBroadcasts(const std::string &num, const std::string &message);
  void			playerCastsSpell(const std::string &key);
  void			endOfSpell(const std::string &key, bool success);
  void			playerThrowsResource();
  void			playerDead(const std::string &num) const;
  void			playerLays(const std::string &num);
  void			playerLaysEgg(const std::string &num, const std::string &numEgg, const std::string &key);
  void			playerJoinEgg(const std::string &numEgg) const;
  void			eggDead(const std::string &numEgg) const;
  void			endGame(const std::string &winner);
  void			changeTimeUnit(unsigned int frequency);

  void			setMeshLoader();

  ExecuteActions(GraphicMonitor &_graphicMonitor, ActionsManager &_actionsManager);
  ExecuteActions(const ExecuteActions &) = delete;
  ~ExecuteActions();
  ExecuteActions	&operator=(const ExecuteActions &) = delete;
};


#endif //ZAPPY_GUI_EXECUTEACTIONS_HH
