/*
** Players.hh for zappy_gui in /home/werp/rendu/zappy_gui/Players.hh
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Mon Jun 26 11:07:24 2017 Paul Wéry
// Last update Sat Jul  1 15:34:19 2017 Wéry
*/

#ifndef ZAPPY_GUI_PLAYERS_HH
#define ZAPPY_GUI_PLAYERS_HH

# include <map>
# include <queue>
# include <vector>
# include "irrlicht.h"
# include "TimeUnit.hh"

class GraphicMonitor;

class Players : public irr::scene::IAnimationEndCallBack
{
  std::string						num;
  TimeUnit						timeUnit;
  std::vector<irr::core::vector3df>			shifting;
  std::map<std::string, std::vector<irr::s32>>		animations;
  irr::scene::IAnimatedMeshSceneNode			*node;
  std::vector<irr::core::vector3df>			targetPosition;
  std::vector<irr::core::vector3df>			endPosition;
  std::vector<long>					remainingTimes;
  bool							haveTarget;
  bool							animationDead;
  bool							alive;

  irr::core::vector3df			getSumShifting() const;
  void					actualizeTarget();

 public:

  virtual void				OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode *node);
  void					setNode(irr::scene::IAnimatedMeshSceneNode *node);
  void					setFrequency(unsigned int frequency);
  irr::scene::IAnimatedMeshSceneNode	*getNode() const;
  const std::string			&getNum() const;
  void					setTargetPosition(const std::vector<irr::core::vector3df> &position,
							  const std::vector<irr::core::vector3df> &endPosition);
  void					moove();
  void					setAnimationDead(bool state);
  bool					isAlive() const;

  Players(const std::string &num, const std::map<std::string, std::vector<irr::s32>> &_animations);
  Players(const Players &);
  ~Players();
  Players	&operator=(const Players &) = delete;
};


#endif //ZAPPY_GUI_PLAYERS_HH
