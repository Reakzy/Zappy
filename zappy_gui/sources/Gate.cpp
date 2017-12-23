/*
** Gate.cpp for zappy_gui in /home/werp/rendu/zappy_gui/Gate.cpp
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Sat Jul 01 00:09:21 2017 Paul Wéry
** Last update Sat Jul 01 00:09:21 2017 Paul Wéry
*/

#include "Gate.hh"

Gate::Gate(const std::string &num)
{
  this->num = num;
  this->operating = false;
}

Gate::Gate(const Gate &)
{

}

Gate::~Gate()
{

}

void Gate::setBlueGate(irr::scene::IAnimatedMeshSceneNode *node)
{
  this->blueGate = node;
}

void Gate::setOrangeGate(irr::scene::IAnimatedMeshSceneNode *node)
{
  this->orangeGate = node;
}

void Gate::setAction(irr::f32 scaleToStart, irr::f32 scaleToReach)
{
  if (this->blueGate == nullptr || this->orangeGate == nullptr)
    return ;
  if (!operating)
    {
      this->scaleToStart = scaleToStart;
      this->blueGate->setVisible(true);
      this->orangeGate->setVisible(true);
      this->blueGate->setScale(irr::core::vector3df(this->scaleToStart, this->scaleToStart, this->scaleToStart));
      this->orangeGate->setScale(irr::core::vector3df(this->scaleToStart, this->scaleToStart, this->scaleToStart));
    }
  this->scaleToReach.push(scaleToReach);
  this->timeUnit.startCheckTime("open gate");
  this->operating = true;
}

void Gate::openTheGate()
{
  if (!this->operating || this->blueGate == nullptr || this->orangeGate == nullptr)
    return ;
  if (this->scaleToReach.size() > 0)
    this->open();
  else
    this->close();
}

void Gate::open()
{
  irr::f32	scale;
  long		ellapsedTime;

  ellapsedTime = this->timeUnit.elapsedTime();
  scale = (this->scaleToReach.front() * ellapsedTime / this->timeUnit.timeAction()) * 2;
  if (this->blueGate->getScale().X < this->scaleToReach.front())
    {
      this->blueGate->setScale(this->blueGate->getScale() + irr::core::vector3df(scale, scale, scale));
      this->orangeGate->setScale(this->orangeGate->getScale() + irr::core::vector3df(scale, scale, scale));
    }
  if (this->timeUnit.remainingTime() <= this->timeUnit.timeAction() / 2)
    {
      this->lastScaleToReach = this->scaleToReach.front();
      this->scaleToReach.pop();
      if (this->cross_portal.get() != nullptr)
	this->cross_portal->playRandomSoundsLoaded();
    }
}

void Gate::close()
{
  irr::f32	scale;
  long		ellapsedTime;

  ellapsedTime = this->timeUnit.elapsedTime();
  scale = (this->lastScaleToReach * ellapsedTime / this->timeUnit.timeAction()) * 2;
  this->blueGate->setScale(this->blueGate->getScale() - irr::core::vector3df(scale, scale, scale));
  this->orangeGate->setScale(this->orangeGate->getScale() - irr::core::vector3df(scale, scale, scale));
  if (this->timeUnit.remainingTime() == 0)
    {
      this->blueGate->setScale(irr::core::vector3df(this->scaleToStart, this->scaleToStart, this->scaleToStart));
      this->orangeGate->setScale(irr::core::vector3df(this->scaleToStart, this->scaleToStart, this->scaleToStart));
      this->operating = false;
      this->blueGate->setVisible(false);
      this->orangeGate->setVisible(false);
      return ;
    }
}

void Gate::setFrequency(unsigned int frequency)
{
  this->timeUnit.setFrequency(frequency);
}

const std::string &Gate::getNum() const
{
  return (this->num);
}

void Gate::setSound(std::shared_ptr<SoundLoader> sound)
{
  this->cross_portal = sound;
}
