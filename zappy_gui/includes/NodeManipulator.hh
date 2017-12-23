/*
** NodeManipulator.hh for zappy_gui in /home/werp/rendu/zappy_gui/NodeManipulator.hh
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Sun Jun 25 14:26:04 2017 Paul Wéry
** Last update Sun Jun 25 14:26:04 2017 Paul Wéry
*/

#ifndef ZAPPY_GUI_NODEMANIPULATOR_HH
#define ZAPPY_GUI_NODEMANIPULATOR_HH

# include <cmath>
# include <map>
# include "irrlicht.h"

class NodeManipulator
{
 public:

  enum class Rotation
  {
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
  };

 private:

  std::map<Rotation, irr::core::vector3df>	rotation;

 public:

  void		scaleWithRef(irr::scene::ISceneNode *ref, irr::scene::ISceneNode *node, irr::f32 scale) const;
  irr::f32	getScaleWithRef(irr::scene::ISceneNode *ref, irr::scene::ISceneNode *node, irr::f32 scale) const;
  void		posOnRef(irr::scene::ISceneNode *ref,
				   irr::scene::ISceneNode *node) const;
  void		posAroundRefCenter(irr::scene::ISceneNode *ref,
					 irr::scene::ISceneNode *node,
					 irr::u32 pointsOnCircle, irr::u32 index) const;

  irr::core::vector3d<irr::f32>	scaledMaxEdge(irr::scene::ISceneNode *node) const;

  irr::core::vector3df	convInRotationValue(Rotation state);

  NodeManipulator();
  NodeManipulator(const NodeManipulator &) = delete;
  ~NodeManipulator();
  NodeManipulator	&operator=(const NodeManipulator &) = delete;
};


#endif //ZAPPY_GUI_NODEMANIPULATOR_HH
