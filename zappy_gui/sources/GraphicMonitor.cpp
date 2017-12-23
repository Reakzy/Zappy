/*
** GraphicMonitor.cpp for zappy_gui in /home/werp/rendu/zappy_gui/GraphicMonitor.cpp
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Tue Jun 20 11:34:47 2017 Paul Wéry
** Last update Tue Jun 20 11:34:47 2017 Paul Wéry
*/

# include "GraphicMonitor.hh"

GraphicMonitor::GraphicMonitor()
: executeActions(*this, actionsManager), interpretProtocol(actionsManager, executeActions), eventReceiver(*this)
{
  parserJson.loadFile("./config/config.json");
  connected = false;
  map.reset(new std::map<std::string, irr::scene::IAnimatedMeshSceneNode*>());
  playersNodes.reset(new std::map<std::string, irr::scene::IAnimatedMeshSceneNode*>());
  eggs.reset(new std::map<std::string, irr::scene::IAnimatedMeshSceneNode*>());
  objects.reset(new std::map<std::string, irr::scene::IAnimatedMeshSceneNode*>());
  gatesNodes.reset(new std::map<std::string, irr::scene::IAnimatedMeshSceneNode*>());
  allNodes[TypeNodes::MAP] = map;
  allNodes[TypeNodes::PLAYERS] = playersNodes;
  allNodes[TypeNodes::EGGS] = eggs;
  allNodes[TypeNodes::OBJECTS] = objects;
  allNodes[TypeNodes::GATES] = gatesNodes;
  frequency = 1;
}

GraphicMonitor::~GraphicMonitor()
{

}

bool GraphicMonitor::connectGraphic(const std::string &ip, const std::string &port)
{
  return (socket.openConnection(ip, port));
}

bool GraphicMonitor::startDevice()
{
  irr::core::dimension2d<irr::u32>	dimension(1600, 900);
  ParserJson::Data			infos;
  std::vector<double>			info;
  irr::video::ITexture			*texture;

  if ((infos = parserJson.getBlocString("Screen")).get() != nullptr
      && infos->numericTabValues.find("dimension") != infos->numericTabValues.end()
      && infos->numericTabValues.find("dimension")->second.size() == 2)
    {
      info = infos->numericTabValues.find("dimension")->second;
      dimension.set(static_cast<irr::u32>(info.at(0)), static_cast<irr::u32>(info.at(1)));
    }
  this->device = irr::createDevice(irr::video::EDT_OPENGL, dimension, 16, false, false, false, &eventReceiver);
  if (this->device != nullptr && (infos = parserJson.getBlocString("Background")).get() != nullptr
      && infos->stringValues.find("path") != infos->stringValues.end())
    {
      if ((texture = this->getVideoDriver()->getTexture(infos->stringValues.find("path")->second.c_str())) != nullptr)
	{
	  this->background = this->device->getGUIEnvironment()->addImage
	   (texture, irr::core::vector2d<irr::s32>(0, 0), false);
	  if (this->background != nullptr)
	    this->background->setVisible(true);
	}
    }
  if (this->device != nullptr && (infos = parserJson.getBlocString("StonesPanel")).get() != nullptr
      && infos->stringValues.find("path") != infos->stringValues.end())
    {
      if ((texture = this->getVideoDriver()->getTexture(infos->stringValues.find("path")->second.c_str())) != nullptr)
	{
	  this->stonesPanel = this->device->getGUIEnvironment()->addImage
	   (texture, irr::core::vector2d<irr::s32>(0, 0), false);
	  if (this->stonesPanel != nullptr)
	    {
	      this->stonesPanel->setUseAlphaChannel(true);
	      this->stonesPanel->setVisible(true);
	    }
	}
    }
  if (this->device != nullptr && (infos = parserJson.getBlocString("Credits")).get() != nullptr
      && infos->stringValues.find("path") != infos->stringValues.end())
    {
      if ((texture = this->getVideoDriver()->getTexture(infos->stringValues.find("path")->second.c_str())) != nullptr)
	{
	  this->credits = this->device->getGUIEnvironment()->addImage
	   (texture, irr::core::vector2d<irr::s32>(dimension.Width / 3, 0), false);
	  if (this->credits != nullptr)
	    {
	      this->credits->setUseAlphaChannel(true);
	      this->credits->setVisible(false);
	    }
	}
    }
  if (this->device != nullptr)
    {
      teamsPanel.createPanel(this->device->getGUIEnvironment(),
			     irr::core::position2d<irr::u32>(0, dimension.Height / 2),
			     irr::core::dimension2d<irr::u32>(dimension.Width / 4, dimension.Height / 2));
      broadcastPanel.createPanel(this->device->getGUIEnvironment(),
				 irr::core::position2d<irr::u32>(dimension.Width - dimension.Width / 4, 0), dimension / 4);
    }
  return (this->device != nullptr);
}

void GraphicMonitor::launchGraphic()
{
  std::string	msg;
  bool		continueToRead;

  this->device->getCursorControl()->setVisible(false);
  this->executeActions.setMeshLoader();
  this->loadAnimationsPlayer();
  this->loadSounds();
  this->camera = this->device->getSceneManager()->addCameraSceneNodeFPS(0, 100.0, 0.01);
  this->camera->setInputReceiverEnabled(false);
  this->light.push_back(this->device->getSceneManager()->addLightSceneNode());
  this->light.push_back(this->device->getSceneManager()->addLightSceneNode());
  this->light.push_back(this->device->getSceneManager()->addLightSceneNode());
  this->light.push_back(this->device->getSceneManager()->addLightSceneNode());
  this->light.push_back(this->device->getSceneManager()->addLightSceneNode());
  while (this->device->run())
    {
      this->doAnimations();
      continueToRead = true;
      while (continueToRead)
	{
	  socket.monitorFds();
	  socket.readSocket();
	  msg = socket.pullCommand();
	  if ((continueToRead = msg.size() > 0 && msg.back() == '\n'))
	    msgQueue.push(msg);
	}
      if (connectionEstablished())
	{
	  while (msgQueue.size() > 0)
	    {
	      interpretProtocol.interpretCommand(msgQueue.front());
	      msgQueue.pop();
	    }
	  device->getVideoDriver()->beginScene();
	  if (this->background != nullptr)
	    background->draw();
	  device->getSceneManager()->drawAll();
	  this->drawInfoPanels();
	  if (this->credits != nullptr)
	    this->credits->draw();
	  device->getVideoDriver()->endScene();
	}
    }
}

bool GraphicMonitor::connectionEstablished()
{
  if (!connected)
    {
      if (msgQueue.size() > 0 && msgQueue.front() == "WELCOME\n")
	{
	  if ((connected = socket.writeSocket("GRAPHIC")))
	    {
	      msgQueue.pop();
	    }
	}
      return (false);
    }
  return (true);
}

void GraphicMonitor::drawInfoPanels()
{
  if (this->stonesPanel != nullptr)
    stonesPanel->draw();
  this->teamsPanel.drawPanel();
  this->broadcastPanel.drawPanel();
}

void GraphicMonitor::loadAnimationsPlayer()
{
  ParserJson::Data					data;
  std::vector<irr::s32>					vector;

  if (!parserJson.loadFile("./assets/players/players.json")
      || (data = parserJson.getBlocString("animations")).get() == nullptr)
    return ;
  for (std::map<std::string, std::vector<double>>::iterator it = data->numericTabValues.begin();
       it != data->numericTabValues.end(); ++it)
    {
      vector.clear();
      if (it->second.size() == 2)
	{
	  vector.push_back(static_cast<irr::s32>(it->second.at(0)));
	  vector.push_back(static_cast<irr::s32>(it->second.at(1)));
	  animations.insert(std::make_pair(it->first, vector));
	}
    }
}

void GraphicMonitor::loadSounds()
{
  ParserJson::Data					data;
  std::vector<std::string>				soundsList;
  std::shared_ptr<SoundLoader>				soundLoader;

  if (!parserJson.loadFile("./assets/sounds.json") || parserJson.getBlocsString().get() == nullptr)
    return ;
  for (std::map<std::string, ParserJson::Data>::iterator it = parserJson.getBlocsString()->begin();
       it != parserJson.getBlocsString()->end(); ++it)
    {
      soundsList.clear();
      data = it->second;
      if (data->stringValues.find("Path") != data->stringValues.end()
	  && data->stringTabValues.find("Sounds") != data->stringTabValues.end())
	{
	  for (unsigned int index = 0; index < data->stringTabValues.find("Sounds")->second.size(); index++)
	    soundsList.push_back(data->stringValues.find("Path")->second
				 + data->stringTabValues.find("Sounds")->second.at(index));
	  soundLoader.reset(new SoundLoader());
	  soundLoader->loadSounds(soundsList);
	  this->sounds.insert(std::make_pair(it->first, soundLoader));
	}
    }
}

GraphicMonitor::NodeList &GraphicMonitor::getNodes(GraphicMonitor::TypeNodes type)
{
  return (allNodes[type]);
}

irr::scene::ISceneManager *GraphicMonitor::getSceneManager() const
{
  return (device->getSceneManager());
}

irr::video::IVideoDriver *GraphicMonitor::getVideoDriver() const
{
  return (device->getVideoDriver());
}

void GraphicMonitor::setPosTargetCamera(const irr::core::vector3df &position)
{
  this->camera->setTarget(position);
}

void GraphicMonitor::setPosLight(const irr::core::vector3df &position, irr::f32 width)
{
  irr::core::vector3df	pos = position;

  this->light.at(0)->setPosition(pos);
  pos.set(position.X - width * 2, 0, position.Z);
  this->light.at(1)->setPosition(pos);
  pos.set(position.X + width * 2, 0, position.Z);
  this->light.at(2)->setPosition(pos);
  pos.set(position.X, 0, position.Z - width * 2);
  this->light.at(3)->setPosition(pos);
  pos.set(position.X, 0, position.Z + width * 2);
  this->light.at(4)->setPosition(pos);

}

void GraphicMonitor::setRadiusLight(irr::f32 radius)
{
  for (unsigned int index = 0; index < this->light.size(); index++)
    this->light.at(index)->setRadius(radius);
}

void GraphicMonitor::clearNodes()
{
  for (std::map<std::string, irr::scene::IAnimatedMeshSceneNode*>::iterator it = map->begin(); it != map->end(); ++it)
    it->second->remove();
  for (std::map<std::string, irr::scene::IAnimatedMeshSceneNode*>::iterator it = playersNodes->begin(); it != playersNodes->end(); ++it)
    it->second->remove();
  for (std::map<std::string, irr::scene::IAnimatedMeshSceneNode*>::iterator it = eggs->begin(); it != eggs->end(); ++it)
    it->second->remove();
  for (std::map<std::string, irr::scene::IAnimatedMeshSceneNode*>::iterator it = objects->begin(); it != objects->end(); ++it)
    it->second->remove();
  for (std::map<std::string, irr::scene::IAnimatedMeshSceneNode*>::iterator it = gatesNodes->begin(); it != gatesNodes->end(); ++it)
    it->second->remove();
  map->clear();
  playersNodes->clear();
  eggs->clear();
  objects->clear();
  gatesNodes->clear();
}

void GraphicMonitor::newPlayer(const std::string &num)
{
  std::shared_ptr<Players>	player;

  if (playersNodes->find(num) != playersNodes->end())
    {
      player.reset(new Players(num, animations));
      player->setNode(playersNodes->find(num)->second);
      player->setFrequency(frequency);
      players.push_back(player);
    }
}

void GraphicMonitor::deadPlayer(const std::string &num)
{
  if (playersNodes->find(num) != playersNodes->end())
    {
      playersNodes->find(num)->second->remove();
      for (std::vector<std::shared_ptr<Players>>::iterator it = players.begin(); it != players.end();)
	{
	  if ((*it)->getNum() == num)
	    it = players.erase(it);
	  else
	    ++it;
	}
      playersNodes->erase(playersNodes->find(num));
    }
}

std::shared_ptr<Players> GraphicMonitor::getPlayer(const std::string &num) const
{
  for (unsigned int index = 0; index < players.size(); index++)
    {
      if (players.at(index)->getNum() == num)
	return (players.at(index));
    }
  return (nullptr);
}

void GraphicMonitor::newGate(const std::string &numBlueGate, const std::string &numOrangeGate)
{
  std::shared_ptr<Gate>		gate;

  if (gatesNodes->find(numBlueGate) != gatesNodes->end()
      || gatesNodes->find(numOrangeGate) != gatesNodes->end())
    {
      gate.reset(new Gate(numBlueGate));
      gate->setBlueGate(gatesNodes->find(numBlueGate)->second);
      gate->setOrangeGate(gatesNodes->find(numOrangeGate)->second);
      gate->setFrequency(frequency);
      if (sounds.find("Portal_Crossing") != sounds.end())
	gate->setSound(sounds.find("Portal_Crossing")->second);
      gates.push_back(gate);
    }
}

std::shared_ptr<Gate> GraphicMonitor::getGate(const std::string &numBlueGate) const
{
  for (unsigned int index = 0; index < gates.size(); index++)
    {
      if (gates.at(index)->getNum() == numBlueGate)
	return (gates.at(index));
    }
  return (nullptr);
}

void GraphicMonitor::setFrequency(unsigned int frequency)
{
  this->frequency = frequency;
}

void GraphicMonitor::setGateFrequency(unsigned int frequency)
{
  for (unsigned int index = 0; index < gates.size(); index++)
    {
      gates.at(index)->setFrequency(frequency);
    }
}

void GraphicMonitor::doAnimations()
{
  for (std::vector<std::shared_ptr<Players>>::iterator it = players.begin(); it != players.end();)
    {
      if (!(*it)->isAlive())
	{
	  this->playersNodes->find((*it)->getNum())->second->remove();
	  this->playersNodes->erase(this->playersNodes->find((*it)->getNum()));
	  it = this->players.erase(it);
	}
      else
	++it;
    }
  for (unsigned int index = 0; index < players.size(); index++)
    players.at(index)->moove();
  for (unsigned int index = 0; index < gates.size(); index++)
    gates.at(index)->openTheGate();
}

void GraphicMonitor::playSound(const std::string &sound)
{
  if (sounds.find(sound) != sounds.end())
    sounds.find(sound)->second->playRandomSoundsLoaded();
}

void GraphicMonitor::playMusic(const std::string &music)
{
  if (sounds.find(music) != sounds.end())
    sounds.find(music)->second->playRandomMusicsLoaded();
}

void GraphicMonitor::stopMusic(const std::string &music)
{
  if (sounds.find(music) != sounds.end())
    sounds.find(music)->second->stopMusic();
}

const std::map<std::string, std::vector<irr::s32>> &GraphicMonitor::getAnimations() const
{
  return (animations);
}

void GraphicMonitor::changeCameraMode(const irr::core::vector3df position,
				      const irr::core::vector3df rotation,
				      const irr::core::vector3df target,
				      bool inputReceiver)
{
  this->camera->setPosition(position);
  this->camera->setRotation(rotation);
  if (!inputReceiver)
    this->camera->setTarget(target);
  this->camera->setInputReceiverEnabled(inputReceiver);
}

irr::scene::ICameraSceneNode *GraphicMonitor::getCamera() const
{
  return (camera);
}

TextPanel &GraphicMonitor::getTeamsPanel()
{
  return (teamsPanel);
}

TextPanel &GraphicMonitor::getBroadcastPanel()
{
  return (broadcastPanel);
}

void GraphicMonitor::reversePanelsVisibility()
{
  this->stonesPanel->setVisible(!this->stonesPanel->isVisible());
  this->teamsPanel.setVisible(!this->teamsPanel.isVisible());
  this->broadcastPanel.setVisible(!this->broadcastPanel.isVisible());
}

void GraphicMonitor::addCameraPosition(irr::EKEY_CODE key, const irr::core::vector3df &position)
{
  this->cameraPositions[key] = position;
}

void GraphicMonitor::changeCameraPosition(irr::EKEY_CODE key)
{
  if (this->cameraPositions.find(key) != this->cameraPositions.end())
    this->camera->setPosition(this->cameraPositions[key]);
}

irr::gui::IGUIImage *GraphicMonitor::getCredits()
{
  return (this->credits);
}
