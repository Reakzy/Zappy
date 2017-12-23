/*
** Players.cpp for zappy_gui in /home/werp/rendu/zappy_gui/Players.cpp
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Mon Jun 26 11:07:24 2017 Paul Wéry
** Last update Mon Jun 26 11:07:24 2017 Paul Wéry
*/

# include "Players.hh"
# include "GraphicMonitor.hh"

Players::Players(const std::string &num, const std::map<std::string, std::vector<irr::s32>> &_animations)
{
  this->num = num;
  this->animations = _animations;
  this->haveTarget = false;
  this->animationDead = false;
  this->alive = true;
}

Players::Players(const Players &obj)
: animations(obj.animations)
{
  this->node = obj.node;
}

Players::~Players()
{

}

void Players::OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode *node)
{
  if (animationDead)
    {
      this->node->setCurrentFrame(0);
      this->alive = false;
    }
  else if (animations.find("moove") != animations.end())
    node->setFrameLoop(animations.find("moove")->second.at(0), animations.find("moove")->second.at(1));
}

void Players::setNode(irr::scene::IAnimatedMeshSceneNode *node)
{
  this->node = node;
  this->node->setAnimationEndCallback(this);
  if (animations.find("moove") != animations.end())
    {
      node->setFrameLoop(animations.find("moove")->second.at(0),
			 animations.find("moove")->second.at(1));
    }
  node->setLoopMode(true);
}

irr::scene::IAnimatedMeshSceneNode *Players::getNode() const
{
  return (node);
}

const std::string &Players::getNum() const
{
  return (num);
}
void Players::setTargetPosition(const std::vector<irr::core::vector3df> &position,
				const std::vector<irr::core::vector3df> &endPosition)
{
  irr::f32	posY = this->node->getPosition().Y;
  long		remainingTime;

  if (position.size() == 0 || position.size() != endPosition.size())
    return ;
  this->targetPosition.clear();
  this->endPosition.clear();
  this->shifting.clear();
  this->remainingTimes.clear();
  this->targetPosition = position;
  this->endPosition = endPosition;
  for (unsigned int index = 0; index < position.size(); index++)
    {
      if (this->shifting.size() == 0)
	this->shifting.push_back(position.at(index) - this->node->getPosition());
      else
	this->shifting.push_back(position.at(index) - endPosition.at(index - 1));
      this->shifting.back().Y = posY;
    }
  this->haveTarget = true;
  this->timeUnit.startCheckTime("forward");
  remainingTime = this->timeUnit.remainingTime();
  for (unsigned int index = 0; index < this->targetPosition.size(); index++)
    {
      this->remainingTimes.push_back(remainingTime - (remainingTime / this->targetPosition.size() * (index + 1)));
    }
}

irr::core::vector3df Players::getSumShifting() const
{
  irr::core::vector3df	sumShifting(0, 0, 0);

  if (this->shifting.size() == 0)
    return (sumShifting);
  sumShifting.Y += std::abs(this->shifting.at(0).Y);
  for (unsigned int index = 0; index < this->shifting.size(); index++)
    {
      if (this->shifting.at(0).X != 0)
	sumShifting.X += std::abs(this->shifting.at(index).X);
      if (this->shifting.at(0).Z != 0)
      	sumShifting.Z += std::abs(this->shifting.at(index).Z);
    }
  if (this->shifting.at(0).X < 0)
    sumShifting.X *= -1;
  if (this->shifting.at(0).Z < 0)
    sumShifting.Z *= -1;
  return (sumShifting);
}

void Players::moove()
{
  irr::f32	posX;
  irr::f32	posZ;
  long		ellapsedTime;

  if (this->haveTarget)
    {
      ellapsedTime = this->timeUnit.elapsedTime();
      posX = getSumShifting().X * ellapsedTime / this->timeUnit.timeAction();
      posZ = getSumShifting().Z * ellapsedTime / this->timeUnit.timeAction();
      this->node->setPosition(this->node->getPosition() + irr::core::vector3df(posX, 0, posZ));
      if (this->remainingTimes.front() >= this->timeUnit.remainingTime())
	{
	  this->node->setPosition(irr::core::vector3df(this->endPosition.front().X,
						       this->node->getPosition().Y,
						       this->endPosition.front().Z));
	  actualizeTarget();
	}
      if (this->timeUnit.remainingTime() == 0)
	{
	  if (this->endPosition.size() > 0)
	    {
	      this->node->setPosition(irr::core::vector3df(this->endPosition.back().X,
							   this->node->getPosition().Y,
							   this->endPosition.back().Z));
	    }
	  this->haveTarget = false;
	}
    }
}

void Players::actualizeTarget()
{
  irr::core::vector3df	back;

  back = this->shifting.front();
  this->shifting.push_back(back);
  this->shifting.erase(this->shifting.begin());
  this->targetPosition.erase(this->targetPosition.begin());
  this->endPosition.erase(this->endPosition.begin());
  this->remainingTimes.erase(this->remainingTimes.begin());
}

void Players::setFrequency(unsigned int frequency)
{
  this->timeUnit.setFrequency(frequency);
}

void Players::setAnimationDead(bool state)
{
  this->animationDead = state;
}

bool Players::isAlive() const
{
  return (this->alive);
}

