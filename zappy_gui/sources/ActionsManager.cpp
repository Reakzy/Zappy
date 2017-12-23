/*
** ActionsManager.cpp for zappy_gui in /home/werp/rendu/zappy_gui/ActionsManager.cpp
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Mon Jun 19 14:07:25 2017 Paul Wéry
** Last update Mon Jun 19 14:07:25 2017 Paul Wéry
*/

# include "ActionsManager.hh"

ActionsManager::ActionsManager()
{
  playerPosChanged = false;
  moovedAtOpposite = false;
}

ActionsManager::~ActionsManager()
{

}

void ActionsManager::setSizeMap(unsigned int width, unsigned int height)
{
  this->sizeMap.X = width;
  this->sizeMap.Y = height;
  tiles.clear();
  for (unsigned int index = 0; index < (width * height); index++)
    tiles.push_back(std::vector<unsigned int>());
}

void ActionsManager::setTile(unsigned int x, unsigned int y, const std::vector<unsigned int> content)
{
  unsigned int index = posToIndex(irr::core::vector2d<irr::u32>(x, y));

  if (this->sizeMap.X * y + x <= (this->sizeMap.X * this->sizeMap.Y))
    {
      while (this->tiles.at(index).size() < content.size())
	this->tiles.at(index).push_back(0);
      for (unsigned int i = 0; i < content.size(); i++)
	{
	  this->tiles.at(index).at(i) = content.at(i);
	}
    }
}

void ActionsManager::newTeam(const std::string &teamName)
{
  if (this->teams.find(teamName) != teams.end())
    return ;
  this->teams.insert(std::make_pair(teamName, Players()));
  this->eggs.insert(std::make_pair(teamName, EggsList()));
}

unsigned int ActionsManager::posToIndex(irr::core::vector2d<irr::u32> position) const
{
  return (this->sizeMap.X * position.Y + position.X);
}

irr::core::vector2d<irr::u32> ActionsManager::indexToPos(unsigned int index) const
{
  return (irr::core::vector2d<irr::u32>(index % this->sizeMap.X, index / this->sizeMap.X));
}

void ActionsManager::newPlayer(const std::vector<std::string> &info)
{
  std::shared_ptr<Player>	player(new Player);

  if (this->teams.find(info.back()) == teams.end()
      || this->teams[info.back()].find(info.front()) != this->teams[info.back()].end())
    return ;
  player->position = irr::core::vector2d<irr::u32>(static_cast<irr::u32>(std::atoi(info.at(1).c_str())),
						   static_cast<irr::u32>(std::atoi(info.at(2).c_str())));
  player->rotation = static_cast<Rotation>(std::atoi(info.at(3).c_str()));
  player->level = static_cast<unsigned int>(std::atoi(info.at(4).c_str()));
  player->inventory = std::vector<unsigned int>();
  this->teams[info.back()][info.front()] = player;
}

void ActionsManager::setPlayerInventory(const std::string &num,
					const std::vector<unsigned int> content)
{
  std::shared_ptr<Player>	player = findPlayer(num);

  if (player.get() != nullptr)
    {
      player->inventory = content;
    }
}

std::shared_ptr<ActionsManager::Player> ActionsManager::findPlayer(const std::string &num)
{
  ActionsManager::Players::iterator	player;

  for (std::map<std::string, Players>::iterator it = this->teams.begin(); it != this->teams.end(); ++it)
    {
      if ((player = it->second.find(num)) != it->second.end())
	{
	  return (player->second);
	}
    }
  return (nullptr);
}

void ActionsManager::setPosPlayer(const std::vector<std::string> &info)
{
  std::shared_ptr<Player>	player = findPlayer(info.front());

  if (player.get() != nullptr)
    {
      playerPosChanged = player->position.X != static_cast<irr::u32>(std::atoi(info.at(1).c_str()))
			 || player->position.Y != static_cast<irr::u32>(std::atoi(info.at(2).c_str()));
      if (playerPosChanged)
	{
	  moovedAtOpposite = (player->position.X == 0 && static_cast<irr::u32>(std::atoi(info.at(1).c_str())) == (sizeMap.X - 1))
			     || (player->position.X == (sizeMap.X - 1) && static_cast<irr::u32>(std::atoi(info.at(1).c_str())) == 0)
			     || (player->position.Y == 0 && static_cast<irr::u32>(std::atoi(info.at(2).c_str())) == (sizeMap.Y - 1))
			     || (player->position.Y == (sizeMap.Y - 1) && static_cast<irr::u32>(std::atoi(info.at(2).c_str())) == 0);
	}
      player->position = irr::core::vector2d<irr::u32>(static_cast<irr::u32>(std::atoi(info.at(1).c_str())),
						       static_cast<irr::u32>(std::atoi(info.at(2).c_str())));
      player->rotation = static_cast<Rotation>(std::atoi(info.at(3).c_str()));
    }
}

void ActionsManager::setLevelPlayer(const std::string &num, unsigned int level)
{
  std::shared_ptr<Player>	player = findPlayer(num);

  if (player.get() != nullptr)
    {
      player->level = level;
    }
}

void ActionsManager::playerThrowsResource(const std::string &num, unsigned int resource)
{
  std::shared_ptr<Player>	player = findPlayer(num);

  if (player.get() != nullptr && resource < player->inventory.size())
    {
      if (player->inventory.at(resource) > 0)
      	player->inventory.at(resource)--;
    }
}

void ActionsManager::playerPicksUpResource(const std::string &num, unsigned int resource)
{
  std::shared_ptr<Player>	player = findPlayer(num);

  if (player.get() != nullptr && resource < player->inventory.size())
    {
      player->inventory.at(resource)++;
    }
}

void ActionsManager::playerDead(const std::string &num)
{
  ActionsManager::Players::iterator	player;

  for (std::map<std::string, Players>::iterator it = this->teams.begin(); it != this->teams.end(); ++it)
    {
      if ((player = it->second.find(num)) != it->second.end())
	{
	  it->second.erase(player);
	  return ;
	}
    }
}

void ActionsManager::playerLaysEgg(unsigned int x, unsigned int y,
				   const std::string &eggNum, const std::string &num)
{
  for (std::map<std::string, Players>::iterator it = this->teams.begin(); it != this->teams.end(); ++it)
    {
      if (it->second.find(num) != it->second.end())
	{
	  this->eggs[it->first][eggNum] = irr::core::vector2d<irr::u32>(x, y);
	  return ;
	}
    }
}

void ActionsManager::playerJoinEgg(const std::string &eggNum)
{
  Player	player;

  for (std::map<std::string, EggsList>::iterator it = this->eggs.begin(); it != this->eggs.end(); ++it)
    {
      for (EggsList::iterator eggIt = it->second.begin(); eggIt != it->second.end(); ++eggIt)
	{
	  if (eggIt->first == eggNum)
	    {
	      it->second.erase(eggIt);
	      return ;
	    }
	}
    }
}

void ActionsManager::eggDead(const std::string &eggNum)
{
  for (std::map<std::string, EggsList>::iterator it = this->eggs.begin(); it != this->eggs.end(); ++it)
    {
      for (EggsList::iterator eggIt = it->second.begin(); eggIt != it->second.end(); ++eggIt)
	{
	  if (eggIt->first == eggNum)
	    {
	      it->second.erase(eggIt);
	    }
	}
    }
}

const irr::core::vector2d<irr::u32> &ActionsManager::getSizeMap() const
{
  return (sizeMap);
}

const std::vector<std::vector<unsigned int>> &ActionsManager::getTiles() const
{
  return (tiles);
}

const std::map<std::string, ActionsManager::Players> &ActionsManager::getTeams() const
{
  return (teams);
}

const std::map<std::string, ActionsManager::EggsList> &ActionsManager::getEggs() const
{
  return (eggs);
}

const std::vector<unsigned int> &ActionsManager::getTile(unsigned int x, unsigned int y) const
{
  return (tiles.at(posToIndex(irr::core::vector2d<irr::u32>(x, y))));
}

bool ActionsManager::playerMooved() const
{
  return (playerPosChanged);
}

bool ActionsManager::playerMoovedAtOpposite() const
{
  return (moovedAtOpposite);
}

std::string ActionsManager::teamPlayer(const std::string &num) const
{
  for (std::map<std::string, Players>::const_iterator it = this->teams.begin(); it != this->teams.end(); ++it)
    {
      for (Players::const_iterator playerIt = it->second.begin(); playerIt != it->second.end(); ++playerIt)
	{
	  if (playerIt->first == num)
	    {
	      return (it->first);
	    }
	}
    }
  return ("");
}

std::string	ActionsManager::teamEgg(const std::string &eggNum) const
{
  for (std::map<std::string, EggsList>::const_iterator it = this->eggs.begin(); it != this->eggs.end(); ++it)
    {
      for (EggsList::const_iterator eggIt = it->second.begin(); eggIt != it->second.end(); ++eggIt)
	{
	  if (eggIt->first == eggNum)
	    {
	      return (it->first);
	    }
	}
    }
  return ("");
}

