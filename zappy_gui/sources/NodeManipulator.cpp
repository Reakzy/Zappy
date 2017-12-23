/*
** NodeManipulator.cpp for zappy_gui in /home/werp/rendu/zappy_gui/NodeManipulator.cpp
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Sun Jun 25 14:26:04 2017 Paul Wéry
** Last update Sun Jun 25 14:26:04 2017 Paul Wéry
*/

#include "NodeManipulator.hh"

NodeManipulator::NodeManipulator()
{
  rotation.insert(std::make_pair(Rotation::NORTH, irr::core::vector3df(0, 0, 0)));
  rotation.insert(std::make_pair(Rotation::EAST, irr::core::vector3df(0, 90, 0)));
  rotation.insert(std::make_pair(Rotation::SOUTH, irr::core::vector3df(0, 180, 0)));
  rotation.insert(std::make_pair(Rotation::WEST, irr::core::vector3df(0, 260, 0)));
}

NodeManipulator::~NodeManipulator()
{

}

irr::core::vector3d<irr::f32> NodeManipulator::scaledMaxEdge(irr::scene::ISceneNode *node) const
{
  return (node->getBoundingBox().MaxEdge * node->getScale());
}

void NodeManipulator::scaleWithRef(irr::scene::ISceneNode *ref,
				   irr::scene::ISceneNode *node,
				   irr::f32 scale) const
{
  irr::f32		realScale;

  realScale = scaledMaxEdge(ref).X * scale / node->getBoundingBox().MaxEdge.X;
  node->setScale(irr::core::vector3df(realScale, realScale, realScale));
}

void NodeManipulator::posOnRef(irr::scene::ISceneNode *ref,
			       irr::scene::ISceneNode *node) const
{
  irr::f32	edge = scaledMaxEdge(ref).Y;
  irr::f32	posY;

  posY = ref->getPosition().Y + edge + scaledMaxEdge(node).Y * node->getScale().Y;
  node->setPosition(ref->getPosition() + irr::core::vector3df(0, posY, 0));
}

void NodeManipulator::posAroundRefCenter(irr::scene::ISceneNode *ref,
					 irr::scene::ISceneNode *node,
					 irr::u32 pointsOnCircle, irr::u32 index) const
{
  irr::f32	angle = 360 / pointsOnCircle * index;
  irr::f32	ray = scaledMaxEdge(ref).X - scaledMaxEdge(node).X * 4;
  irr::f32	posX;
  irr::f32	posZ;

  posX = ref->getPosition().X + (ray * std::cos(angle));
  posZ = ref->getPosition().Z + (ray * std::sin(angle));
  node->setPosition(irr::core::vector3df(posX, node->getPosition().Y, posZ));
}

irr::core::vector3df NodeManipulator::convInRotationValue(NodeManipulator::Rotation state)
{
  return (rotation[state]);
}

irr::f32 NodeManipulator::getScaleWithRef(irr::scene::ISceneNode *ref,
					  irr::scene::ISceneNode *node,
					  irr::f32 scale) const
{
  return (scaledMaxEdge(ref).X * scale / node->getBoundingBox().MaxEdge.X);
}
