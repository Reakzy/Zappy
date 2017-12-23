/*
** ExecuteActions.cpp for zappy_gui in /home/werp/rendu/zappy_gui/ExecuteActions.cpp
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Tue Jun 20 11:33:01 2017 Paul Wéry
** Last update Tue Jun 20 11:33:01 2017 Paul Wéry
*/

# include "ExecuteActions.hh"
# include "GraphicMonitor.hh"
# include "ActionsManager.hh"

ExecuteActions::ExecuteActions(GraphicMonitor &_graphicMonitor,
			       ActionsManager &_actionsManager)
: graphicMonitor(_graphicMonitor), actionsManager(_actionsManager)
{
  objects.push_back("Food");
  objects.push_back("Linemate");
  objects.push_back("Deraumère");
  objects.push_back("Sibur");
  objects.push_back("Mendiane");
  objects.push_back("Phiras");
  objects.push_back("Thystame");
  frequency = 1;
}

ExecuteActions::~ExecuteActions()
{

}

void ExecuteActions::setSizeMap()
{
  GraphicMonitor::NodeList		&nodes = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::MAP);
  irr::scene::IAnimatedMeshSceneNode	*node;
  irr::core::vector2d<irr::u32>		sizeMap;
  irr::f32				edge = 0;
  std::string				key;

  graphicMonitor.clearNodes();
  sizeMap = actionsManager.getSizeMap();
  for (unsigned int x = 0; x < sizeMap.X; x++)
    {
      for (unsigned int y = 0; y < sizeMap.Y; y++)
	{
	  key = std::to_string(x) + " " + std::to_string(y);
	  if ((node = meshLoader->loadAsset("BlocMap", "./assets/assets.json")) != nullptr)
	    {
	      edge = nodeManipulator.scaledMaxEdge(node).X * 2;
	      node->setPosition(irr::core::vector3df(edge * x, 0, edge * y));
	      addObjects(node, key);
	      nodes->insert(std::make_pair(key, node));
	    }
	}
    }
  addGates();
  graphicMonitor.addCameraPosition(irr::EKEY_CODE::KEY_DOWN,
				   irr::core::vector3df(sizeMap.X * edge / 2 - edge / 2,
							static_cast<irr::f32>(sizeMap.Y * edge / 1.5), -(edge * 2)));
  graphicMonitor.addCameraPosition(irr::EKEY_CODE::KEY_UP,
				   irr::core::vector3df(sizeMap.X * edge / 2 - edge / 2,
							static_cast<irr::f32>(sizeMap.Y * edge / 1.5), sizeMap.Y * edge + edge));
  graphicMonitor.addCameraPosition(irr::EKEY_CODE::KEY_LEFT,
				   irr::core::vector3df(-edge * 2, static_cast<irr::f32>(sizeMap.Y * edge / 1.5), sizeMap.Y * edge / 2 - edge / 2));
  graphicMonitor.addCameraPosition(irr::EKEY_CODE::KEY_RIGHT,
				   irr::core::vector3df(sizeMap.X * edge + edge,
							static_cast<irr::f32>(sizeMap.Y * edge / 1.5), sizeMap.Y * edge / 2 - edge / 2));
  graphicMonitor.changeCameraPosition(irr::EKEY_CODE::KEY_DOWN);
  graphicMonitor.setPosTargetCamera(irr::core::vector3df(sizeMap.X * edge / 2 - edge / 2, 0,
							 sizeMap.Y * edge / 2 - edge / 2));
  graphicMonitor.setPosLight(irr::core::vector3df(sizeMap.X * edge / 2, sizeMap.X * edge,
						  sizeMap.Y * edge / 2), sizeMap.X * edge);
  graphicMonitor.setRadiusLight(sizeMap.X * edge * 2);
  graphicMonitor.playMusic("Music");
}

void ExecuteActions::addObjects(irr::scene::IAnimatedMeshSceneNode *parent, const std::string &key)
{
  GraphicMonitor::NodeList		&nodes = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::OBJECTS);
  irr::scene::IAnimatedMeshSceneNode	*node;
  std::string				keyObject;

  for (unsigned int index = 0; index < objects.size(); index++)
    {
      keyObject = key + " " + std::to_string(index);
      if ((node = meshLoader->loadAsset(objects.at(index), "./assets/assets.json")) != nullptr)
	{
	  node->setVisible(false);
	  if (index == 0)
	    {
	      nodeManipulator.scaleWithRef(parent, node, 0.3);
	      nodeManipulator.posOnRef(parent, node);
	    }
	  else
	    {
	      nodeManipulator.scaleWithRef(parent, node, 0.1);
	      nodeManipulator.posOnRef(parent, node);
	      nodeManipulator.posAroundRefCenter(parent, node, static_cast<irr::u32>(objects.size() - 1), index - 1);
	    }
	  nodes->insert(std::make_pair(keyObject, node));
	}
    }
}

std::queue<irr::scene::IAnimatedMeshSceneNode*> ExecuteActions::getOpposites(unsigned int x, unsigned int y) const
{
  GraphicMonitor::NodeList				&nodes = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::MAP);
  std::queue<irr::scene::IAnimatedMeshSceneNode*>	opposites;
  std::string						key = "";

  if (x == 0)
    key = std::to_string(actionsManager.getSizeMap().X -1) + " " + std::to_string(y);
  else if (x == actionsManager.getSizeMap().X - 1)
    key = std::to_string(0) + " " + std::to_string(y);
  if (nodes->find(key) != nodes->end())
    opposites.push(nodes->find(key)->second);
  key = "";
  if (y == 0)
    key = std::to_string(x) + " " + std::to_string(actionsManager.getSizeMap().Y - 1);
  else if (y == actionsManager.getSizeMap().Y - 1)
    key = std::to_string(x) + " " + std::to_string(0);
  if (nodes->find(key) != nodes->end())
    opposites.push(nodes->find(key)->second);
  return (opposites);
}

void ExecuteActions::addGates()
{
  GraphicMonitor::NodeList				&nodes = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::MAP);
  irr::scene::IAnimatedMeshSceneNode			*parentBlue;
  std::queue<irr::scene::IAnimatedMeshSceneNode*>	parentsOrange;

  for (unsigned int x = 0; x < actionsManager.getSizeMap().X; x++)
    {
      for (unsigned int y = 0; y < actionsManager.getSizeMap().Y; y++)
	{
	  if (x == 0 || x == actionsManager.getSizeMap().X - 1
	      || y == 0 || y == actionsManager.getSizeMap().Y - 1)
	    {
	      if (nodes->find(std::to_string(x) + " " + std::to_string(y)) != nodes->end())
		{
		  parentBlue = nodes->find(std::to_string(x) + " " + std::to_string(y))->second;
		  parentsOrange = getOpposites(x, y);
		  addGate(parentBlue, parentsOrange, x, y);
		}
	    }
	}
    }
}

void ExecuteActions::addGate(irr::scene::IAnimatedMeshSceneNode *parentBlue,
			     std::queue<irr::scene::IAnimatedMeshSceneNode*> parentsOrange,
			     unsigned int x, unsigned int y)
{
  GraphicMonitor::NodeList		&nodes = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::GATES);
  irr::scene::IAnimatedMeshSceneNode	*blueGate = nullptr;
  irr::scene::IAnimatedMeshSceneNode	*orangeGate = nullptr;
  std::string				key = std::to_string(x) + " " + std::to_string(y);

  if (x == 0 || x == actionsManager.getSizeMap().X - 1)
    {
      if ((blueGate = meshLoader->loadAsset("BlueGate", "./assets/assets.json")) == nullptr
	  || (orangeGate = meshLoader->loadAsset("OrangeGate", "./assets/assets.json")) == nullptr)
	return ;
      blueGate->setVisible(false);
      orangeGate->setVisible(false);
      nodeManipulator.posOnRef(parentBlue, blueGate);
      nodeManipulator.posOnRef(parentsOrange.front(), orangeGate);
      if (x == 0)
	{
	  blueGate->setPosition(blueGate->getPosition() - irr::core::vector3df(nodeManipulator.scaledMaxEdge(parentBlue).X, 0, 0));
	  orangeGate->setPosition(orangeGate->getPosition() + irr::core::vector3df(nodeManipulator.scaledMaxEdge(parentsOrange.front()).X, 0, 0));
	}
      else
	{
	  blueGate->setPosition(blueGate->getPosition() - irr::core::vector3df(-nodeManipulator.scaledMaxEdge(parentBlue).X, 0, 0));
	  orangeGate->setPosition(orangeGate->getPosition() + irr::core::vector3df(-nodeManipulator.scaledMaxEdge(parentsOrange.front()).X, 0, 0));
	}
      blueGate->setRotation(blueGate->getRotation() + irr::core::vector3df(0, 90, 0));
      orangeGate->setRotation(orangeGate->getRotation() + irr::core::vector3df(0, 90, 0));
      nodes->insert(std::make_pair(key + " x Blue", blueGate));
      nodes->insert(std::make_pair(key + " x Orange", orangeGate));
      graphicMonitor.newGate(key + " x Blue", key + " x Orange");
      parentsOrange.pop();
    }
  if (y == 0 || y == actionsManager.getSizeMap().Y - 1)
    {
      if ((blueGate = meshLoader->loadAsset("BlueGate", "./assets/assets.json")) == nullptr
	  || (orangeGate = meshLoader->loadAsset("OrangeGate", "./assets/assets.json")) == nullptr)
	return ;
      blueGate->setVisible(false);
      orangeGate->setVisible(false);
      nodeManipulator.posOnRef(parentBlue, blueGate);
      nodeManipulator.posOnRef(parentsOrange.front(), orangeGate);
      if (y == 0)
	{
	  blueGate->setPosition(blueGate->getPosition() - irr::core::vector3df(0, 0, nodeManipulator.scaledMaxEdge(parentBlue).Z));
	  orangeGate->setPosition(orangeGate->getPosition() + irr::core::vector3df(0, 0, nodeManipulator.scaledMaxEdge(parentsOrange.front()).Z));
	}
      else
	{
	  blueGate->setPosition(blueGate->getPosition() - irr::core::vector3df(0, 0, -nodeManipulator.scaledMaxEdge(parentBlue).Z));
	  orangeGate->setPosition(orangeGate->getPosition() + irr::core::vector3df(0, 0, -nodeManipulator.scaledMaxEdge(parentsOrange.front()).Z));
	}
      nodes->insert(std::make_pair(key + " y Blue", blueGate));
      nodes->insert(std::make_pair(key + " y Orange", orangeGate));
      graphicMonitor.newGate(key + " y Blue", key + " y Orange");
      parentsOrange.pop();
    }
}

void ExecuteActions::setTile(unsigned int x, unsigned int y)
{
  GraphicMonitor::NodeList	&nodesMap = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::MAP);
  GraphicMonitor::NodeList	&nodes = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::OBJECTS);
  std::vector<unsigned int>	tile = actionsManager.getTile(x, y);
  std::string			key = std::to_string(x) + " " + std::to_string(y);
  std::string			keyObject;

  if (nodesMap->find(key) == nodes->end())
    return ;
  for (unsigned int index = 0; index < tile.size(); index++)
    {
      keyObject = key + " " + std::to_string(index);
      if (nodes->find(keyObject) != nodes->end())
	{
	  nodes->find(keyObject)->second->setVisible(tile.at(index) > 0);
	}
    }
}

void ExecuteActions::newTeam(const std::string &team)
{
  ParserJson::Data	bloc;
  std::string		key;
  irr::video::SColor	color;
  std::vector<double>	infos;

  if (parserJson.loadFile("./assets/colors.json")
      && (bloc = parserJson.getBlocString("palette")).get() != nullptr)
    {
      key = std::to_string(teamsColor.size() + 1);
      if (bloc->numericTabValues.find(key) != bloc->numericTabValues.end()
	  && (infos = bloc->numericTabValues.find(key)->second).size() == 3)
	color.set(255, static_cast<irr::u32>(infos.at(0)),
		  static_cast<irr::u32>(infos.at(1)),
		  static_cast<irr::u32>(infos.at(2)));
      else
	color.set(255, static_cast<irr::u32>(std::rand() % 256),
		  static_cast<irr::u32>(std::rand() % 256),
		  static_cast<irr::u32>(std::rand() % 256));
      teamsColor[team] = color;
      graphicMonitor.getTeamsPanel().addPrintableText(team, color);
    }
}

void ExecuteActions::newPlayer(const std::string &num, const std::string &team)
{
  GraphicMonitor::NodeList			&nodesMap = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::MAP);
  GraphicMonitor::NodeList			&nodes = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::PLAYERS);
  std::shared_ptr<ActionsManager::Player>	player = actionsManager.findPlayer(num);
  irr::scene::IAnimatedMeshSceneNode		*node;
  std::string					key;

  if (player.get() != nullptr && (node = meshLoader->loadAsset("Player", "./assets/assets.json")) != nullptr)
    {
      for (unsigned int index = 0; index < node->getMaterialCount(); index++)
	{
	  node->getMaterial(index).Shininess = 0.5f;
	  if (teamsColor.find(team) != teamsColor.end())
	    node->getMaterial(index).SpecularColor = teamsColor[team];
	}
      key = std::to_string(player->position.X) + " " + std::to_string(player->position.Y);
      nodeManipulator.scaleWithRef(nodesMap->find(key)->second, node, 0.4);
      nodeManipulator.posOnRef(nodesMap->find(key)->second, node);
      node->setRotation(nodeManipulator.convInRotationValue(static_cast<NodeManipulator::Rotation>(player->rotation)));
      nodes->insert(std::make_pair(num, node));
      graphicMonitor.newPlayer(num);
      graphicMonitor.playSound("Player_connect");
    }
}

irr::core::vector2d<irr::u32> ExecuteActions::getPosInMap(irr::scene::IAnimatedMeshSceneNode *node,
							  irr::scene::IAnimatedMeshSceneNode *ref) const
{
  irr::core::vector2d<irr::u32>	posInMap;
  irr::f32			edge;

  edge = nodeManipulator.scaledMaxEdge(ref).X * 2;
  posInMap.X = static_cast<irr::u32>(node->getPosition().X / edge);
  posInMap.Y = static_cast<irr::u32>(node->getPosition().Z / edge);
  return (posInMap);
}

void ExecuteActions::openTheGate(std::vector<irr::core::vector3df> &positions,
				 std::vector<irr::core::vector3df> &endPositions,
				 irr::core::vector2d<irr::u32> currentPos, irr::core::vector2d<irr::u32> newPos)
{
  GraphicMonitor::NodeList		&nodes = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::GATES);
  GraphicMonitor::NodeList		&nodesMap = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::MAP);
  std::shared_ptr<Gate>			gate;
  irr::scene::IAnimatedMeshSceneNode	*blueGate;
  irr::scene::IAnimatedMeshSceneNode	*orangeGate;
  irr::scene::IAnimatedMeshSceneNode	*map;
  std::string				key = std::to_string(currentPos.X) + " " + std::to_string(currentPos.Y);

  if (nodesMap->find(std::to_string(newPos.X) + " " + std::to_string(newPos.Y)) == nodesMap->end())
    return ;
  map = nodesMap->find(std::to_string(newPos.X) + " " + std::to_string(newPos.Y))->second;
  if (currentPos.X != newPos.X)
    {
      if (nodes->find(key + " x Blue") == nodes->end() || nodes->find(key + " x Orange") == nodes->end())
	return ;
      blueGate = nodes->find(key + " x Blue")->second;
      orangeGate = nodes->find(key + " x Orange")->second;
      positions.push_back(blueGate->getPosition());
      endPositions.push_back(orangeGate->getPosition());
      positions.push_back(map->getPosition());
      endPositions.push_back(map->getPosition());
      gate = graphicMonitor.getGate(key + " x Blue");
      if (gate.get() != nullptr)
	gate->setAction(nodeManipulator.getScaleWithRef(map, blueGate, 0.0001),
			nodeManipulator.getScaleWithRef(map, blueGate, 1));
    }
  if (currentPos.Y != newPos.Y)
    {
      if (nodes->find(key + " y Blue") == nodes->end() || nodes->find(key + " y Orange") == nodes->end())
	return ;
      blueGate = nodes->find(key + " y Blue")->second;
      orangeGate = nodes->find(key + " y Orange")->second;
      positions.push_back(blueGate->getPosition());
      endPositions.push_back(orangeGate->getPosition());
      positions.push_back(map->getPosition());
      endPositions.push_back(map->getPosition());
      gate = graphicMonitor.getGate(key + " y Blue");
      if (gate.get() != nullptr)
	gate->setAction(nodeManipulator.getScaleWithRef(map, blueGate, 0.0001),
			nodeManipulator.getScaleWithRef(map, blueGate, 1));
    }
  graphicMonitor.playSound("Portal_Opening");
}

void ExecuteActions::setPosPlayer(const std::string &num)
{
  GraphicMonitor::NodeList			&nodesMap = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::MAP);
  GraphicMonitor::NodeList			&nodes = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::PLAYERS);
  std::shared_ptr<ActionsManager::Player>	player = actionsManager.findPlayer(num);
  std::shared_ptr<Players>			playerObject = graphicMonitor.getPlayer(num);
  std::string					key;
  std::vector<irr::core::vector3df>		positions;
  std::vector<irr::core::vector3df>		endPositions;

  if (player.get() != nullptr && playerObject.get() != nullptr)
    {
      key = std::to_string(player->position.X) + " " + std::to_string(player->position.Y);
      if (actionsManager.playerMooved())
	{
	  if (!actionsManager.playerMoovedAtOpposite())
	    {
	      positions.push_back(nodesMap->find(key)->second->getPosition());
	      endPositions.push_back(nodesMap->find(key)->second->getPosition());
	    }
	  else
	    openTheGate(positions, endPositions,
			getPosInMap(nodes->find(num)->second, nodesMap->find(key)->second),
			irr::core::vector2d<irr::u32>(player->position.X, player->position.Y));
	  playerObject->setTargetPosition(positions, endPositions);
	}
      nodes->find(num)->second->setRotation(nodeManipulator.convInRotationValue
       (static_cast<NodeManipulator::Rotation>(player->rotation)));
    }
}

void ExecuteActions::setLevelPlayer(const std::string &num)
{
  GraphicMonitor::NodeList			&nodesMap = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::MAP);
  GraphicMonitor::NodeList			&nodes = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::PLAYERS);
  std::shared_ptr<ActionsManager::Player>	player = actionsManager.findPlayer(num);
  std::string					key;

  if (player.get() != nullptr && player->level > 0)
    {
      key = std::to_string(player->position.X) + " " + std::to_string(player->position.Y);
      nodes->find(num)->second->setFrameLoop(0, 0);
      nodes->find(num)->second->setLoopMode(false);
      nodeManipulator.scaleWithRef(nodesMap->find(key)->second, nodes->find(num)->second,
				   static_cast<irr::f32>(0.4) + static_cast<irr::f32>((player->level - 1) * 0.05));
      nodeManipulator.posOnRef(nodesMap->find(key)->second, nodes->find(num)->second);
      if (graphicMonitor.getAnimations().find("moove") != graphicMonitor.getAnimations().end())
	{
	  nodes->find(num)->second->setFrameLoop(graphicMonitor.getAnimations().find("moove")->second.at(0),
						 graphicMonitor.getAnimations().find("moove")->second.at(1));
	}
      nodes->find(num)->second->setLoopMode(true);
    }
}

void ExecuteActions::playerExpels(const std::string &num)
{
  GraphicMonitor::NodeList	&nodes = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::PLAYERS);

  if (graphicMonitor.getAnimations().find("eject") != graphicMonitor.getAnimations().end())
    {
      nodes->find(num)->second->setLoopMode(true);
      nodes->find(num)->second->setFrameLoop(graphicMonitor.getAnimations().find("eject")->second.at(0),
					     graphicMonitor.getAnimations().find("eject")->second.at(1));
    }
  graphicMonitor.playSound("Eject");
}

void ExecuteActions::playerBroadcasts(const std::string &num, const std::string &message)
{
  std::string		team = actionsManager.teamPlayer(num);

  if (this->teamsColor.find(team) != this->teamsColor.end())
    {
      this->graphicMonitor.getBroadcastPanel().addPrintableText(message, this->teamsColor.find(team)->second);
    }
}

void ExecuteActions::playerCastsSpell(const std::string &key)
{
  GraphicMonitor::NodeList	&nodesMap = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::MAP);
  std::shared_ptr<VolumeLight>	volumeLight;
  unsigned int			index = 0;

  if (nodesMap->find(key) == nodesMap->end())
    return ;
  while (index < volumeLights.size() && volumeLights.at(index)->isUsed())
    index++;
  if (index < volumeLights.size())
    {
      volumeLights.at(index)->isUsed() = true;
      volumeLights.at(index)->assignedBloc() = key;
      volumeLights.at(index)->getVolumeLight()->setVisible(true);
      nodeManipulator.posOnRef(nodesMap->find(key)->second, volumeLights.at(index)->getVolumeLight());
      volumeLights.at(index)->getVolumeLight()->setPosition
       (volumeLights.at(index)->getVolumeLight()->getPosition()
	+ irr::core::vector3df(0, -nodeManipulator.scaledMaxEdge(volumeLights.at(index)->getVolumeLight()).Y
				  * volumeLights.at(index)->getVolumeLight()->getScale().Y, 0));

    }
  else
    {
      volumeLight.reset(new VolumeLight(graphicMonitor.getSceneManager(),
					graphicMonitor.getVideoDriver()));
      volumeLight->loadVolumeLight("./assets/animations.json", "Incantation");
      nodeManipulator.scaleWithRef(nodesMap->find(key)->second, volumeLight->getVolumeLight(), 1.5);
      nodeManipulator.posOnRef(nodesMap->find(key)->second, volumeLight->getVolumeLight());
      volumeLight->getVolumeLight()->setPosition
       (volumeLight->getVolumeLight()->getPosition()
	+ irr::core::vector3df(0, -nodeManipulator.scaledMaxEdge(volumeLight->getVolumeLight()).Y
				  * volumeLight->getVolumeLight()->getScale().Y, 0));
      volumeLight->isUsed() = true;
      volumeLight->assignedBloc() = key;
      volumeLights.push_back(volumeLight);
    }
  graphicMonitor.playSound("StartIncantation");
}

void ExecuteActions::endOfSpell(const std::string &key, bool success)
{
  unsigned int index = 0;

  if (success)
    graphicMonitor.playSound("IncantationPass");
  else
    graphicMonitor.playSound("IncantationFail");
 while (index < volumeLights.size()
	&& (!volumeLights.at(index)->isUsed() || volumeLights.at(index)->assignedBloc() != key))
   {
     index++;
   }
  if (index < volumeLights.size())
    {
      volumeLights.at(index)->isUsed() = false;
      volumeLights.at(index)->getVolumeLight()->setVisible(false);
    }
}

void ExecuteActions::playerThrowsResource()
{
  graphicMonitor.playSound("Throw_resource");
}

void ExecuteActions::playerDead(const std::string &num) const
{
  std::shared_ptr<Players>	player = graphicMonitor.getPlayer(num);

  if (player.get() != nullptr)
    {
      if (graphicMonitor.getAnimations().find("dead") != graphicMonitor.getAnimations().end())
	{
	  player->getNode()->setLoopMode(false);
	  player->getNode()->setFrameLoop(graphicMonitor.getAnimations().find("dead")->second.at(0),
					  graphicMonitor.getAnimations().find("dead")->second.at(1));
	  player->setAnimationDead(true);
	}
      else
      	graphicMonitor.deadPlayer(num);
      graphicMonitor.playSound("Player_death");
    }
}

void ExecuteActions::playerLays(const std::string &num)
{
  GraphicMonitor::NodeList	&nodes = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::PLAYERS);

  if (nodes->find(num) == nodes->end())
    return ;
  if (graphicMonitor.getAnimations().find("lay") != graphicMonitor.getAnimations().end())
    {
      nodes->find(num)->second->setLoopMode(true);
      nodes->find(num)->second->setFrameLoop(graphicMonitor.getAnimations().find("lay")->second.at(0),
					     graphicMonitor.getAnimations().find("lay")->second.at(1));
    }
  graphicMonitor.playSound("Lay_egg");
}

void ExecuteActions::playerLaysEgg(const std::string &num, const std::string &numEgg, const std::string &key)
{
  GraphicMonitor::NodeList		&nodesMap = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::MAP);
  GraphicMonitor::NodeList		&nodes = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::PLAYERS);
  GraphicMonitor::NodeList		&eggsNodes = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::EGGS);
  irr::scene::IAnimatedMeshSceneNode	*node;
  std::string				team = actionsManager.teamEgg(numEgg);

  if (teamsColor.find(team) != teamsColor.end()
      && (node = meshLoader->loadAsset("Eggs", "./assets/assets.json")) != nullptr)
    {
      for (unsigned int index = 0; index < node->getMaterialCount(); index++)
      {
	node->getMaterial(index).Shininess = 0.5f;
	if (teamsColor.find(team) != teamsColor.end())
	  node->getMaterial(index).SpecularColor = teamsColor[team];
      }
      eggsNodes->insert(std::make_pair(numEgg, node));
      nodeManipulator.scaleWithRef(nodesMap->find(key)->second, node, 0.3);
      nodeManipulator.posOnRef(nodesMap->find(key)->second, node);
      if (graphicMonitor.getAnimations().find("moove") != graphicMonitor.getAnimations().end())
	{
	  nodes->find(num)->second->setLoopMode(true);
	  nodes->find(num)->second->setFrameLoop(graphicMonitor.getAnimations().find("moove")->second.at(0),
						 graphicMonitor.getAnimations().find("moove")->second.at(1));
	}
      graphicMonitor.playSound("Birth_of_egg");
    }
}

void ExecuteActions::playerJoinEgg(const std::string &numEgg) const
{
  GraphicMonitor::NodeList	&eggsNodes = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::EGGS);

  if (eggsNodes->find(numEgg) != eggsNodes->end())
    {
      eggsNodes->find(numEgg)->second->remove();
      eggsNodes->erase(eggsNodes->find(numEgg));
    }
}

void ExecuteActions::eggDead(const std::string &numEgg) const
{
  GraphicMonitor::NodeList	&eggsNodes = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::EGGS);

  if (eggsNodes->find(numEgg) != eggsNodes->end())
    {
      eggsNodes->find(numEgg)->second->remove();
      eggsNodes->erase(eggsNodes->find(numEgg));
    }
}

void ExecuteActions::endGame(const std::string &winner)
{
  GraphicMonitor::NodeList	&nodesMap = graphicMonitor.getNodes(GraphicMonitor::TypeNodes::MAP);

  if (this->teamsColor.find(winner) != this->teamsColor.end())
    {
      for (std::map<std::string, irr::scene::IAnimatedMeshSceneNode*>::const_iterator it = nodesMap->begin();
	   it != nodesMap->end(); ++it)
	{
	  for (unsigned int index = 0; index < it->second->getMaterialCount(); index++)
	    {
	      it->second->getMaterial(index).Shininess = 0.5f;
	      it->second->getMaterial(index).SpecularColor = teamsColor[winner];
	    }
	}
      graphicMonitor.stopMusic("Music");
      graphicMonitor.playMusic("MusicEndGame");
      if (this->graphicMonitor.getCredits() != nullptr)
	this->graphicMonitor.getCredits()->setVisible(true);
    }
}

void ExecuteActions::changeTimeUnit(unsigned int frequency)
{
  graphicMonitor.setFrequency(frequency);
  graphicMonitor.setGateFrequency(frequency);
  this->frequency = frequency;
  this->meshLoader->setFrequency(frequency);
}

void ExecuteActions::setMeshLoader()
{
  meshLoader.reset(new MeshLoader(graphicMonitor.getSceneManager(),
				  graphicMonitor.getVideoDriver()));
}
