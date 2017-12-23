/*
** EventReceiver.cpp for zappy_gui in /home/werp/rendu/zappy_gui/EventReceiver.cpp
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Sat Jul 01 23:26:35 2017 Paul Wéry
** Last update Sat Jul 01 23:26:35 2017 Paul Wéry
*/

# include "EventReceiver.hh"
# include "GraphicMonitor.hh"

EventReceiver::EventReceiver(GraphicMonitor &_graphicMonitor)
: graphicMonitor(_graphicMonitor)
{
  this->actions[irr::EKEY_CODE::KEY_SPACE] = &EventReceiver::changeCameraMode;
  this->actions[irr::EKEY_CODE::KEY_KEY_I] = &EventReceiver::reversePanelsVisibility;
  this->actions[irr::EKEY_CODE::KEY_UP] = &EventReceiver::changeCameraPosition;
  this->actions[irr::EKEY_CODE::KEY_DOWN] = &EventReceiver::changeCameraPosition;
  this->actions[irr::EKEY_CODE::KEY_LEFT] = &EventReceiver::changeCameraPosition;
  this->actions[irr::EKEY_CODE::KEY_RIGHT] = &EventReceiver::changeCameraPosition;
  this->alwaysChanged = false;
}

EventReceiver::~EventReceiver()
{

}

bool EventReceiver::OnEvent(const irr::SEvent &event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
      if (actions.find(event.KeyInput.Key) != actions.end())
	{
	  (this->*actions[event.KeyInput.Key])(event);
	}
    }
  return (false);
}

void EventReceiver::changeCameraMode(const irr::SEvent &event)
{
  irr::core::vector3df	position;
  irr::core::vector3df	rotation;
  irr::core::vector3df	target;

  if (!event.KeyInput.PressedDown)
    {
      if (!this->alwaysChanged)
	{
	  position = this->graphicMonitor.getCamera()->getPosition();
	  rotation = this->graphicMonitor.getCamera()->getRotation();
	  target = this->graphicMonitor.getCamera()->getTarget();
	}
      else
	{
	  position = this->savedCameraPosition;
	  rotation = this->savedCameraRotation;
	  target = this->savedCameraTargetPosition;
	}
      this->savedCameraPosition = graphicMonitor.getCamera()->getPosition();
      this->savedCameraRotation = graphicMonitor.getCamera()->getRotation();
      this->savedCameraTargetPosition = graphicMonitor.getCamera()->getTarget();
      this->alwaysChanged = true;
      this->graphicMonitor.changeCameraMode(position, rotation, target, !this->graphicMonitor.getCamera()->isInputReceiverEnabled());
    }
}

void EventReceiver::reversePanelsVisibility(const irr::SEvent &event)
{
  if (!event.KeyInput.PressedDown)
    {
      this->graphicMonitor.reversePanelsVisibility();
    }
}

void EventReceiver::changeCameraPosition(const irr::SEvent &event)
{
  if (!event.KeyInput.PressedDown && !this->graphicMonitor.getCamera()->isInputReceiverEnabled())
    {
      this->graphicMonitor.changeCameraPosition(event.KeyInput.Key);
    }
}
