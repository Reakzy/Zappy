/*
** EventReceiver.hh for zappy_gui in /home/werp/rendu/zappy_gui/EventReceiver.hh
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Sat Jul 01 23:26:35 2017 Paul Wéry
** Last update Sat Jul 01 23:26:35 2017 Paul Wéry
*/

#ifndef ZAPPY_GUI_EVENTRECEIVER_HH
#define ZAPPY_GUI_EVENTRECEIVER_HH

# include <map>
# include "irrlicht.h"

class GraphicMonitor;

class EventReceiver : public irr::IEventReceiver
{
  GraphicMonitor		&graphicMonitor;
  irr::core::vector3df		savedCameraPosition;
  irr::core::vector3df		savedCameraRotation;
  irr::core::vector3df		savedCameraTargetPosition;
  bool				alwaysChanged;

  typedef void (EventReceiver::*methode)(const irr::SEvent &event);
  std::map<irr::EKEY_CODE, methode>	actions;

  void			changeCameraMode(const irr::SEvent &event);
  void			reversePanelsVisibility(const irr::SEvent &event);
  void			changeCameraPosition(const irr::SEvent &event);

 public:

  virtual bool		OnEvent(const irr::SEvent &event);

  EventReceiver(GraphicMonitor &_graphicMonitor);
  EventReceiver(const EventReceiver &) = delete;
  ~EventReceiver();
  EventReceiver		&operator=(const EventReceiver &) = delete;
};


#endif //ZAPPY_GUI_EVENTRECEIVER_HH
