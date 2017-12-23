/*
** Gate.hh for zappy_gui in /home/werp/rendu/zappy_gui/Gate.hh
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Sat Jul 01 00:09:22 2017 Paul Wéry
** Last update Sat Jul 01 00:09:22 2017 Paul Wéry
*/

#ifndef ZAPPY_GUI_GATE_HH
#define ZAPPY_GUI_GATE_HH

# include <memory>
# include <string>
# include <queue>
# include "irrlicht.h"
# include "TimeUnit.hh"
# include "SoundLoader.hh"

class Gate
{
  std::string						num;
  unsigned int						time;
  TimeUnit						timeUnit;
  irr::scene::IAnimatedMeshSceneNode			*blueGate;
  irr::scene::IAnimatedMeshSceneNode			*orangeGate;
  irr::f32						scaleToStart;
  std::queue<irr::f32>					scaleToReach;
  irr::f32						lastScaleToReach;
  bool							operating;
  std::shared_ptr<SoundLoader>				cross_portal;

  void			open();
  void			close();

 public:

  void			setSound(std::shared_ptr<SoundLoader> sound);
  void			setAction(irr::f32 scaleToStart, irr::f32 scaleToReach);
  void			openTheGate();
  void			setBlueGate(irr::scene::IAnimatedMeshSceneNode *node);
  void			setOrangeGate(irr::scene::IAnimatedMeshSceneNode *node);
  void			setFrequency(unsigned int frequency);
  const std::string	&getNum() const;

  Gate(const std::string &num);
  Gate(const Gate &);
  ~Gate();
  Gate		&operator=(const Gate &) = delete;
};


#endif //ZAPPY_GUI_GATE_HH
